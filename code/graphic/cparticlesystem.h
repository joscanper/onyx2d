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


#ifndef CPARTICLESYSTEM_H
#define CPARTICLESYSTEM_H

#include "cdrawable.h"
#include "ctexture.h"
#include "../core/utils/gen_func.h"
#include "../core/math/cvector2.h"
#include "../core/math/cvector4.h"

#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

namespace onyx2d
{

class cParticleSystem : public cDrawable
{
    public:
        Vector2<double> AngleRange;
        Vector2<double> ScaleRange;
        cColor InitColor;
        cColor EndColor;
        Vector2<int16> EnergyRange;
        Vector2<double> XAccelerationRange;
        Vector2<double> YAccelerationRange;
        Vector2<double> XVelocityRange;
        Vector2<double> YVelocityRange;
        Vector2<int16> NumberRange;
        cTexture *Texture;

        /** Constructor */
        cParticleSystem();

        /** Copy Constructor */
        cParticleSystem(cParticleSystem*);

        /** Destructor*/
        virtual ~cParticleSystem();

        void Emit();

        bool Finished();

    protected:
    private:
        class Particle
        {
            public:
                Vector2<int16> PrevPosition;
                Vector3<double> Position;
                Vector2<double> Velocity;
                Vector2<double> Acceleration;
                Vector2<int16> Size;
                double Angle;
                double Scale;
                int InitEnergy;
                int Energy;
                cColor Color;

                Particle();
                ~Particle(){};
                void Update();
                void Draw();
                bool Dead();
        };

        vector<Particle*> m_vParticles;


        /**
            Function that draws the particle system
        */
        void Draw();

        /**
           Function that updates the particle system
        */
        void Update();
};


}
#endif // CPARTICLESYSTEM_H
