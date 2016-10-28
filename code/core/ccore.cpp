/*

    cCore - Class that controls all the engine

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

#include "ccore.h"

#include "../graphic/crendermanager.h"
#include "../input/cinputmanager.h"
#include "../sound/csoundmanager.h"
#include "utils/ctimer.h"
#include "ccontentmanager.h"
#include "cconsole.h"



namespace onyx2d
{


cCore::cCore()
{
    //ctor
}

cCore::~cCore()
{
    //dtor
}

bool cCore::Init(string log_file)
{
   // MemLeaks::MemoryBegin();
    RenderMngr();
    SoundMngr();
    InputMngr()->Init();
    ContentMngr();

    //Initialize the console
    Console()->Init(0,0);


    return true;
}

void cCore::Update()
{
    cTimer *timer = new cTimer();
    timer->Start();

    /* Here we update all the managers */
    RenderMngr()->Update();

    while (timer->GetElapsedTimeInMilliSec() < (1000/_framerate));
    timer->Stop();
    SAFE_RELEASE(timer);
}

void cCore::Dispose()
{

    RenderMngr()->DeviceEnd();
   // MemLeaks::MemoryEnd();
    //PrintMemoryLeakInfo();
}


void cCore::SetFramerate(int fps)
{
    _framerate = fps;
}

int cCore::GetFramerate()
{
    return _framerate;
}

}//namespace onyx2d
