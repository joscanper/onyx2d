/*

    onyx2d_defs.h File that contains all the includes used by the engine
    and all the defines.

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

#pragma once

#ifndef ONYX2D_DEFS_H_
#define ONYX2D_DEFS_H_

#define ONYX2D_VERSION "0.1"

#ifdef _WIN32	
	#include <windows.h>  
#endif 

#include "3rdparty/GL/GLee.h"

#ifdef _WIN32		
    #include "3rdparty/GL/wglext.h"
#else
    #include "3rdparty/GL/glext.h"
#endif
#include <GL/gl.h>

#define FREEGLUT_BUILDING_LIB
#include "3rdparty/GL/freeglut.h"

#include "core/utils/types.h"
#include <cstdlib>

#define SAFE_RELEASE(x) do{if(x) { free(x); x = NULL; }}while(0)

#endif// ONYX2D_DEFS_H_
