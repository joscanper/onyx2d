#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "../../../onyx2d.h"

#include "Ship.h"

class cPlayerShip : public cShip
{
    public:
        cPlayerShip();
        virtual ~cPlayerShip();
        void UpdateControls();
        void Update();
    private:
        cParticleSystem * ps_engineL;
        cParticleSystem * ps_engineR;
};

#endif // PLAYERSHIP_H
