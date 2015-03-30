/*

    cRenderManager - Class that controls all the graphics elements

    Copyright (C) 2010-2011 Josue Candela Perdomo (josuecp.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

**/


#ifndef CRENDERMANAGER_H
#define CRENDERMANAGER_H

#include "../onyx2d_defs.h"

#include "../core/csingleton.h"
#include "../core/math/cvector2.h"
#include "../core/math/cvector3.h"

#include "cdrawable.h"
#include "crectangle.h"
#include "ccolor.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

namespace onyx2d
{

class cRenderManager : public cSingleton<cRenderManager>
{
    friend class cCore;
    friend class cDrawable;

    friend void renderGlut(void);
    friend void reshapeGlut(int x, int y);
    friend void idleGlut(void);

    public:
        cColor             ClearColor;      //! Clear screen color
    private:
        Vector2<uint16>    m_vSize;         //! Size of the device
        vector<cDrawable*> m_vDrawables;    //! Vector of drawable objects
        GLuint m_uFrameBufferID;
        GLuint m_uRenderBufferID;
        GLuint m_uRenderTextureID;
    public:
        /** Default constructor */
        cRenderManager();

        /** Destructor */
        virtual ~cRenderManager();

        /**
        * Function that starts the device
        * @return <i>true</i> if the device was started correctly, <i>false</i> in other case
        */
        bool DeviceStart(int width, int height, bool fullscreen, char* title, int argc, char**argv);

        /**
        * Function that ends the device
        * @return <i>true</i> if the device was relased correctly, <i>false</i> in other case
        */
        bool DeviceEnd();

        /**
        * Function that returns the device size
        * @return Vector of size 2 with the device size
        */
        Vector2<uint16> DeviceSize(){ return m_vSize; };

        /**
        * Function that draws debug text on the window
        * @param x X position of the text
        * @param y Y position of the text
        * @param string Text
        */
        void DebugText( float x, float y, std::string string);


        /**
        * Function that clears the screen
        */
        void Cls();

        /**
        * Function that rotates space coordinates
        * @param coors Coordinates to rotate
        * @param angle Angle to rotate
        * @param rot_ref Rotation reference point
        */
        Vector2<float> RotateCoordinates(Vector2<float> coors, float angle, Vector2<float> rot_ref);


    protected:

    private:

        /**
        * Function that removes the object from the lis of drawables and destroys it
        * @param dra Pointer to the drawable to remove
        */
        void DeleteDrawable(cDrawable *dra);

        /**
        * Function that render all the drawable objects
        */
        void Render();

        /**
        * Function called by Glut when the window reshapes
        */
        void Reshape(int x, int y);

        /**
        * Function that updates the Render Manager
        */
        void Update();

        /**
        * Function called by Glut when the window is in Idle time
        */
        void Idle();

        /**
        * Function that sorts all drawable objects by depth variable
        * @param ini Index of first drawable element
        * @param end Index of last drawable element
        */
        void DrawablesDepthQuickSort(int ini, int end);


};

inline cRenderManager* RenderMngr()
{
        return cRenderManager::GetSingletonPtr();
};

/**
* Auxiliar functions for use as freeGlut functions paramenters
*/
void renderGlut(void);
void reshapeGlut(int x, int y);
void idleGlut(void);
void keysGlut(unsigned char, int, int);
void keysUpGlut(unsigned char, int, int);
void specialKeysGlut(int, int, int);
void specialKeysUpGlut(int, int, int);
//void joystickGlut(unsigned int buttonMask, int x, int y, int z);
void mouseGlut(int button, int state, int x, int y);
void motionGlut(int x, int y);

}

#endif // CRENDERMANAGER_H
