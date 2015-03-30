#include "../include/Game.h"

Game::Game()
{
    Initialize();
}

Game::~Game()
{

}

void Game::Dispose()
{
    bg->Delete();
    enemy->Delete();
    player->Delete();
    p_bullet->Delete();
    e_bullet->Delete();
    ps_engineL->Delete();
    ps_engineR->Delete();
    elifeBar->Delete();
    plifeBar->Delete();

    cout << "TERMINAOD";
}

void Game::Initialize()
{

    // Background
    bg = new cImage("content/images/space_bg.png");
    bg->Position.Set(0,0,-1);

    // Player Ship
    player = new cImage("content/images/ship.png");
    player->Position.Set(RenderMngr()->DeviceSize().x / 2,50,1);

    // Particles systems of player ship engine
    ps_engineL = new cParticleSystem();
    ps_engineL->EnergyRange.Set(5,15);
    ps_engineL->NumberRange.Set(5,8);
    ps_engineL->SetParent(player);
    ps_engineL->Position.Set(15,-8,1);
    ps_engineL->Size.Set(10,10);
    ps_engineL->YVelocityRange.Set(-2,-2);
    ps_engineL->YAccelerationRange.Set(-0.02f,-0.02f);
    ps_engineL->XVelocityRange.Set(-0.5f,0.5f);
    ps_engineL->InitColor.Set(1.0f,1.0f,0.0f,1.0f);
    ps_engineL->EndColor.Set(1.0f,0.0f,0.0f,0.0f);

    ps_engineR = new cParticleSystem(ps_engineL);
    ps_engineR->Position.Set(47,-8,1);

    // Enemy Ship
    enemy = new cImage("content/images/enemy_ship.png");
    enemy->Position.Set(RenderMngr()->DeviceSize().x / 2, RenderMngr()->DeviceSize().y - 100 , 1);

    // LifeBars
    elifeBar = new LifeBar(cColor(1,0,0,1));
    elifeBar->SetParent(enemy);
    elifeBar->Position.Set(20, 70, 0);

    plifeBar = new LifeBar(cColor(0,1,0,1));
    plifeBar->Position.Set(RenderMngr()->DeviceSize().x / 2 - 100, 20, 0);
    plifeBar->Resize(Vector2<float>(200, 10));

    // Bullets of the player ship
    p_bullet = new cImage("content/images/bullet.png");
    p_bullet->Active = false;

    // Bullets of enemy ship
    e_bullet = new cImage("content/images/e_bullet.png");
    e_bullet->Active = false;

    // Texts of the game
    cText *txt = new cText("Player points : ");
    txt->Position.Set(10, RenderMngr()->DeviceSize().y - 20,2);
    cText *txt2 = new cText("Enemy points : ");
    txt2->Position.Set(RenderMngr()->DeviceSize().x - 200, RenderMngr()->DeviceSize().y - 20,2);

    cFPSCounter* fps = new cFPSCounter();
    fps->Position.Set(5, 5, 0);

    // Game sounds
    sndLaser1 = new cSound("content/sounds/laser1.wav");
    sndLaser2 = new cSound("content/sounds/laser2.wav");
    sndHurt1 = new cSound("content/sounds/hit.wav");

}



void Game::Update(bool &done)
{
    player->Angle = 0;

    ShipControl();

    ps_engineL->Emit();
    ps_engineR->Emit();

    // Key that close the window
    if (InputMngr()->KeyHit(Keys::Escape))
        done = true;

    // Updates enemy actions
    EnemyAI();

    UpdateBullets();

}


void Game::ShipControl()
{
    // Movement keys
    if (InputMngr()->KeyDown(Keys::Left) && player->Position.x > 0)
    {
        player->Position.x -= 5;
        player->Angle = -10;
    }


    if (InputMngr()->KeyDown(Keys::Right) && (player->Position.x + player->Size.x) < RenderMngr()->DeviceSize().x)
    {
        player->Position.x += 5;
        player->Angle = 10;
    }

    // Shooting key
    if (InputMngr()->KeyHit(Keys::Space))
    {
        cImage* new_bullet = new cImage(p_bullet);
        new_bullet->Position.Set(player->Position.x + 31,player->Position.y + 50, 1);
        new_bullet->Active = true;
        p_bullets.push_back(new_bullet);

        sndLaser1->Play();
    }
}

void Game::UpdateBullets()
{

    // TODO - Detectar que balas colisionan entre ellas

    // This pdates player bullets
    for (std::vector<cImage*>::iterator it = p_bullets.begin() ; it != p_bullets.end(); ++it)
    {
        cImage* bullet = (*it);
        bullet->Position.y = bullet->Position.y + BULLET_SPEED;

        if (bullet->DrawableHit(enemy)) // Detects when the bullet hits the enemy
        {
            elifeBar->Decrease(10);
            sndHurt1->Play();
            p_bullets.erase(it--);
            bullet->Delete();

        } else if (bullet->Position.y > RenderMngr()->DeviceSize().y) {
            p_bullets.erase(it--);
            bullet->Delete();
        }
    }

    // This updates enemy bullets
    for (std::vector<cImage*>::iterator it = e_bullets.begin() ; it != e_bullets.end(); ++it)
    {
        cImage* bullet = (*it);
        bullet->Position.y = bullet->Position.y - BULLET_SPEED;
        if (bullet->DrawableHit(player)) // Detects when the bullet hits the player
        {
            plifeBar->Decrease(10);
            e_bullets.erase(it--);
            bullet->Delete();
        }else if (bullet->Position.y < - bullet->Size.y)
        {
            e_bullets.erase(it--);
            bullet->Delete();
        }
    }

}


void Game::EnemyAI()
{
    static cTimer timer_bullet;
    static cTimer timer_change;
    static int time = 200;

    if (player->Position.x > enemy->Position.x)
        enemy->Position.x += 2;
    if (player->Position.x < enemy->Position.x)
        enemy->Position.x -= 2;

    if (timer_bullet.GetElapsedTimeInMilliSec() > time)
    {
        cImage* new_bullet = new cImage(e_bullet);
        new_bullet->Position.Set(enemy->Position.x + 31,enemy->Position.y - 15, 1);
        new_bullet->Active = true;
        e_bullets.push_back(new_bullet);
        timer_bullet.Start();

        sndLaser2->Play();
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
