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


#include "cimage.h"

namespace onyx2d
{

cImage::cImage()
{
    m_pShader  = new cTextureShader();
    PushShader(m_pShader);
}

cImage::cImage(cImage* img)
{
    Copy(img);
    m_pTexture = img->m_pTexture;
    m_pShader = img->m_pShader;
}

cImage::cImage(string path)
{
    m_pTexture = new cTexture(path);
    m_pShader  = new cTextureShader();

    PushShader(m_pShader);

    Size.Set(m_pTexture->GetSize().x,m_pTexture->GetSize().y);

    /* Set rotation reference point */
    RotationRef.x = m_pTexture->GetSize().x/2;
    RotationRef.y = m_pTexture->GetSize().y/2;
}

cImage::cImage(cTexture *tex)
{
    m_pTexture = tex;
    m_pShader  = new cTextureShader();

    PushShader(m_pShader);

    Size.Set(m_pTexture->GetSize().x,m_pTexture->GetSize().y);

    /* Set rotation reference point */
    RotationRef.x = m_pTexture->GetSize().x/2;
    RotationRef.y = m_pTexture->GetSize().y/2;
}

bool cImage::Load(string path)
{

    m_pTexture->Load(path);
	return true;
}

cImage::~cImage()
{

    SAFE_RELEASE(m_pTexture);
    SAFE_RELEASE(m_pShader);
}

void cImage::Update()
{

    if (m_vShaders.empty())
        PushShader(m_pShader);

}

void cImage::Draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glActiveTexture(GL_TEXTURE0_ARB);
    glBindTexture(GL_TEXTURE_2D, m_pTexture->GetID());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_pTexture->GetSize().x, m_pTexture->GetSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid *)m_pTexture->GetData());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexEnvi( GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    Transform();

    glColor4f(Color.r, Color.g, Color.b, 1.0f);

    m_pShader->Alpha = Color.a;

    for(int i = 0; i< m_vShaders.size(); i++)
    {
        m_vShaders[i]->Begin();
        Geometry();
        m_vShaders[i]->End();
    }

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    DrawBoundingBox();
}

void cImage::Geometry()
{

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
        glVertex2f(0.0f,0.0f);
        glTexCoord2f(0.0f,1.0f);
        glVertex2f(0.0f,Size.y);
        glTexCoord2f(1.0f,1.0f);
        glVertex2f(Size.x,Size.y);
        glTexCoord2f(1.0f,0.0f);
        glVertex2f(Size.x,0.0f);
    glEnd();


}

}
