/*

    cRectangle - Class that allows create and draw a rectangle shape.

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


#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "cdrawable.h"

namespace onyx2d
{

class cRectangle : public cDrawable
{
    public:
        /** Default constructor */
        cRectangle();

        /**
            Copy constructor
            @param rc Other Rectangle
        */
        cRectangle(cRectangle* rc);

        /**
        *   Constructor that accept the position and size of the rectangle
        *   @param x X position of the rectangle
        *   @param y Y position of the rectangle
        *   @param width Width of the rectangle
        *   @param height Height of the rectangle
        */
        cRectangle(uint16 x, uint16 y, uint16 width, uint16 height);

        /** Destructor */
        virtual ~cRectangle();
    protected:
    private:
        /**
            Function that draws the image
        */
        void Draw();

        /**
            Function that updates the image
        */
        void Update(){};

        /**
            Function that contain all the geometry
        */
        void Geometry();

};

}

#endif // CRECTANGLE_H
