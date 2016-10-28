#include "BulletsManager.h"

#include "Bullet.h"

cBulletsManager::cBulletsManager()
{
    //ctor
}

cBulletsManager::~cBulletsManager()
{
    //dtor
}

void cBulletsManager::OnShoot(cBullet* bullet)
{
    bullets.push_back(bullet);
}

void cBulletsManager::Update(cPlayerShip *player, cEnemyShip *enemy)
{
    // TODO - Detectar que balas colisionan entre ellas

    // This pdates player bullets
    for (std::vector<cBullet*>::iterator it = bullets.begin() ; it != bullets.end(); ++it)
    {
        cBullet* bullet = (*it);
        bool alive = bullet->Update(player, enemy);
        if (!alive)
        {
            bullets.erase(it--);
            bullet->Delete();
        }
    }

}
