/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

   @author  Paul Nasca
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#include "Chorus.h"

// this is expressed in milliseconds
#define MAX_CHORUS_DELAY 250.0


//==============================================================================
Chorus::Chorus (int insertion_, REALTYPE *efxoutl_, REALTYPE *efxoutr_)
{
    efxoutl = efxoutl_;
    efxoutr = efxoutr_;
    dlk = 0;
    drk = 0;
    maxdelay = (int)(MAX_CHORUS_DELAY / 1000.0 * SAMPLE_RATE);
    delayl = new REALTYPE[maxdelay];
    delayr = new REALTYPE[maxdelay];
    insertion = insertion_;

    filterpars = NULL;
    Ppreset = 0;
    setPreset (Ppreset);

    lfo.effectlfoout (&lfol, &lfor);
    dl2 = getdelay (lfol);
    dr2 = getdelay (lfor);
    clean();
}

Chorus::~Chorus()
{
    delete [] delayl;
    delete [] delayr;
}

//==============================================================================
REALTYPE Chorus::getdelay (REALTYPE xlfo)
{
    REALTYPE result;
    if (Pflangemode == 0)
    {
        result = (delay + xlfo * depth) * SAMPLE_RATE;
    }
    else
        result = 0;

    //check if it is too big delay(caused bu errornous setdelay() and setdepth()
    if ((result + 0.5) >= maxdelay)
    {
        DBG ("WARNING: Chorus.C::getdelay(..) too big delay (see setdelay and setdepth funcs.)");
        result = maxdelay - 1.0;
    }
    return (result);
}

//==============================================================================
void Chorus::clean()
{
    for (int i = 0; i < maxdelay; i++)
    {
        delayl[i]=0.0;
        delayr[i]=0.0;
    }
}

//==============================================================================
void Chorus::out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples)
{
    int i;
    dl1 = dl2;
    dr1 = dr2;
    lfo.effectlfoout (&lfol, &lfor);

    dl2 = getdelay (lfol);
    dr2 = getdelay (lfor);

    for (i = 0; i < numSamples; i++)
    {
        REALTYPE inl = smpsl[i];
        REALTYPE inr = smpsr[i];

        //LRcross
        REALTYPE l = inl;
        REALTYPE r = inr;
        inl = l * (1.0 - lrcross) + r * lrcross;
        inr = r * (1.0 - lrcross) + l * lrcross;

        //Left channel

        //compute the delay in samples using linear interpolation between the lfo delays
        mdel = (dl1 * (numSamples - i) + dl2 * i) / numSamples;

        dlk = (dlk + 1) % maxdelay; // @XXX - new code
//        if (++dlk >= maxdelay) dlk = 0;

        REALTYPE tmp = dlk - mdel + maxdelay * 2.0; //where should I get the sample from

        F2I (tmp, dlhi);
        dlhi %= maxdelay;

        dlhi2 = (dlhi - 1 + maxdelay) % maxdelay;
        dllo = 1.0 - fmod (tmp, 1.0);
        efxoutl[i] = delayl[dlhi2] * dllo + delayl[dlhi] * (1.0 - dllo);
        delayl[dlk] = inl + efxoutl[i] * fb;

        //Right channel

        //compute the delay in samples using linear interpolation between the lfo delays
        mdel = (dr1 * (numSamples - i) + dr2 * i) / numSamples;

        drk = (drk + 1) % maxdelay; // @XXX - new code
//        if (++drk >= maxdelay) drk = 0;

        tmp = drk - mdel + maxdelay * 2.0; //where should I get the sample from

        F2I (tmp, dlhi);
        dlhi %= maxdelay;

        dlhi2 = (dlhi - 1 + maxdelay) % maxdelay;
        dllo = 1.0 - fmod (tmp, 1.0);
            efxoutr[i] = delayr[dlhi2] * dllo + delayr[dlhi] * (1.0 - dllo);
        delayr[dlk] = inr + efxoutr[i] * fb;
    }

    if (Poutsub != 0)
    for (i = 0; i < numSamples; i++)
    {
        efxoutl[i] *= -1.0;
        efxoutr[i] *= -1.0;
    }

    for (i = 0; i < numSamples; i++)
    {
        efxoutl[i] *= panning;
        efxoutr[i] *= (1.0 - panning);
    }
}

//==============================================================================
void Chorus::setParameter (int npar, uint8 value)
{
    switch(npar) {
    case 0: setvolume (value);
            break;
    case 1: setpanning (value);
            break;
    case 2: lfo.Pfreq = value;
            lfo.updateparams();
            break;
    case 3: lfo.Prandomness = value;
            lfo.updateparams();
            break;
    case 4: lfo.PLFOtype = value;
            lfo.updateparams();
            break;
    case 5: lfo.Pstereo=value;
            lfo.updateparams();
            break;
    case 6: setdepth (value);
            break;
    case 7: setdelay (value);
            break;
    case 8: setfb (value);
            break;
    case 9: setlrcross(value);
            break;
    case 10: if (value > 1) value = 1;
             Pflangemode = value;
             break;
    case 11: if (value > 1) value = 1;
             Poutsub = value;
             break;
    }
}

uint8 Chorus::getParameter (int npar)
{
    switch (npar)
    {
    case 0:  return(Pvolume);          break;
    case 1:  return(Ppanning);         break;
    case 2:  return(lfo.Pfreq);        break;
    case 3:  return(lfo.Prandomness);  break;
    case 4:  return(lfo.PLFOtype);     break;
    case 5:  return(lfo.Pstereo);      break;
    case 6:  return(Pdepth);           break;
    case 7:  return(Pdelay);           break;
    case 8:  return(Pfb);              break;
    case 9:  return(Plrcross);         break;
    case 10: return(Pflangemode);      break;
    case 11: return(Poutsub);          break;
    default: return (0);
    }
}

//==============================================================================
void Chorus::setdepth (uint8 Pdepth)
{
    this->Pdepth=Pdepth;
    depth=(pow(8.0,(Pdepth/127.0)*2.0)-1.0)/1000.0;//seconds
}

void Chorus::setdelay (uint8 Pdelay)
{
    this->Pdelay=Pdelay;
    delay=(pow(10.0,(Pdelay/127.0)*2.0)-1.0)/1000.0;//seconds
}

void Chorus::setfb (uint8 Pfb)
{
    this->Pfb=Pfb;
    fb=(Pfb-64.0)/64.1;
}

void Chorus::setvolume (uint8 Pvolume)
{
    this->Pvolume=Pvolume;
    outvolume=Pvolume/127.0;
    if (insertion==0) volume=1.0;
    else volume=outvolume;
}

void Chorus::setpanning (uint8 Ppanning)
{
    this->Ppanning=Ppanning;
    panning=Ppanning/127.0;
}

void Chorus::setlrcross (uint8 Plrcross)
{
    this->Plrcross=Plrcross;
    lrcross=Plrcross/127.0;
}

//==============================================================================
void Chorus::setPreset (uint8 npreset)
{
    const int PRESET_SIZE = 12;
    const int NUM_PRESETS = 10;

    uint8 presets[NUM_PRESETS][PRESET_SIZE] =
    {
        //Chorus1
        {64,64,50,0,0,90,40,85,64,119,0,0},
        //Chorus2
        {64,64,45,0,0,98,56,90,64,19,0,0},
        //Chorus3
        {64,64,29,0,1,42,97,95,90,127,0,0},
        //Celeste1
        {64,64,26,0,0,42,115,18,90,127,0,0},
        //Celeste2
        {64,64,29,117,0,50,115,9,31,127,0,1},
        //Flange1
        {64,64,57,0,0,60,23,3,62,0,0,0},
        //Flange2
        {64,64,33,34,1,40,35,3,109,0,0,0},
        //Flange3
        {64,64,53,34,1,94,35,3,54,0,0,1},
        //Flange4
        {64,64,40,0,1,62,12,19,97,0,0,0},
        //Flange5
        {64,64,55,105,0,24,39,19,17,0,0,1}
    };

    if (npreset >= NUM_PRESETS) npreset = NUM_PRESETS - 1;
    for (int n = 0; n < PRESET_SIZE; n++) setParameter (n, presets[npreset][n]);
    Ppreset = npreset;
}

