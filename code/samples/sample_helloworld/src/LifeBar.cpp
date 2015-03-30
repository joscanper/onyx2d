#include "../include/LifeBar.h"

LifeBar::LifeBar(cColor c)
{

    this->Size.x = 50;
    this->Size.y = 5;

    lifeAmount = 100;

    // Enemy Ship life
    lifeBack = new cRectangle(0, 0, this->Size.x, this->Size.y);
    lifeBack->SetParent(this);
    life = new cRectangle(1, 1, this->Size.x - 2, this->Size.y - 2);
    life->SetParent(lifeBack);
    life->Color.Set(c.r, c.g, c.b);
}

LifeBar::~LifeBar()
{
    lifeBack->Delete();
    life->Delete();
}

void LifeBar::Delete()
{
    lifeBack->Delete();
    life->Delete();

    //SAFE_RELEASE(this);
}

void LifeBar::Decrease(int amount)
{
    lifeAmount -= amount;
    if (lifeAmount <= 0)
        lifeAmount = 0;
    life->Size.x = lifeAmount * (life->Size.x - 2) / 100;
}


void LifeBar::Increase(int amount)
{
    lifeAmount += amount;
    if (lifeAmount <= 0)
        lifeAmount = 0;
    life->Size.x = lifeAmount * (life->Size.x - 2) / 100;
}

bool LifeBar::IsEmpty()
{
    return lifeAmount <= 0;
}

void LifeBar::Resize(Vector2<float> size)
{
    lifeBack->Resize(size);
    life->Resize(Vector2<float>(size.x - 2, size.y - 2));
}
