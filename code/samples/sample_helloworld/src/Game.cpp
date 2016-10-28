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
    /*
    enemy->Delete();
    player->Delete();
    p_bullet->Delete();
    e_bullet->Delete();
    ps_engineL->Delete();
    ps_engineR->Delete();
    elifeBar->Delete();
    plifeBar->Delete();
    */
}

void Game::Initialize()
{
    player = new cPlayerShip();
    enemy = new cEnemyShip();
    bullets = new cBulletsManager();

    player->SetObserver(bullets);
    enemy->SetObserver(bullets);

    // Background
    bg = new cImage("content/images/space_bg.png");
    bg->Position.Set(0,0,-1);

    // Texts of the game
    cText *txt = new cText("Player points : ");
    txt->Position.Set(10, RenderMngr()->DeviceSize().y - 20,2);
    cText *txt2 = new cText("Enemy points : ");
    txt2->Position.Set(RenderMngr()->DeviceSize().x - 200, RenderMngr()->DeviceSize().y - 20,2);

    cFPSCounter* fps = new cFPSCounter();
    fps->Position.Set(5, 5, 0);

    // Game sounds

  //  sndHurt1 = new cSound("content/sounds/hit.wav");

}



void Game::Update(bool &done)
{
    player->UpdateControls();

    bullets->Update(player, enemy);
    player->Update();
    enemy->Update();

    // Key that close the window
    if (InputMngr()->KeyHit(Keys::Escape))
        done = true;
}


