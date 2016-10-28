#include "PlayerShip.h"

#include "Bullet.h"
#include "LifeBar.h"

cPlayerShip::cPlayerShip()
{
    // Player Ship
    img_ship = new cImage("content/images/ship.png");
    img_ship->Position.Set(RenderMngr()->DeviceSize().x / 2,50,1);

    // Particles systems of player ship engine
    ps_engineL = new cParticleSystem();
    ps_engineL->EnergyRange.Set(5,15);
    ps_engineL->NumberRange.Set(5,8);
    ps_engineL->SetParent(img_ship);
    ps_engineL->Position.Set(15,-8,1);
    ps_engineL->Size.Set(10,10);
    ps_engineL->YVelocityRange.Set(-2,-2);
    ps_engineL->YAccelerationRange.Set(-0.02f,-0.02f);
    ps_engineL->XVelocityRange.Set(-0.5f,0.5f);
    ps_engineL->InitColor.Set(1.0f,1.0f,0.0f,1.0f);
    ps_engineL->EndColor.Set(1.0f,0.0f,0.0f,0.0f);

    ps_engineR = new cParticleSystem(ps_engineL);
    ps_engineR->Position.Set(47,-8,1);


    lifeBar = new LifeBar(cColor(0,1,0,1));
    lifeBar->Position.Set(RenderMngr()->DeviceSize().x / 2 - 100, 20, 0);
    lifeBar->Resize(Vector2<float>(200, 10));

    // Bullets of the player ship
    bullet = new cImage("content/images/bullet.png");
    bullet->Active = false;

    sndShoot = new cSound("content/sounds/laser2.wav");
}

cPlayerShip::~cPlayerShip()
{
    img_ship = NULL;
    ps_engineR = NULL;
    ps_engineL = NULL;
}

void cPlayerShip::UpdateControls()
{
    // Movement keys
    if (InputMngr()->KeyDown(Keys::Left) && img_ship->Position.x > 0)
    {
        img_ship->Position.x -= 5;
        img_ship->Angle = -10;
    }


    if (InputMngr()->KeyDown(Keys::Right) && (img_ship->Position.x + img_ship->Size.x) < RenderMngr()->DeviceSize().x)
    {
        img_ship->Position.x += 5;
        img_ship->Angle = 10;
    }

    // Shooting key
    if (InputMngr()->KeyHit(Keys::Space))
    {
        cPlayerBullet* new_bullet = new cPlayerBullet();
        new_bullet->Init(img_ship->Position.x + 31,img_ship->Position.y + 50);
        observer->OnShoot(new_bullet);

        sndShoot->Play();
    }
}

void cPlayerShip::Update()
{
    img_ship->Angle = 0;
}
