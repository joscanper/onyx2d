#include <iostream>
#include "../../onyx2d.h"

using namespace std;

int main(int argc, char **argv)
{
    /* Initialize the engine */
    Core()->Init();

    /* Initialize the graphic device */
    RenderMngr()->DeviceStart(572,270, false,"Onyx Illusion : Particle System Demo", argc, argv);

    /* Images */
    cImage *img_cow = new cImage("content/images/cow.png");
    img_cow->Position.Set(100,100,0);
    cImage *img_zom = new cImage("content/images/zombie.png");
    img_zom->Position.Set(200,100,0);
    cImage *img_pir = new cImage("content/images/pirate.png");
    img_pir->Position.Set(300,100,0);
    cImage *img_bom1 = new cImage("content/images/bomberman1.png");
    img_bom1->Position.Set(400,100,0);
    img_bom1->Active = false;
    cImage *img_bom2 = new cImage("content/images/bomberman2.png");
    img_bom2->Position.Set(400,100,0);

    /* Sounds */
    cSound *snd_cow = new cSound("content/sounds/cow.wav");
    cSound *snd_zom = new cSound("content/sounds/zombie.wav");
    cSound *snd_blood = new cSound("content/sounds/blood.wav");
    cSound *snd_laugh = new cSound("content/sounds/laugh.wav");
    cSound *snd_coins = new cSound("content/sounds/coins.wav");
    cSound *snd_boom = new cSound("content/sounds/boom.wav");

    /* Particles systems */
    cParticleSystem *ps_milk = new cParticleSystem();
    ps_milk->NumberRange(10,20);
    ps_milk->Position(134,107,0);
    ps_milk->XVelocityRange(-0.5,0.5);
    ps_milk->YVelocityRange(0,-1);
    ps_milk->YAccelerationRange(-0.2,-0.5);
    ps_milk->XAccelerationRange(0.0,0.0);

    cParticleSystem *ps_blood = new cParticleSystem();
    ps_blood->InitColor(1.0f,0.0f,0.0f,1.0f);
    ps_blood->EndColor(1.0f,0.0f,0.0f,0.0f);
    ps_blood->NumberRange(20,50);
    ps_blood->Position(260,126,0);
    ps_blood->XVelocityRange(0.5,0.5);
    ps_blood->YVelocityRange(1,2);
    ps_blood->YAccelerationRange(-0.2,-0.5);
    ps_blood->XAccelerationRange(0.0,0.1);

    cTexture *tx_coin = new cTexture("content/images/coin.png");
    cParticleSystem *ps_coins = new cParticleSystem();
    ps_coins->Texture = tx_coin;
    ps_coins->ScaleRange(0.5,1);
    ps_coins->NumberRange(10,20);
    ps_coins->Position(334,140,0);
    ps_coins->XVelocityRange(-2,2);
    ps_coins->YVelocityRange(0,8);
    ps_coins->YAccelerationRange(-0.2,-0.5);
    ps_coins->XAccelerationRange(0,0);

    cTexture *tx_smoke = new cTexture("content/images/smokepuff.png");
    cParticleSystem *ps_smoke = new cParticleSystem();
    ps_smoke->Texture = tx_smoke;
    ps_smoke->InitColor(0.0,0.0,0.0,1.0);
    ps_smoke->EndColor.a = 0.0f;
    ps_smoke->AngleRange(0,360);
    ps_smoke->ScaleRange(0.1,4);
    ps_smoke->NumberRange(20,40);
    //ps_smoke->XVelocityRange(-0,0.5);
    //ps_smoke->YVelocityRange(-0.5,0.5);
    ps_smoke->Position(434,130,0.5f);

    cTexture *tx_fire = new cTexture("content/images/firepuff.png");
    cParticleSystem *ps_fire = new cParticleSystem();
    ps_fire->Position(434,130,1);
    ps_fire->Texture = tx_fire;
    ps_fire->EndColor.a = 0.0f;
    ps_fire->AngleRange(1,360);
    ps_fire->ScaleRange(0.1,3);
    ps_fire->EnergyRange(0,50);
    ps_fire->XVelocityRange(-0.2,0.2);
    ps_fire->YVelocityRange(-0.2,0.2);
    ps_fire->NumberRange(20,40);

    cParticleSystem *ps_part = new cParticleSystem();
    ps_part->Position(434,130,1);
    ps_part->InitColor(0.5,0.5,0.5,1.0f);
    ps_part->EndColor(0.5,0.5,0.5,1.0f);
    ps_part->ScaleRange(0.1,2);
    ps_part->XVelocityRange(-5,5);
    ps_part->YVelocityRange(-5,5);
    ps_part->EnergyRange(0,50);
    ps_part->NumberRange(20,100);

    cTexture *tx_cursor = new cTexture("content/images/cursor.png");
    cParticleSystem *ps_cursor = new cParticleSystem();
    ps_cursor->Texture = tx_cursor;
    ps_cursor->InitColor(0,0.5,0.8,1.0);
    ps_cursor->AngleRange(0,360);
    ps_cursor->NumberRange(5,5);

    bool done=false;
    while (!done)
    {
        if (img_cow->MouseHit(Buttons::Left))
        {
            snd_cow->Play();
            ps_milk->Emit();
        }
        if (img_zom->MouseHit(Buttons::Left))
        {
            snd_zom->Play();
            snd_blood->Play();
            ps_blood->Emit();
        }
        if (img_pir->MouseHit(Buttons::Left))
        {
            snd_laugh->Play();
            snd_coins->Play();
            ps_coins->Emit();
        }
        if (img_bom1->MouseHit(Buttons::Left))
        {
            snd_boom->Play();
            img_bom1->Active = true;
            img_bom2->Active = false;
            ps_smoke->Emit();
            ps_fire->Emit();
            ps_part->Emit();
        }

        if (InputMngr()->KeyHit(Keys::Escape))
            done= true;

        ps_cursor->Position.Set(InputMngr()->MousePosition().x, InputMngr()->MousePosition().y, 0);
        ps_cursor->Emit();

        Core()->Update();
    }

    Core()->Dispose();
    return 0;
}










