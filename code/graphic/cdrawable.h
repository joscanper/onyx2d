/*

    cDrawable - Class that contain all necesary elements of a drawable object

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


#ifndef CDRAWABLE_H
#define CDRAWABLE_H

#include "../core/math/crect.hpp"
#include "../core/math/cvector2.h"
#include "../core/math/cvector3.h"
#include "../core/utils/gen_func.h"
#include "ccolor.h"
#include "../core/cobject.h"
#include <algorithm>

namespace onyx2d
{

class cDrawable : public cObject
{
    friend class cRenderManager;

    public:
        cColor Color;               //! Color of the object
        Vector3<float> Position;    //! Position of the object
        Vector2<float> Size;        //! Size of the object
        Vector2<float> RotationRef; //! Rotation reference point
        float Angle;                //! Angle of the object
        bool BoundingBox;           //! Indicates if will be drawed the bounding box
        bool Area;                  //! Indicates if will be drawed the drawable area

        /** Default constructor */
        cDrawable();

        /** Copy constructor */
        cDrawable(cDrawable*);

        /** Destructor */
        virtual ~cDrawable();

        /**
            Function that returns if the area described by the drawable was clicked
            @return <i>true</i> if the area was clicked, <i>false</i> in other case.
        */
        bool MouseHit(int button);

        /**
            Function that returns if the area described by the drawable overlap the
            given drawable
            @param dw Other drawable object
        */
        bool DrawableHit(cDrawable* obj);

        /**
            Function that copies other drawable properties
            @param dw Other drawable object
        */
        void Copy(cDrawable*);

        /**
            Function that deletes the object from the render manager and destroy itself
        */
        void Delete();

        /**
            Function that gives the rect that defines the position and size of the drawable
        */
        cRect Rect();


        /**
            Function that resizes this element and all its children propotionally
        */
        void Resize(Vector2<float> size);


        void SetParent(cDrawable* obj);

    protected:
        void DrawBoundingBox();

        /**
            Function that applies the parent transform to drawable and its own tranform
        */
        void Transform();

        /**
            Function that returns the absolute position of the drawable (depends of the parent)
            @return Absolute position of drawable element
        */
        Vector2<float> AbsolutePosition();


        /**

        */
        void AddChild(cDrawable* obj);

        /**

        */
        void RemoveChild(cDrawable* obj);

        /**

        */
        //float AbsoluteRotation();

        /**

        */
        //Vector2<float> AbsoluteRotationRef();




    private:
        cDrawable* pParent;          //! Parent of the drawable
        vector<cDrawable*> vChildren; //! Children of the drawable

        /**
            Virtual function that draws the object
        */
        virtual void Draw(){};

        /**
            Virtual function that updates the object
        */
        void Update();





};

}

#endif // CDRAWABLE_H
