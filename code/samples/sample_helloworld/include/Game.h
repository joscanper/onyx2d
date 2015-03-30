#ifndef GAME_H
#define GAME_H

#include "../../../onyx2d.h"

#include "LifeBar.h"

#define BULLET_SPEED 5

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
        cImage * bg;
        cImage * enemy;
        cImage * player;
        cImage * p_bullet;
        cImage * e_bullet;
        cParticleSystem * ps_engineL;
        cParticleSystem * ps_engineR;

        LifeBar* elifeBar;
        LifeBar* plifeBar;

        cSound * sndLaser1;
        cSound * sndLaser2;
        cSound * sndHurt1;

        vector<cImage*> p_bullets;
        vector<cImage*> e_bullets;

        void Initialize();

        void UpdateBullets();

        void EnemyAI();

        void ShipControl();


};

#endif // GAME_H
