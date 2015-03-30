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

#ifndef CIMAGE_H
#define CIMAGE_H

#include "../onyx2d_defs.h"
#include "../core/math/cvector2.h"

#include "cshading.h"
#include "ctexture.h"
#include "ctextureshader.h"

#include <algorithm>

namespace onyx2d
{

class cImage : public cShading
{
    public:
        /** Default constructor */
        cImage();

        /**
            Constructor that accept a file path and loads the image.
            @param path Path of the image file.
        */
        cImage(string path);

        /**
            Constructor that accept a texture object.
            @param tex Texture object.
        */
        cImage(cTexture *tex);

        /**
            Copy Constructoy
            @param img Other image
        */
        cImage(cImage*);

        /** Destructor */
        virtual ~cImage();

        /**
            Function that loads a image.
            @param path Path of the image file.
            @return <i>true</i> if loads the image correctly, <i>false</i> in other case.
        */
        bool Load(string path);

    protected:
    private:
        cTexture* m_pTexture;         //! Texture that allows image data
        cTextureShader* m_pShader;    //! Basic shader used to draw the image

        /**
            Function that draws the image
        */
        void Draw();

        /**
            Function that updates the image
        */
        void Update();

        /**
            Function that contain all the geometry
        */
        void Geometry();
};

}
#endif // CIMAGE_H
