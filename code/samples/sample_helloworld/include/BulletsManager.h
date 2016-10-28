#ifndef CBULLETSMANAGER_H
#define CBULLETSMANAGER_H

// -----------
class cEnemyShip;
class cPlayerShip;
// -----------

#include "Ship.h"

class cBulletsManager : public iShipObserver
{
    public:
        cBulletsManager();
        virtual ~cBulletsManager();
        void Update(cPlayerShip *player, cEnemyShip *enemy);
        void OnShoot(cBullet* bullet);
    private:
        vector<cBullet*> bullets;
};


#endif // CBULLETSMANAGER_H
