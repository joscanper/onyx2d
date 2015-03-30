/*

    cTexture - Class that loads and contain texture data

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


#ifndef CTEXTURE_H
#define CTEXTURE_H

#include "../onyx2d_defs.h"

#include "../3rdparty/freeimage.h"
#include "../core/math/cvector2.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;
namespace onyx2d
{

class cTexture
{
    public:
        /** Default constructor. */
        cTexture(){}

        /**
           Copy constructor.
           @param tex Other Texture
        */

        cTexture(cTexture* tex);

        /**
            Constructor that accept a file path and loads the image.
            @param file Path of the image file.
        */
        cTexture(string file);

        /** Destructor. */
        virtual ~cTexture();

        /**
            Function that loads a image.
            @param file Path of the image file.
            @return <i>true</i> if loads the image correctly, <i>false</i> in other case.
        */
        bool Load(string file);

        /**
            Function that returns OpenGL texture ID.
            @return Texture ID.
        */
        GLuint GetID(){ return m_uTextureID; };

        /**
            Function that returns the texture size.
            @return Vector of two elements that contain the texture size.
        */
        Vector2<int16> GetSize(){ return m_vSize; };

        /**
            Function that returns the texture data.
            @return Array with the texture data.
        */
        GLubyte* GetData(){ return m_cTexture; };

    protected:
    private:
        string m_sPath;         //! Path of the image.
        Vector2<int16> m_vSize; //! Size of the image.
        GLuint m_uTextureID;    //! OpenGL texture ID.
        GLuint m_uTextureList;  //! OpenGL texture display list.
        GLubyte* m_cTexture;    //! Texture data.

};

}
#endif // CTEXTURE_H
