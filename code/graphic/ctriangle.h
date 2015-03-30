#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "../onyx2d_defs.h"
#include "cdrawable.h"

namespace onyx2d
{

class cTriangle : public cDrawable
{
    public:
        /**   Constructor that accept the position and size of the triangle
        *   @param x X position of the triangle
        *   @param y Y position of the triangle
        *   @param width Width of the triangle
        *   @param height Height of the triangle
        */
        cTriangle(uint16 x, uint16 y, uint16 width, uint16 height);

        virtual ~cTriangle();
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
#endif // CTRIANGLE_H
