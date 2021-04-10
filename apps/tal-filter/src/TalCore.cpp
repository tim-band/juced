/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#include "includes.h"
#include "TalComponent.h"
#include "TalCore.h"
#include "ProgramChunk.h"

#include <cmath>

/**
    This function must be implemented to create a new instance of your
    plugin object.
*/
AudioProcessor* JUCE_CALLTYPE createPluginFilter(const String& commandLine)
{
    return new TalCore();
}

TalCore::TalCore()
{
	// init engine
	if (this->getSampleRate() > 0)
		sampleRate = this->getSampleRate();
	else
		sampleRate = 44100.0f;

    zeromem (&lastPosInfo, sizeof (lastPosInfo));
    lastPosInfo.timeSigNumerator = 4;
    lastPosInfo.timeSigDenominator = 4;
    lastPosInfo.bpm = 120;

	engine = new Engine(sampleRate);
	talPresets = new TalPreset*[NUMPROGRAMS];

	for (int i = 0; i < NUMPROGRAMS; i++) talPresets[i] = new TalPreset(); 
	curProgram = 0;

	// load factory presets
	ProgramChunk *chunk = new ProgramChunk();
	XmlDocument myDocument (chunk->getXmlChunk());
	XmlElement* mainElement = myDocument.getDocumentElement();
	
	MemoryBlock* destData = new MemoryBlock();
	copyXmlToBinary(*mainElement, *destData);
	setStateInformation(destData->getData(), destData->getSize());
	setCurrentProgram(curProgram);

	// used for midi learn
	lastMovedController = 0;
}

TalCore::~TalCore()
{
	if (talPresets) delete[] talPresets;
	if (engine) delete engine;
}

const String TalCore::getName() const
{
    return "Tal-Filter";
}

int TalCore::getNumParameters()
{
	return NUMPARAM;
}

float TalCore::getParameter (int index)
{
	if (index < NUMPARAM)
		return talPresets[curProgram]->programData[index];
	else 
		return 0;
}

void TalCore::setParameter (int index, float newValue)
{
	if (index < NUMPARAM)
	{
		switch(index)
		{
		case LFORATE:
			engine->setSync((int)talPresets[curProgram]->programData[LFOSYNC], newValue);
			break;
		case LFOSYNC:
			engine->setSync((int)newValue, talPresets[curProgram]->programData[LFORATE]);
			break;
		case VOLUME:
			engine->setVolume(newValue);
			break;
		case INPUTDRIVE:
			engine->setInputDrive(newValue);
			break;
		case ENVELOPEINTENSITY:
			engine->setEnvelopeAmount(newValue);
			break;
		case LFOINTENSITY:
			engine->setLfoAmount(newValue);
			break;
		}
		engine->param[index] = newValue;
		talPresets[curProgram]->programData[index] = newValue;
		sendChangeMessage (this);

		// for midi learn
		lastMovedController = index;
	}
}

const String TalCore::getParameterName (int index)
{
	switch(index)
	{
		case CUTOFF: return T("cutoff");
		case RESONANCE: return T("resonance");
		case FILTERTYPE: return T("filtertype");
		case LFOINTENSITY: return T("lfointensity");
		case LFORATE: return T("lforate");
		case LFOSYNC: return T("lfosync");
		case LFOWAVEFORM: return T("lfowaveform");
		case VOLUME: return T("volume");
		case INPUTDRIVE: return T("inputdrive");
		case ENVELOPEINTENSITY: return T("envelopeintensity");
		case ENVELOPESPEED: return T("envelopespeed");
		case LFOWIDTH: return T("lfowidth");
		case MIDILEARN: return T("Midi Learn");
	}
    return String::empty;
}

const String TalCore::getParameterText (int index)
{
	if (index < NUMPARAM)
	{
		return String (engine->param[index], 2);
	}
    return String::empty;
}

const String TalCore::getInputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

const String TalCore::getOutputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

bool TalCore::isInputChannelStereoPair (int index) const
{
    return true;
}

bool TalCore::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool TalCore::acceptsMidi() const
{
    return true;
}

bool TalCore::producesMidi() const
{
    return false;
} 

void TalCore::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	engine->setSampleRate(sampleRate);
}

void TalCore::releaseResources()
{
    // when playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void TalCore::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiMessages)
{
    AudioPlayHead::CurrentPositionInfo pos;
    if (getPlayHead() != 0 && getPlayHead()->getCurrentPosition (pos))
    {
        if (memcmp (&pos, &lastPosInfo, sizeof (pos)) != 0)
        {
            lastPosInfo = pos;
			engine->setBpm(lastPosInfo.bpm, 
				talPresets[curProgram]->programData[LFOSYNC], 
				talPresets[curProgram]->programData[LFORATE]);

			if (talPresets[curProgram]->programData[LFOSYNC] > 1)
			{
				// Sync lfo to host
				float inc = engine->getLfoInc() / 256.0f;
				float samplesPerBeat = 60.0f / lastPosInfo.bpm * sampleRate;
				// find Phase
				float phase = inc * samplesPerBeat * lastPosInfo.ppqPosition;
				engine->setLfoPhase(phase - floorf(phase));
			}
        }
    }
    else
    {
		engine->setBpm(120.0f,				
			talPresets[curProgram]->programData[LFOSYNC], 
			talPresets[curProgram]->programData[LFORATE]);
    }

    const ScopedLock sl (this->getCallbackLock());

    // for each of our input channels, we'll attenuate its level by the
    // amount that our volume parameter is set to.
	int numberOfChannels = getNumInputChannels();

	// midi buffer
	MidiMessage controllerMidiMessage (0xF0);
    MidiBuffer::Iterator midiIterator(midiMessages);
	hasMoreMidiMessages = midiIterator.getNextEvent(controllerMidiMessage, midiEventPos);

	if (numberOfChannels == 2)
	{
		float *samples0 = buffer.getSampleData(0, 0);
		float *samples1 = buffer.getSampleData(1, 0);

		int samplePos = 0;
		int numSamples = buffer.getNumSamples();
		while (numSamples > 0)
		{
			processMidiPerSample(&midiIterator, controllerMidiMessage, samplePos);
			engine->process(samples0++, samples1++);
			numSamples--;
			samplePos++;
		}
	}
	if (numberOfChannels == 1)
	{
		float *samples0 = buffer.getSampleData(0, 0);
		float *samples1 = buffer.getSampleData(0, 0); 

		int samplePos = 0;
		int numSamples = buffer.getNumSamples();
		while (numSamples > 0)
		{
			processMidiPerSample(&midiIterator, controllerMidiMessage, samplePos);
			engine->process(samples0++, samples1++);
			numSamples--;
			samplePos++;
		}
	}
    // in case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

void TalCore::processMidiPerSample(MidiBuffer::Iterator *midiIterator, MidiMessage controllerMidiMessage, int samplePos)
{
	// There can be more than one event at the same position
	while (hasMoreMidiMessages && midiEventPos == samplePos)
	{ 
		if (controllerMidiMessage.isController())
		{
			handleController (controllerMidiMessage.getControllerNumber(),
							  controllerMidiMessage.getControllerValue());
		}
		hasMoreMidiMessages = midiIterator->getNextEvent (controllerMidiMessage, midiEventPos);
	}
}

void TalCore::handleController (const int controllerNumber,
								const int controllerValue)
{
	if (engine->param[MIDILEARN] > 0.0f)
	{
		for (int i = 0; i < NUMPROGRAMS; i++) 
		{
			talPresets[i]->midiMap[controllerNumber] = lastMovedController; 
		}
	}
	if (talPresets[curProgram]->midiMap[controllerNumber] > 0)
	{
		setParameter (talPresets[curProgram]->midiMap[controllerNumber], controllerValue / 127.0f);
	}
}

AudioProcessorEditor* TalCore::createEditor()
{
    return new TalComponent (this);
}

void TalCore::getStateInformation (MemoryBlock& destData)
{
    // you can store your parameters as binary data if you want to or if you've got
    // a load of binary to put in there, but if you're not doing anything too heavy,
    // XML is a much cleaner way of doing it - here's an example of how to store your
    // params as XML..

	// header
	XmlElement tal("tal");
	tal.setAttribute (T("curprogram"), curProgram);
	tal.setAttribute (T("version"), 1);

	// programs
    XmlElement *programList = new XmlElement ("programs");
	for (int i = 0; i < NUMPROGRAMS; i++)
	{
		XmlElement* program = new XmlElement ("program");
		program->setAttribute (T("programname"), talPresets[i]->name);
		program->setAttribute (T("cutoff"), talPresets[i]->programData[CUTOFF]);
		program->setAttribute (T("resonance"), talPresets[i]->programData[RESONANCE]);
		program->setAttribute (T("filtertype"), talPresets[i]->programData[FILTERTYPE]);
		program->setAttribute (T("lfointensity"), talPresets[i]->programData[LFOINTENSITY]);
		program->setAttribute (T("lforate"), talPresets[i]->programData[LFORATE]);
		program->setAttribute (T("lfosync"), talPresets[i]->programData[LFOSYNC]);
		program->setAttribute (T("lfowaveform"), talPresets[i]->programData[LFOWAVEFORM]);
		program->setAttribute (T("volume"), talPresets[i]->programData[VOLUME]);
		program->setAttribute (T("inputdrive"), talPresets[i]->programData[INPUTDRIVE]);
		program->setAttribute (T("envelopeintensity"), talPresets[i]->programData[ENVELOPEINTENSITY]);
		program->setAttribute (T("envelopespeed"), talPresets[i]->programData[ENVELOPESPEED]);
		program->setAttribute (T("lfowidth"), talPresets[i]->programData[LFOWIDTH]);

		programList->addChildElement(program);
	}
	tal.addChildElement(programList);

	// midi params
	XmlElement *midiMapList = new XmlElement ("midimap");
	for (int i = 0; i < 255; i++)
	{
		if (talPresets[0]->midiMap[i] != 0)
		{
			XmlElement* map = new XmlElement ("map");
			map->setAttribute (T("param"), talPresets[0]->midiMap[i]);
			map->setAttribute (T("controllernumber"), i);
			midiMapList->addChildElement(map);
		}
	}
	tal.addChildElement(midiMapList);

	// Reset midi learn
	setParameter(MIDILEARN, 0.0f);
	sendChangeMessage (this);

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (tal, destData);

	// use this for new factory presets
	//#ifdef _DEBUG && WIN32
	//File *file = new File("d:/presets.txt");
	//String myXmlDoc = tal.createDocument (String::empty);
	//file->replaceWithText(myXmlDoc);
	//#endif
}

void TalCore::setStateInformation (const void* data, int sizeInBytes)
{
	// use this helper function to get the XML from this binary blob..
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

	curProgram = 0;
	if (xmlState != 0 && xmlState->hasTagName(T("tal")))
	{
		curProgram = xmlState->getIntAttribute (T("curprogram"), 0.8f);
		XmlElement* programs = xmlState->getFirstChildElement();
		if (programs->hasTagName(T("programs")))
		{
			int i = 0;
			forEachXmlChildElement (*programs, e)
			{
				if (e->hasTagName(T("program")) && i < NUMPROGRAMS)
				{
					talPresets[i]->name = e->getStringAttribute (T("programname"), T("Not Saved"));
					talPresets[i]->programData[CUTOFF] = (float) e->getDoubleAttribute (T("cutoff"), 0.8f);
					talPresets[i]->programData[RESONANCE] = (float) e->getDoubleAttribute (T("resonance"), 0.8f);
					talPresets[i]->programData[FILTERTYPE] = (float) e->getDoubleAttribute (T("filtertype"), 1.0f);
					talPresets[i]->programData[LFOINTENSITY] = (float) e->getDoubleAttribute (T("lfointensity"), 1.0f);
					talPresets[i]->programData[LFORATE] = (float) e->getDoubleAttribute (T("lforate"), 1.0f);
					talPresets[i]->programData[LFOSYNC] = (float) e->getDoubleAttribute (T("lfosync"), 1.0f);
					talPresets[i]->programData[LFOWAVEFORM] = (float) e->getDoubleAttribute (T("lfowaveform"), 1.0f);
					talPresets[i]->programData[VOLUME] = (float) e->getDoubleAttribute (T("volume"), 0.5f);
					talPresets[i]->programData[INPUTDRIVE] = (float) e->getDoubleAttribute (T("inputdrive"), 1.0f);
					talPresets[i]->programData[ENVELOPEINTENSITY] = (float) e->getDoubleAttribute (T("envelopeintensity"), 0.5f);
					talPresets[i]->programData[ENVELOPESPEED] = (float) e->getDoubleAttribute (T("envelopespeed"), 1.0f);
					talPresets[i]->programData[LFOWIDTH] = (float) e->getDoubleAttribute (T("lfowidth"), 1.0f);
					i++;
				}
			}
		}
		// restore midi mapping
		XmlElement* midiMap = xmlState->getChildByName(T("midimap"));
		if (midiMap != 0 && midiMap->hasTagName(T("midimap")))
		{
			forEachXmlChildElement (*midiMap, e)
			{
				for (int j = 0; j < NUMPROGRAMS; j++) 
				{
					int controller = e->getIntAttribute(T("controllernumber"), 0);
					if (controller < 255 && controller > 0)
					{
						talPresets[j]->midiMap[controller] = e->getIntAttribute(T("param"), 0);
					}
				}
			}
		}
		delete xmlState;
		setCurrentProgram(curProgram);
		sendChangeMessage (this);
	}
}

int TalCore::getNumPrograms ()
{
	return NUMPROGRAMS;
}

int TalCore::getCurrentProgram ()
{
	return curProgram;
}

void TalCore::setCurrentProgram (int index)
{
	if (index < NUMPROGRAMS)
	{
		curProgram = index;
		for (int i = 0; i < NUMPARAM; i++) 
		{
			setParameter(i, talPresets[index]->programData[i]);
		}
		sendChangeMessage (this);
	}
}

const String TalCore::getProgramName (int index)
{
	if (index < NUMPROGRAMS)
		return talPresets[index]->name;
	else
		return T("Invalid");
}

void TalCore::changeProgramName (int index, const String& newName)
{
	if (index < NUMPROGRAMS)
		talPresets[index]->name = newName;
}
