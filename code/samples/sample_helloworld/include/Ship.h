#ifndef CSHIP_H
#define CSHIP_H

#include "../../../onyx2d.h"

// -----------
class cBullet;
class LifeBar;
// -----------

class iShipObserver
{
    public:
        virtual void OnShoot(cBullet* bullet) = 0;
};

class cShip
{
    protected:
        cImage * img_ship;
        LifeBar* lifeBar;
        cImage * bullet;
        cSound * sndShoot;
        iShipObserver * observer;
    public:
        cShip();
        virtual ~cShip();
        virtual void Update() = 0;
        virtual void Hit();
        void SetObserver(iShipObserver * o);
        cImage *GetImage();
};

#endif // CSHIP_H
