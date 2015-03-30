/*

    cImage - Class that allows image loading and drawing

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

#ifndef CTEXT_H
#define CTEXT_H

#include "../onyx2d_defs.h"
#include "cdrawable.h"

#include <string>

using namespace std;

namespace onyx2d
{

class cText : public cDrawable
{
    public:
        string Text;

        /** Default constructor */
        cText();

        /**
            Constructor
            @param txt Text to show
        */
        cText(string txt);


        /** Destructor */
        virtual ~cText();

    protected:
    private:
        /**
            Function that draws the image
        */
        void Draw();

        /**
            Function that updates the image
        */
        void Update(){};

        /**
            Function that contain all the geometry
        */
        void Geometry();
};

}

#endif // CTEXT_H
