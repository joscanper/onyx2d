/*

    cColor - Class that contain all necesary elements and operations of color

    Copyright (C) 2010-2011 Josue Candela Perdomo (josuecp.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

**/

#ifndef CCOLOR_H_
#define CCOLOR_H_

#include "../core/math/mathtypes.h"
#include "../core/math/mathutils.h"
#include "../core/math/cvector2.h"
#include "../core/math/cvector3.h"
#include "../core/utils/types.h"

class cColor
{
public:
  float r, g, b, a; //! Color components

public:

  /** Constructor */
  inline cColor ();
  inline cColor (const cColor& other);
  inline cColor (const Vector3<float>& other);
  inline cColor (const Vector3<float>& other, const float ta);
  inline cColor (const float tr, const float tg, const float tb, const float ta);
  inline cColor (const float scalar);

  /** Arithmethic operations */
  inline        cColor  operator + (const cColor& other) const;
  inline        cColor  operator - (const cColor& other) const;
  inline        cColor  operator * (const float scalar) const;
  inline        cColor  operator / (const float scalar) const;
  inline        cColor  operator + (const float scalar) const;
  inline        cColor  operator - (const float scalar) const;
  inline        cColor  operator - () const;
  inline        cColor& operator + ();
  inline const  cColor& operator + () const;


  inline cColor& operator += (const cColor& otro);
  inline cColor& operator -= (const cColor& otro);
  inline cColor& operator *= (const float escalar);
  inline cColor& operator /= (const float escalar);
  inline cColor& operator += (const float escalar);
  inline cColor& operator -= (const float escalar);


  /** Assignment operators and functions */
  inline void operator =  (const cColor& other);
  inline cColor& operator () (const float tr, const float tg, const float tb, const float ta);
  inline void        Set         (const float tr, const float tg, const float tb, const float ta = 1.0f);
  inline void        SetZero     ();


  /** Scalar product (*) */
  inline float operator * (const cColor& otro) const;


  /** Comparison Functions and Operators */
  inline bool operator ==       (const cColor& otro) const;
  inline bool operator !=       (const cColor& otro) const;
  inline bool IsEqualEpsilon    (const cColor& otro) const;
  inline bool IsNotEqualEpsilon (const cColor& otro) const;


  /** Access operator */
  inline float  operator [] (int i) const;
  inline float& operator [] (int i);

  /** Length functions */
  inline cColor& Normalize     (const float tk = One<float>());
  inline cColor  GetNormalized () const;
  inline float           Length        () const;
  inline float           SquaredLength () const;

  /** Linear interpolation */
  inline cColor& Lerp    (const cColor& other, const float t);
  inline cColor  GetLerp (const cColor& other, const float t) const;
};

/** Operators */
inline cColor  operator * (const float scalar, const cColor& other);
inline cColor  operator / (const float scalar, const cColor& other);
inline cColor  operator + (const float scalar, const cColor& other);
inline cColor  operator - (const float scalar, const cColor& other);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File with definitions of inline functions
#include "ccolor.inl"


#endif

