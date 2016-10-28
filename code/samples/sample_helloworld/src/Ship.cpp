#include "Ship.h"
#include "LifeBar.h"

cShip::cShip()
{
    //ctor
}

cShip::~cShip()
{
    //dtor
}

void cShip::SetObserver(iShipObserver * o)
{
    observer = o;
}

void cShip::Hit()
{
    lifeBar->Decrease(10);
}

cImage * cShip::GetImage()
{
    return img_ship;
}


