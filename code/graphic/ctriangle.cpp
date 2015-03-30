#include "ctriangle.h"

namespace onyx2d
{

cTriangle::cTriangle(uint16 x, uint16 y, uint16 width, uint16 height)
{
    Position.x = x;
    Position.y = y;
    Size.Set(width,height);
}

cTriangle::~cTriangle()
{
    //dtor
}

void cTriangle::Draw()
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

void cTriangle::Update()
{

}

void cTriangle::Geometry()
{
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f,0.0f);
        glVertex2f(Size.x/2,Size.y);
        glVertex2f(Size.x,0.0f);
    glEnd();

}

}
