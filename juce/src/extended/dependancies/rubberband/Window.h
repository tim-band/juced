/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
    Rubber Band
    An audio time-stretching and pitch-shifting library.
    Copyright 2007-2008 Chris Cannam.
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.  See the file
    COPYING included with this distribution for more information.
*/

#ifndef _RUBBERBAND_WINDOW_H_
#define _RUBBERBAND_WINDOW_H_

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <map>

#include "sysutils.h"

namespace RubberBand {

enum WindowType {
    RectangularWindow,
    BartlettWindow,
    HammingWindow,
    HanningWindow,
    BlackmanWindow,
    GaussianWindow,
    ParzenWindow,
    NuttallWindow,
    BlackmanHarrisWindow
};

template <typename Type>
class Window
{
public:
    /**
     * Construct a windower of the given type.
     */
    Window(WindowType type, int size) : m_type(type), m_size(size) { encache(); }
    Window(const Window &w) : m_type(w.m_type), m_size(w.m_size) { encache(); }
    Window &operator=(const Window &w) {
	if (&w == this) return *this;
	m_type = w.m_type;
	m_size = w.m_size;
	encache();
	return *this;
    }
    virtual ~Window() { delete[] m_cache; }
    
    void cut(Type *R__ src) const
    {
        const int sz = m_size;
        for (int i = 0; i < sz; ++i) {
            src[i] *= m_cache[i];
        }
    }

    void cut(Type *R__ src, Type *dst) const {
        const int sz = m_size;
	for (int i = 0; i < sz; ++i) {
            dst[i] = src[i];
        }
	for (int i = 0; i < sz; ++i) {
            dst[i] *= m_cache[i];
        }
    }

    Type getArea() { return m_area; }
    Type getValue(int i) { return m_cache[i]; }

    WindowType getType() const { return m_type; }
    int getSize() const { return m_size; }

protected:
    WindowType m_type;
    int m_size;
    Type *R__ m_cache;
    Type m_area;
    
    void encache();
    void cosinewin(Type *, Type, Type, Type, Type);
};

template <typename Type>
void Window<Type>::encache()
{
    int n = int(m_size);
    Type *mult = new Type[n];
    int i;
    for (i = 0; i < n; ++i) mult[i] = 1.0;

    switch (m_type) {
		
    case RectangularWindow:
	for (i = 0; i < n; ++i) {
	    mult[i] *= 0.5;
	}
	break;
	    
    case BartlettWindow:
	for (i = 0; i < n/2; ++i) {
	    mult[i] *= (i / Type(n/2));
	    mult[i + n/2] *= (1.0f - (i / Type(n/2)));
	}
	break;
	    
    case HammingWindow:
        cosinewin(mult, 0.54f, 0.46f, 0.0f, 0.0f);
	break;
	    
    case HanningWindow:
        cosinewin(mult, 0.50f, 0.50f, 0.0f, 0.0f);
	break;
	    
    case BlackmanWindow:
        cosinewin(mult, 0.42f, 0.50f, 0.08f, 0.0f);
	break;
	    
    case GaussianWindow:
	for (i = 0; i < n; ++i) {
            mult[i] *= pow((Type)2.0f, - pow((i - (n-1)/2.0f) / ((n-1)/2.0f / 3.0f), 2.0f));
	}
	break;
	    
    case ParzenWindow:
    {
        int N = n-1;
        for (i = 0; i < N/4; ++i) {
            Type m = 2 * pow(1.0f - (Type(N)/2 - i) / (Type(N)/2), 3);
            mult[i] *= m;
            mult[N-i] *= m;
        }
        for (i = N/4; i <= N/2; ++i) {
            int wn = i - N/2;
            Type m = 1.0f - 6 * pow(wn / (Type(N)/2), 2) * (1.0f - abs(wn) / (Type(N)/2));
            mult[i] *= m;
            mult[N-i] *= m;
        }            
        break;
    }

    case NuttallWindow:
        cosinewin(mult, 0.3635819f, 0.4891775f, 0.1365995f, 0.0106411f);
	break;

    case BlackmanHarrisWindow:
        cosinewin(mult, 0.35875f, 0.48829f, 0.14128f, 0.01168f);
        break;
    }
	
    m_cache = mult;

    m_area = 0;
    for (int i = 0; i < n; ++i) {
        m_area += m_cache[i];
    }
    m_area /= n;
}

template <typename Type>
void Window<Type>::cosinewin(Type *mult, Type a0, Type a1, Type a2, Type a3)
{
    const Type pi((Type)M_PI);
    int n = int(m_size);
    for (int i = 0; i < n; ++i) {
        mult[i] *= (a0
                    - a1 * cos(2 * pi * i / n)
                    + a2 * cos(4 * pi * i / n)
                    - a3 * cos(6 * pi * i / n));
    }
}

}

#endif
