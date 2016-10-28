#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "../../../onyx2d.h"

#include "Ship.h"

class cEnemyShip : public cShip
{
    public:
        cEnemyShip();
        virtual ~cEnemyShip();
        void Update();
    protected:

    private:

};

#endif // ENEMYSHIP_H
