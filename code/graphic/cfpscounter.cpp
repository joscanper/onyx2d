/*

    cFPSCounter - Simple class that draws a FPS counter

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

#include "cfpscounter.h"
#include "crendermanager.h"

namespace onyx2d
{

cFPSCounter::cFPSCounter()
{
     count = 0;
     elapsedTime = 0.0;

}

cFPSCounter::~cFPSCounter()
{
    //dtor
}

void cFPSCounter::Draw()
{

        // set to 2D orthogonal projection
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();                   // reset projection matrix

        Transform();

        glColor3f(Color.r,Color.g,Color.b);

        // update fps every second
        elapsedTime = m_pFPSTimer.GetElapsedTime();
        if(elapsedTime < 1.0)
        {
                ++count;
        }
        else
        {
                ss = "";
                char num[5];
                itoa((count / elapsedTime),num,10);
                ss += num;
                ss += " FPS"; // update fps string
                //ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
                count = 0;                      // reset counter
                m_pFPSTimer.Start();                  // restart timer
        }

        RenderMngr()->DebugText(Position.x, Position.y,ss.c_str());

        glColor3f(1.0f,1.0f,1.0f);

}

}
