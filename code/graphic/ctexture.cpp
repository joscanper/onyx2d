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


#include "ctexture.h"
#include "..\core\cconsole.h"

namespace onyx2d
{

cTexture::cTexture(cTexture* tex)
{
    m_sPath = tex->m_sPath;
    m_vSize = tex->m_vSize;
    m_uTextureID = tex->m_uTextureID;
    m_uTextureList = tex->m_uTextureList;
    m_cTexture = tex->m_cTexture;
}

cTexture::cTexture(string path)
{
    Load(path);
}

bool cTexture::Load(string path)
{

    m_sPath = path;

    //Check if the file exist
    fstream fp(path.c_str());
    if (!fp)
    {
        string log_str = "cTexture : File not found : " + path;
        Console()->AddRecord(log_str, RecordType::Error);
        return false;
    }else{
        fp.close();
    }

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str(),0);//Automatocally detects the format(from over 20 formats!)
    FIBITMAP* image = FreeImage_Load(format, path.c_str());

    FIBITMAP* temp = image;


    image = FreeImage_ConvertTo32Bits(image);

    if (!image)
    {
        string log_str = "cTexture : Error loading texture : " + path;
        Console()->AddRecord(log_str, RecordType::Error);
        return false;
    }

    FreeImage_SetTransparent(image, true);
    FreeImage_Unload(temp);

    m_vSize.x  = FreeImage_GetWidth(image);
    m_vSize.y  = FreeImage_GetHeight(image);


    //FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
    m_cTexture = new GLubyte[4* m_vSize.x* m_vSize.y];
    char* pixels = (char*)FreeImage_GetBits(image);
    for(int j= 0; j< m_vSize.x* m_vSize.y; j++){
        m_cTexture[j*4+0]= pixels[j*4+2];
        m_cTexture[j*4+1]= pixels[j*4+1];
        m_cTexture[j*4+2]= pixels[j*4+0];
        m_cTexture[j*4+3]= pixels[j*4+3];
    }


    //Now generate the OpenGL texture object
    glGenTextures(1, &m_uTextureID);
    glBindTexture(GL_TEXTURE_2D, m_uTextureID);

    glNewList(m_uTextureList = glGenLists(1), GL_COMPILE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
    glTexEnvi( GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE );


    // Define the 2D texture image.
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
                         m_vSize.x,
                         m_vSize.y,
                        0, GL_RGBA,GL_UNSIGNED_BYTE,
                        (GLvoid*)m_cTexture );

    glEndList();


    GLenum wasError = glGetError();
    if(wasError){
        string log_str = "cTexture : Error generating texture : " + path;
        Console()->AddRecord(log_str, RecordType::Error);
        return false;
    }
}

cTexture::~cTexture()
{
    //dtor
}

}
