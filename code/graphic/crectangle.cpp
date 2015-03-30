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

#include "crectangle.h"
#include "crendermanager.h"


namespace onyx2d
{

cRectangle::cRectangle()
{
    //ctor

}

cRectangle::cRectangle(cRectangle* rc)
{
    Copy(rc);

}

cRectangle::cRectangle(uint16 x, uint16 y, uint16 width, uint16 height)
{
    Position.x = x;
    Position.y = y;

    Size.x = width;
    Size.y = height;
}

cRectangle::~cRectangle()
{
    //dtor
}

void cRectangle::Draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glColor4f(Color.r, Color.g, Color.b, Color.a);

    Transform();

    Geometry();

    glDisable(GL_BLEND);

    DrawBoundingBox();
}

void cRectangle::Geometry()
{
    glBegin(GL_QUADS);
        glVertex2f(0.0f,0.0f);
        glVertex2f(0.0f,Size.y);
        glVertex2f(Size.x,Size.y);
        glVertex2f(Size.x,0.0f);
    glEnd();

}
}
