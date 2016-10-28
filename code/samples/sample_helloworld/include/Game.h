#ifndef GAME_H
#define GAME_H

#include "../../../onyx2d.h"

#include "EnemyShip.h"
#include "PlayerShip.h"
#include "BulletsManager.h"

using namespace onyx2d;

class Game
{
    public:
        Game();
        virtual ~Game();
        void Update(bool &done);
        void Dispose();
    protected:
    private:
        cPlayerShip * player;
        cEnemyShip * enemy;
        cBulletsManager * bullets;

        cImage * bg;

        void Initialize();

};

#endif // GAME_H
