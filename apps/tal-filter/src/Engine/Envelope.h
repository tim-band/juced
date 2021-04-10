/*
	==============================================================================
	This file is part of Tal-Reverb by Patrick Kunz.

	Copyright(c) 2005-2009 Patrick Kunz, TAL
	Togu Audio Line, Inc.
	http://kunz.corrupt.ch

	This file may be licensed under the terms of of the
	GNU General Public License Version 2 (the ``GPL'').

	Software distributed under the License is distributed
	on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
	express or implied. See the GPL for the specific language
	governing rights and limitations.

	You should have received a copy of the GPL along with this
	program. If not, go to http://www.gnu.org/licenses/gpl.html
	or write to the Free Software Foundation, Inc.,  
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
	==============================================================================
 */


#if !defined(__TalEnvelope_h)
#define __TalEnvelope_h

#include <cmath>

// Low pass filter for gentle parameter changes
class Envelope
{
private:
	float currentValue;
	float paramWeight;

public:
	Envelope() : currentValue(0.0), paramWeight(0.0)
	{
	}

	void setSampleRate(float sampleRate) {
		paramWeight = M_PI / sampleRate;
	}

	// speed [0,1] --> 1 = fast, 0 = slow
	// input [-1,1]
	// single pole lowpass recurrance: ynew = yold + a*x
	// for small w, a = w/2. w = 2pi*f/samplerate so a = pi*f/samplerate
	// t = 1/f (right? maybe there's a pi in there)
	// => a = (pi / samplerate) / t
	float tick(float input, float amount, float speed)
	{
		static const float slowest = 0.05;
		static const float fastest = 0.5;
		float t = slowest + (fastest - slowest) * speed;
		input = fabs(input);
		if (input > 1.0f) input = 1.0f;
		currentValue = currentValue + input * paramWeight / t;
		return currentValue * amount * 4.0f;
	}
};
#endif
