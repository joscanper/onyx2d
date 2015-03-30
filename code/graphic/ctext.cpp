#include "ctext.h"
#include "crendermanager.h"

namespace onyx2d
{


cText::cText()
{
    Text = "";
}

cText::cText(string txt)
{
    Text = txt;
}

cText::~cText()
{
    //dtor
}

void cText::Draw()
{

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(Color.r, Color.g, Color.b, Color.a);

    //Transform();

    //Geometry();

    RenderMngr()->DebugText(Position.x, Position.y, Text);

    glColor3f(1.0f,1.0f,1.0f);

    DrawBoundingBox();

}

void cText::Geometry()
{

    glBegin(GL_QUADS);
        glVertex2f(0.0f,0.0f);
        glVertex2f(0.0f,Size.y);
        glVertex2f(Size.x,Size.y);
        glVertex2f(Size.x,0.0f);
    glEnd();

}


}
