#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "../onyx2d_defs.h"
#include "../core/utils/gen_func.h"
#include "cdrawable.h"

namespace onyx2d
{


class cCircle : public cDrawable
{
    public:
        cCircle(int16 x, int16 y, float radius);


        virtual ~cCircle();
    protected:
    private:
        /**
            Function that draws the image
        */
        void Draw();

        /**
            Function that updates the image
        */
        void Update();

        /**
            Function that contain all the geometry
        */
        void Geometry();
};

}

#endif // CCIRCLE_H
