/*

    onyx2d.h File that include all the files for engine use.

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

//Defines
#include "onyx2d_defs.h"

//Core
//#include "core/csingleton.h"
#include "core/ccore.h"
#include "core/cconsole.h"
#include "core/utils/ctimer.h"
#include "core/xml/xml.h"
#include "core/xml/xmlstr.h"
#include "core/utils/gen_func.h"

//Content
#include "core/ccontentmanager.h"

//Graphic
#include "graphic/crendermanager.h"
#include "graphic/ctexture.h"
#include "graphic/cline.h"
#include "graphic/crectangle.h"
#include "graphic/ccircle.h"
#include "graphic/ctriangle.h"
#include "graphic/cshader.h"
#include "graphic/ctextureshader.h"
#include "graphic/cimage.h"
#include "graphic/ccolor.h"
#include "graphic/cfpscounter.h"
#include "graphic/cparticlesystem.h"
#include "graphic/ctext.h"

//Input
#include "input/cinputmanager.h"

//Sound
#include "sound/csoundmanager.h"
#include "sound/csound.h"

//AI
#include "ai/cpathfindingastar.h"

using namespace onyx2d;
