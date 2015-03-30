/*

    cParticleSystem - Class that allows particle systems creation and drawing

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

#include "cparticlesystem.h"

namespace onyx2d
{

cParticleSystem::cParticleSystem()
{
    Size.Set(1,1);

    ScaleRange.Set(1.0f,1.0f);
    AngleRange.Set(0.0f,0.0f);

    InitColor.Set(1.0f,1.0f,1.0f,1.0f);
    EndColor.Set(1.0f,1.0f,1.0f,1.0f);

    EnergyRange.Set(20,100);
    XAccelerationRange.Set(0,0);
    YAccelerationRange.Set(0,0);
    XVelocityRange.Set(-1,1);
    YVelocityRange.Set(-1,1);
    NumberRange.Set(5,10);

    Texture = NULL;

    srand(time(NULL));
}

cParticleSystem::cParticleSystem(cParticleSystem* ps)
{
    Copy(ps);

    Size = ps->Size;

    ScaleRange = ps->ScaleRange;
    AngleRange = ps->AngleRange;

    InitColor = ps->InitColor;
    EndColor  = ps->EndColor;

    EnergyRange = ps->EnergyRange;
    XAccelerationRange = ps->XAccelerationRange;
    YAccelerationRange = ps->YAccelerationRange;
    XVelocityRange = ps->XVelocityRange;
    YVelocityRange = ps->YVelocityRange;
    NumberRange = ps->NumberRange;

    Texture = ps->Texture;

    srand(time(NULL));

}

cParticleSystem::~cParticleSystem()
{
    SAFE_RELEASE(Texture);

    for (int i=0; i < m_vParticles.size(); i++)
        SAFE_RELEASE(m_vParticles[i]);

    m_vParticles.clear();
}

bool cParticleSystem::Finished()
{
    if (m_vParticles.empty())
        return true;
    else
        return false;
}

void cParticleSystem::Draw()
{
    glMatrixMode(GL_MODELVIEW);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    //glEnable(GL_COLOR_MATERIAL);

    //glTranslated(Position.x,Position.y,Position.z);
    Transform();

    if (Texture!=NULL)
    {
        glActiveTexture(GL_TEXTURE0_ARB);
        glBindTexture(GL_TEXTURE_2D, Texture->GetID());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Texture->GetSize().x, Texture->GetSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid *)Texture->GetData());

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexEnvi( GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE );

        glEnable(GL_TEXTURE_2D);
    }

    for (int i =0; i< m_vParticles.size(); i++)
    {
        m_vParticles[i]->Draw();
    }


    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_COLOR_MATERIAL);

    Transform();
    DrawBoundingBox();
}

void cParticleSystem::Update()
{

    Angle = 0.0f;

    for (int i=0; i< m_vParticles.size(); i++)
    {
        m_vParticles[i]->Update();

        if (m_vParticles[i]->Dead())
        {
            Particle *par = m_vParticles[i];
            m_vParticles.erase(find(m_vParticles.begin(),m_vParticles.end(),par));
            SAFE_RELEASE(par);
            //cout << "Ha muerto" << endl;
        }

        //Particle color change
        if (m_vParticles[i]->InitEnergy > 0 && InitColor != EndColor)
        {
            m_vParticles[i]->Color.r = InitColor.r - (( m_vParticles[i]->InitEnergy - m_vParticles[i]->Energy) * 1.0f * (InitColor.r - EndColor.r) / (m_vParticles[i]->InitEnergy*1.0f));
            m_vParticles[i]->Color.g = InitColor.g - (( m_vParticles[i]->InitEnergy - m_vParticles[i]->Energy) * 1.0f * (InitColor.g - EndColor.g) / (m_vParticles[i]->InitEnergy*1.0f));
            m_vParticles[i]->Color.b = InitColor.b - (( m_vParticles[i]->InitEnergy - m_vParticles[i]->Energy) * 1.0f * (InitColor.b - EndColor.b) / (m_vParticles[i]->InitEnergy*1.0f));
            m_vParticles[i]->Color.a = InitColor.a - (( m_vParticles[i]->InitEnergy - m_vParticles[i]->Energy) * 1.0f * (InitColor.a - EndColor.a) / (m_vParticles[i]->InitEnergy*1.0f));
        }


    }



}

void cParticleSystem::Emit()
{
    int number = Random(NumberRange[0],NumberRange[1]);

    Vector2<float> AbsPosition = AbsolutePosition();

//   rc = AbsoluteRotationRef();
//    tetha = AbsoluteRotation();

//    Vector2<float> tmp;
//    tmp.x = rc.x+(AbsPosition.x-rc.x)*cos(ToRads(tetha))+(AbsPosition.y-rc.y)*sin(ToRads(tetha));
//    tmp.y = rc.y-(AbsPosition.x-rc.x)*sin(ToRads(tetha))+(AbsPosition.y-rc.y)*cos(ToRads(tetha));

 //   AbsPosition.Set(tmp.x, tmp.y);

    for (int i =0; i< number; i++)
    {
        m_vParticles.push_back(new Particle());

        m_vParticles.back()->InitEnergy = Random(EnergyRange[0],EnergyRange[1]);
        m_vParticles.back()->Energy = m_vParticles.back()->InitEnergy;

        m_vParticles.back()->Acceleration.x = Randomd(XAccelerationRange[0],XAccelerationRange[1]);
        m_vParticles.back()->Acceleration.y = Randomd(YAccelerationRange[0],YAccelerationRange[1]);
        m_vParticles.back()->Velocity.x = Randomd(XVelocityRange[0],XVelocityRange[1]);
        m_vParticles.back()->Velocity.y = Randomd(YVelocityRange[0],YVelocityRange[1]);

        m_vParticles.back()->Position.x = Random(AbsPosition.x,AbsPosition.x+Size.x);
        m_vParticles.back()->Position.y = Random(AbsPosition.y,AbsPosition.y+Size.y);;
        m_vParticles.back()->Position.z = Position.z;

        m_vParticles.back()->Scale = Randomd(ScaleRange[0],ScaleRange[1]);
        m_vParticles.back()->Angle = Randomd(AngleRange[0],AngleRange[1]);

        m_vParticles.back()->Color.Set(InitColor.r,InitColor.g,InitColor.b, InitColor.a);

        if (Texture!=NULL)
            m_vParticles.back()->Size = Texture->GetSize();
        //cout << "P: Energia:" << m_vParticles.back()->Energy << "Posicion : " << m_vParticles.back()->Position.x << "," << m_vParticles.back()->Position.y << endl;
    }


}

// ------------------ Particle -----------------

cParticleSystem::Particle::Particle()
{
    Position.Set(0,0,0);
    Acceleration.Set(0,0);
    Velocity.Set(0,0);
    Energy = 0;
    Size.Set(2,2);
    Color.Set(1.0,1.0,1.0,1.0);
}

void cParticleSystem::Particle::Update()
{
    Velocity += Acceleration;
    Position.x += Velocity.x;
    Position.y += Velocity.y;
    Energy--;
    //cout << Energy << endl;
}

void cParticleSystem::Particle::Draw()
{
    glLoadIdentity();
    glColor4f(Color.r, Color.g, Color.b, Color.a);

    glTranslated(Position.x, Position.y, 0);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
        glVertex2f(-Size.x/2,-Size.y/2);
        glTexCoord2f(0.0f,1.0f);
        glVertex2f(-Size.x/2,(Size.y/2)*Scale);
        glTexCoord2f(1.0f,1.0f);
        glVertex2f((Size.x/2)*Scale,(Size.y/2)*Scale);
        glTexCoord2f(1.0f,0.0f);
        glVertex2f((Size.x/2)*Scale,-Size.y/2);
       /* glVertex3f( (Position.x/RenderMngr()->DeviceSize().x) ,
                    (Position.y/RenderMngr()->DeviceSize().y), 0.0f);
        glVertex3f( (Position.x/RenderMngr()->DeviceSize().x) +  ((Position.x+Size.x)/RenderMngr()->DeviceSize().x),
                    (Position.y/RenderMngr()->DeviceSize().y), 0.0f);
        glVertex3f( (Position.x/RenderMngr()->DeviceSize().x) +  ((Position.x+Size.x)/RenderMngr()->DeviceSize().x),
                    (Position.y/RenderMngr()->DeviceSize().y) +  ((Position.y+Size.y)/RenderMngr()->DeviceSize().y), 0.0f);
        glVertex3f( (Position.x/RenderMngr()->DeviceSize().x) ,
                    (Position.y/RenderMngr()->DeviceSize().y) +  ((Position.y+Size.y)/RenderMngr()->DeviceSize().y), 0.0f);*/
    glEnd();

}

bool cParticleSystem::Particle::Dead()
{
    if (Energy<=0)
        return true;
    else
        return false;
}



}
