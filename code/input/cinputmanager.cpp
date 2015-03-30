/*

    cInputManager - Class that manages all the input devices

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

#include "cinputmanager.h"
#include "../graphic/crendermanager.h"

namespace onyx2d
{

    cInputManager::cInputManager()
    {
        //ctor
    }

    cInputManager::~cInputManager()
    {
        //dtor
    }

    void cInputManager::Init()
    {

        m_vMousePos.SetZero();
        m_vMouseSpin.SetZero();

        FlushKeys();
        FlushMouse();

    }

    void cInputManager::FlushMouse()
    {
        for (int i=0; i<MOUSE_BUTTONS_NUM ; i++)
            m_aButtons[i] = false;

        m_iButtonDown = Buttons::NoButton;
    }

    void cInputManager::FlushKeys()
    {
        for (int i=0; i<KEYS_NUM ; i++)
            m_aKeys[i] = false;

        m_ucKeyDown = Keys::NoKey;
    }

    void cInputManager::Update()
    {

    }

    void cInputManager::UpdateSpecialKeys(int key, int x, int y)
    {
        //printf("sk : %d\n", key);
        //if (key>64 && key<91)
        //    key = toupper(key);
        m_aKeys[key] = true;
        m_ucKeyDown = key;
    }

    void cInputManager::UpdateSpecialKeysUp(int key, int x, int y)
    {
        //if (key>64 && key<91)
        //    key = toupper(key);
        m_aKeys[key] = false;
        m_ucKeyReleased = key;
    }

    void cInputManager::UpdateKeys(unsigned char key, int x, int y)
    {
        if ((key>96 && key<123))
            key = toupper(key);
       // printf("%d\n", key);
        m_aKeys[key] = true;
        m_ucKeyDown = key;
    }


    void cInputManager::UpdateKeysUp(unsigned char key, int x, int y)
    {
        if ((key>96 && key<123))
            key = toupper(key);
        m_aKeys[key] = false;
        m_ucKeyReleased = key;
    }

    void cInputManager::UpdateMouse(int button, int state, int x, int y)
    {

        if (state == GLUT_DOWN)
        {
            m_aButtons[button] = true;
            m_iButtonDown = button;
        }else{
            m_aButtons[button] = false;
            m_iButtonReleased = button;
            m_iButtonDown = Buttons::NoButton;
        }

    }

    void cInputManager::UpdateMouseMotion(int x, int y)
    {

        m_vMouseSpin.x -= (x - m_vMousePos.x);
        m_vMouseSpin.y -= (y - m_vMousePos.y);

        m_vMousePos.x = x;
        m_vMousePos.y = RenderMngr()->DeviceSize().y - y;


    }

    bool  cInputManager::MouseUp(int button)
    {

        if (m_iButtonReleased == button)
            return true;
        else
            return false;

    }

    bool  cInputManager::MouseDown(int button)
    {
         return m_aButtons[button];
    }

    bool  cInputManager::MouseHit(int button)
    {
        if (m_iButtonDown == button)
        {
            m_iButtonDown = Buttons::NoButton;
            return true;
        }else{
            return false;
        }
    }

    bool cInputManager::KeyUp(unsigned char key)
    {
        if (m_ucKeyReleased == key)
            return true;
        else
            return false;
    }

    bool cInputManager::KeyDown(unsigned char key)
    {
        return m_aKeys[key];
    }

    bool cInputManager::KeyHit(unsigned char key)
    {

        if (m_ucKeyDown == key)
        {
            m_ucKeyDown = Keys::NoKey;
            return true;
        }else{
            return false;
        }
    }

}//namespace onyx2d

