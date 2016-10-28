#include "EnemyShip.h"

#include "Bullet.h"
#include "LifeBar.h"

cEnemyShip::cEnemyShip()
{
    // Enemy Ship
    img_ship = new cImage("content/images/enemy_ship.png");
    img_ship->Position.Set(RenderMngr()->DeviceSize().x / 2, RenderMngr()->DeviceSize().y - 100 , 1);

    // LifeBars
    lifeBar = new LifeBar(cColor(1,0,0,1));
    lifeBar->SetParent(img_ship);
    lifeBar->Position.Set(20, 70, 0);

    sndShoot = new cSound("content/sounds/laser1.wav");
}

cEnemyShip::~cEnemyShip()
{
    //dtor
}

void cEnemyShip::Update()
{
    static cTimer timer_bullet;
    static cTimer timer_change;
    static int time = 200;
    /*
    if (player->Position.x > img_ship->Position.x)
        img_ship->Position.x += 2;
    if (player->Position.x < img_ship->Position.x)
        img_ship->Position.x -= 2;
    */
    if (timer_bullet.GetElapsedTimeInMilliSec() > time)
    {
        cEnemyBullet* new_bullet = new cEnemyBullet();
        new_bullet->Init(img_ship->Position.x + 31,img_ship->Position.y - 15);
        observer->OnShoot(new_bullet);
        timer_bullet.Start();

        sndShoot->Play();
    }

    if (timer_change.GetElapsedTimeInSec() > Random(2,4))
    {
        if (time==1000)
            time = 200;
        else
            time = 1000;
        timer_change.Start();
    }
}
