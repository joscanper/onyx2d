#include "Bullet.h"

#include "EnemyShip.h"
#include "PlayerShip.h"

cBullet::cBullet()
{
    //ctor
}

cBullet::~cBullet()
{
    //dtor
}

cPlayerBullet::cPlayerBullet()
{
    image = new cImage("content/images/bullet.png");
}

bool cPlayerBullet::Update(cPlayerShip * player, cEnemyShip * enemy) {
    image->Position.y = image->Position.y + BULLET_SPEED;
    if (image->DrawableHit(enemy->GetImage())) // Detects when the bullet hits the enemy
    {
        enemy->Hit();
        return false;
    } else if (image->Position.y > RenderMngr()->DeviceSize().y) {
        return false;
    }
    return true;
}

cEnemyBullet::cEnemyBullet()
{
    image = new cImage("content/images/e_bullet.png");
}
bool cEnemyBullet::Update(cPlayerShip * player, cEnemyShip * enemy) {
        image->Position.y = image->Position.y - BULLET_SPEED;
        if (image->DrawableHit(player->GetImage())) // Detects when the bullet hits the player
        {
            player->Hit();
            return false;
        }else if (image->Position.y < - image->Size.y){
            return false;
        }
        return true;
    }
