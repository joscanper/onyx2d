#ifndef LIFEBAR_H
#define LIFEBAR_H

#include "../../../onyx2d.h"

#define LIFEBAR_SIZE 50

class LifeBar : public cDrawable
{
    public:
        LifeBar(cColor color);
        virtual ~LifeBar();

        void Decrease(int amount);

        void Increase(int amount);

        bool IsEmpty();

        void Resize(Vector2<float> size);

        void Delete();
    protected:


    private:
        cRectangle * life;
        cRectangle * lifeBack;
        int lifeAmount;

};

#endif // LIFEBAR_H
