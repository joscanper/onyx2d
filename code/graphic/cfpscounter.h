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

#ifndef CFPSCOUNTER_H
#define CFPSCOUNTER_H

#include "cdrawable.h"
#include "../onyx2d_defs.h"

#include "../core/utils/ctimer.h"

#include <string>
#include <iostream>

using namespace std;

namespace onyx2d
{

class cFPSCounter : public cDrawable
{
    private:
        int count;
        string ss;
        double elapsedTime;
        cTimer m_pFPSTimer;
    public:
        /** Default constructor */
        cFPSCounter();

        /** Destructor */
        virtual ~cFPSCounter();
    protected:
    private:
        /**
            Function that draws the image
        */
        void Draw();
};

}

#endif // CFPSCOUNTER_H
