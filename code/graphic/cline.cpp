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

#include "cline.h"

namespace onyx2d
{


cLine::cLine(Vector2<int16> point1, Vector2<int16> point2)
{
    cLine(point1.x, point1.y, point2.x, point2.y);
}

cLine::cLine(int16 p1_x, int16 p1_y, int16 p2_x, int16 p2_y)
{
    Position.x = p1_x;
    Position.y = p1_y;
    Size.Set(p2_x-p1_x, p2_y-p1_y);
}

cLine::~cLine()
{
    //dtor
}

void cLine::Draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    Transform();

    glColor4f(Color.r, Color.g, Color.b, Color.a);

    Geometry();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glDisable(GL_BLEND);

    //DrawBoundingBox();
}

void cLine::Update()
{

}

void cLine::Geometry()
{
    glBegin(GL_LINES );
        glVertex2f(0.0f,0.0f);
        glVertex2f(Size.x,Size.y);
    glEnd();

}

}
