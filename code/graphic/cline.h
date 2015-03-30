/*

    cLine - Class that allows lines creation and drawing

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

#ifndef CLINE_H
#define CLINE_H

#include "../onyx2d_defs.h"

#include "cdrawable.h"

namespace onyx2d
{

class cLine : public cDrawable
{
    public:
        /**
            Constructor
            @param point1 Vertex of two elements that contain the coordinates of the first point of the line
            @param point2 Vertex of two elements that contain the coordinates of the second point of the line
        */
        cLine(Vector2<int16> point1, Vector2<int16> point2);

        /**
            Constructor
            @param p1_x X coordinate of the first point of the line
            @param p1_y Y coordinate of the first point of the line
            @param p2_x X coordinate of the second point of the line
            @param p2_y Y coordinate of the second point of the line
        */
        cLine(int16 p1_x,int16 p1_y,int16 p2_x,int16 p2_y);


        /** Destructor */
        virtual ~cLine();
    protected:

    private:
        /**
            Function that draws the image
        */
        void Draw();

        /**
            Function that updates the image
        */
        void Update();

        /**
            Function that contain all the geometry
        */
        void Geometry();
};

}
#endif // CLINE_H
