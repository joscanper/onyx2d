#include "ccircle.h"
namespace onyx2d
{

cCircle::cCircle(int16 x, int16 y, float radius)
{
    Position.x = x;
    Position.y = y;
    Size.x = radius;
    Size.y = radius;
}


cCircle::~cCircle()
{
    //dtor
}

void cCircle::Draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glTranslated(Position.x,Position.y,0);

    Transform();

    glColor4f(Color.r, Color.g, Color.b, Color.a);

    Geometry();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glDisable(GL_BLEND);

    //DrawBoundingBox();
}

void cCircle::Update()
{

}

void cCircle::Geometry()
{
    float angle=360.0f;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(Size.x/2,Size.y/2);
        while (angle>=0)
        {
            glVertex2f((cos(ToRads(angle))*(Size.x/2))+Size.x/2,(sin(ToRads(angle))*(Size.y/2))+Size.y/2);
            angle-=12.0f;
        }
        glVertex2f((cos(0.0f)*(Size.x/2))+Size.x/2,(sin(0.0f)*(Size.y/2))+Size.y/2);
    glEnd();

}

}
