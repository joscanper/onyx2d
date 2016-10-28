#ifndef CBULLET_H
#define CBULLET_H

#define BULLET_SPEED 5

#include "../../../onyx2d.h"

// -----------
class cEnemyShip;
class cPlayerShip;
// -----------

class cBullet
{
    protected:
        cImage * image;
    public:
        cBullet();
        virtual ~cBullet();
        virtual bool Update(cPlayerShip * player, cEnemyShip * enemy) = 0;
        void Init(int x,int y)
        {
            image->Position.Set(x, y, 1);
            image->Active = true;
        }
        void Delete()
        {
            image = NULL;
        }
};


// ------------------------------------------ EnemyBullet

class cEnemyBullet : public cBullet
{
    public:
        cEnemyBullet();
        virtual ~cEnemyBullet() {};
        bool Update(cPlayerShip * player, cEnemyShip * enemy);
};

// ------------------------------------------ PlayerBullet

class cPlayerBullet : public cBullet
{
    public:
        cPlayerBullet();
        virtual ~cPlayerBullet() {};
        bool Update(cPlayerShip * player, cEnemyShip * enemy);
};

#endif // CBULLET_H
