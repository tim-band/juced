/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2009 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================
*/

#ifndef __JUCETICE_LOCKFREEFIFO_HEADER__
#define __JUCETICE_LOCKFREEFIFO_HEADER__
 

//==============================================================================
/**
 * Exception to catch in the NOT - REALTIME thread polling for get !
 */
class LockFreeFifoUnderrunException
{
public:
    LockFreeFifoUnderrunException ()
    {
    }
};

class LockFreeFifoOverrunException
{
public:
    LockFreeFifoOverrunException ()
    {
    }
};

 
//==============================================================================
/*
    Implementation of a circular buffer
 
    - <typename T> specifies the samples type (i.e. use <float> for VST)
    - The buffer is memory aligned for better performance
*/
template<class ElementType>
class LockFreeFifo
{
public:

    //==============================================================================
    /** Constructor */
    LockFreeFifo (int32 bufferSize)
        : readIndex (0),
          writeIndex (0),
          bufferMax (bufferSize - 1),
          buffer (0)
    {
        jassert((bufferMax & bufferSize) == 0); // bufferSize must be a power of 2
        buffer = new ElementType [bufferSize];
    }

    ~LockFreeFifo ()
    {
        delete[] buffer;
    }

    //==============================================================================
    /**
        Get a value from the FIFO
    */
    ElementType get ()
    {
        if ((readIndex ^ writeIndex) & bufferMax == 0)
        {
            return (ElementType) 0;
        }

        return buffer[readIndex++ & bufferMax];
    }

    //==============================================================================
    /**
        Feed in a new value to the FIFO
    */
    void put (ElementType data)
    {
        buffer [++writeIndex & bufferMax] = data;
    }

    //==============================================================================
    /**
        Returns true if the fifo is empty
    */
    bool isEmpty () const 
    {
        return readIndex == writeIndex;   
    }

    /**
        Returns true if the fifo is full
    */
    bool isFull () const 
    {
        return (((writeIndex + 1) ^ readIndex) & bufferMax) == 0;
    }

private:

    volatile std::atomic_int32_t readIndex, writeIndex;
    int32 bufferMax;
    ElementType* buffer;
};

#endif
