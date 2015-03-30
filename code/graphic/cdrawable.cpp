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

#include "cdrawable.h"
#include "crendermanager.h"
#include "../input/cinputmanager.h"

namespace onyx2d
{

cDrawable::cDrawable()
{
    Position.SetZero();
    RotationRef.SetZero();
    Color.Set(1.0f,1.0f,1.0f,1.0f);
    Angle = 0.0f;
    BoundingBox = false;
    Size.SetZero();
    Area = false;

    pParent = NULL;

    RenderMngr()->m_vDrawables.push_back(this);
}

cDrawable::cDrawable(cDrawable* dw)
{
    Copy(dw);

    RenderMngr()->m_vDrawables.push_back(this);

}

cDrawable::~cDrawable()
{

}

void cDrawable::Copy(cDrawable* dw)
{
    Position = dw->Position;
    RotationRef = dw->RotationRef;
    Color = dw->Color;
    Angle = dw->Angle;
    BoundingBox = dw->BoundingBox;
    Area = dw->Area;
    Size = dw->Size;
    pParent = dw->pParent;
    vChildren = vChildren;

}

void cDrawable::Delete()
{
    RenderMngr()->DeleteDrawable(this);
}

bool cDrawable::MouseHit(int button)
{

    if (InputMngr()->MousePosition().x > Position.x && InputMngr()->MousePosition().y > Position.y)
        if (InputMngr()->MousePosition().x < Position.x+Size.x && InputMngr()->MousePosition().y < Position.y+Size.y)
            if (InputMngr()->MouseHit(button))
                return true;

    return false;
}

bool cDrawable::DrawableHit(cDrawable* obj)
{
    Vector2<float> depth = cRect::GetIntersectionDepth(this->Rect(), obj->Rect());
    if (depth.x > 0 || depth.y > 0)
        return true;

    return false;
}

cRect cDrawable::Rect()
{
    return cRect(this->Position.x, this->Position.y, this->Size.x, this->Size.y);
}

void cDrawable::DrawBoundingBox()
{
   // glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (pParent != NULL)
    {
        pParent->Transform();
    }

    glTranslated(Position.x,Position.y,0);

    glColor3f(1.0f,1.0f,1.0f);

    Vector2<float> points[4];
    points[0].Set(0,0);
    points[1].Set(Size.x,0);
    points[2].Set(Size.x,Size.y);
    points[3].Set(0,Size.y);

	Vector2<float> new_points[4];
    new_points[0] = points[0];
    new_points[1] = points[1];
    new_points[2] = points[2];
    new_points[3] = points[3];

    if (Angle!=0)
    {
        //Here we rotates each vertex
        points[0] = RenderMngr()->RotateCoordinates(points[0], Angle, RotationRef);

        Vector2<float> minp(points[0]);
        Vector2<float> maxp(points[0]);

        for (int i=1; i<4 ; i++)
        {

            points[i] = RenderMngr()->RotateCoordinates(points[i], Angle, RotationRef);

			if (points[i].x > maxp.x)
                maxp.x = points[i].x;
            else if (points[i].x < minp.x)
                minp.x = points[i].x;

            if (points[i].y > maxp.y)
                maxp.y = points[i].y;
            else if (points[i].y < minp.y)
                minp.y = points[i].y;
        }


        new_points[0].Set(minp.x,minp.y);
        new_points[1].Set(minp.x,maxp.y);
        new_points[2].Set(maxp.x,maxp.y);
        new_points[3].Set(maxp.x,minp.y);

    }

    if (BoundingBox)
    {
        glBegin(GL_LINE_STRIP);
            glVertex2f(new_points[0].x,new_points[0].y);
            glVertex2f(new_points[1].x,new_points[1].y);
            glVertex2f(new_points[2].x,new_points[2].y);
            glVertex2f(new_points[3].x,new_points[3].y);
            glVertex2f(new_points[0].x,new_points[0].y);
        glEnd();
    }

    if (Area)
    {
        glBegin(GL_LINE_STRIP);
            glVertex2f(points[0].x,points[0].y);
            glVertex2f(points[1].x,points[1].y);
            glVertex2f(points[2].x,points[2].y);
            glVertex2f(points[3].x,points[3].y);
            glVertex2f(points[0].x,points[0].y);
        glEnd();
    }

}

void cDrawable::Update()
{
    if (Angle > 360.0f)
        Angle = Angle - 360.0f;
}

void cDrawable::Transform()
{
    if (pParent != NULL)
    {
        pParent->Transform();
    }

    glTranslated(Position.x,Position.y,0);
	glTranslatef(RotationRef.x, RotationRef.y, 0.0f);
    glRotatef(-Angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-RotationRef.x, -RotationRef.y, 0.0f);
}


Vector2<float> cDrawable::AbsolutePosition()
{
    Vector2<float> pos;
    pos.x = Position.x;
    pos.y = Position.y;

    cDrawable* parent = pParent;
    while (parent != NULL)
    {

        pos = RenderMngr()->RotateCoordinates(pos,parent->Angle, parent->RotationRef);

        pos.x += parent->Position.x;
        pos.y += parent->Position.y;

        parent = parent->pParent;

    }



//    cout << pos.x << "--" << pos.y << endl;
    return pos;

}

void cDrawable::Resize(Vector2<float> size)
{
    Size.Set(size.x, size.y);
    for (int i=0; i < vChildren.size(); i++)
        vChildren[i]->Resize(size);
}

void cDrawable::AddChild(cDrawable* obj)
{
    this->vChildren.push_back(obj);
}

void cDrawable::RemoveChild(cDrawable* obj)
{
    this->vChildren.erase(std::find(vChildren.begin(), vChildren.end(), obj));
}

void cDrawable::SetParent(cDrawable* obj)
{
    if (pParent != NULL)
        this->pParent->RemoveChild(this);
    this->pParent = obj;
    this->pParent->AddChild(this);
}

/*
float AbsoluteRotation()
{

}

Vector2<float> AbsoluteRotationRef()
{

}
*/
}
