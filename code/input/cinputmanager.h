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

#pragma once

#ifndef CINPUTMANAGER_H
#define CINPUTMANAGER_H

#include "../core/csingleton.h"
#include "../core/math/cvector2.h"
#include <cstdio>

#define KEYS_NUM 1000
#define MOUSE_BUTTONS_NUM 5

namespace onyx2d
{

/* Enumeration of mouse buttons. */
namespace Buttons
{
	enum
	{
		NoButton =				-1,
		Left =					0,
		Middle =				1,
		Right =					2,
		SpinUp =                3,
		SpinDown =              4
	};
}

/* Namespace with enumeration of keyboard keys. */
namespace Keys
{
	enum
	{
		NoKey =				-1,

		A =					'A',
		B =					'B',
		C =					'C',
		D =					'D',
		E =					'E',
		F =					'F',
		G =					'G',
		H =					'H',
		I =					'I',
		J =					'J',
		K =					'K',
		L =					'L',
		M =					'M',
		N =					'N',
		O =					'O',
		P =					'P',
		Q =					'Q',
		R =					'R',
		S =					'S',
		T =					'T',
		U =					'U',
		V =					'V',
		W =					'W',
		X =					'X',
		Y =					'Y',
		Z =					'Z',

		Num0 =				'0',
		Num1 =				'1',
		Num2 =				'2',
		Num3 =				'3',
		Num4 =				'4',
		Num5 =				'5',
		Num6 =				'6',
		Num7 =				'7',
		Num8 =				'8',
		Num9 =				'9',

		Backspace =			8,
		Tab =				9,
		//Caps =				20,
		//CapsLock =			20,
		//ShiftLock =			20,

		Return =			13,
		Enter =				13,

		//Shift =				16,

		//Ctrl =				17,
		//Control =			17,

		Pause =				19,

		Escape =			27,
		Space =				32,
		SpaceBar =			32,

		PageUp =			105,
		PageDown =			104,
		End =				107,
		Home =				106,

		Left =				100,
		Up =				101,
		Right =				102,
		Down =				103,

		Insert =		    108,
		Delete =			127,

		//Windows =			91,			/* Windows-flag key. */
		//Shortcut =			93,			/* Shortcut menu key, usually between Alt Gr and Ctrl. */

		/* Numpad keys. */
		Numpad_0 =			48,
		Numpad_1 =			49,
		Numpad_2 =			50,
		Numpad_3 =			51,
		Numpad_4 =			52,
		Numpad_5 =			53,
		Numpad_6 =			54,
		Numpad_7 =			55,
		Numpad_8 =			56,
		Numpad_9 =			57,

		/* Numeric keyboard part keys. */
		Asterisk =			42,		/* Asterisk key right of Num Lock. */
		Minus =				45,		/* Minus key right of Num Lock. */
		Plus =				43,		/* Plus key right of Num Lock. */
		Add =				43,
		Slash =				47,		/* Slash key right of Num Lock. */
		Dot =               46,      /* Dot key right of Num Lock. */

		/* Function keys. */
		F1 =				1,
		F2 =				2,
		F3 =				3,
		F4 =				4,
		F5 =				5,
		F6 =				6,
		F7 =				7,
		F8 =				8,
		F9 =				9,
		F10 =				10,
		F11 =				11,
		F12 =				12,

		//NumLock =			144,

		/* Media keyboard keys. */
		Next =				176,
		Forward =			176,
		Previous =			177,
		Stop =				178,
		Continue =			179,
		PauseMedia =		179,

		Special =			500, /* Special key on media keyboards, can be media, calculator, ... */

		/* Non-ASCII-based keys */
		//LeftAlt =			800,
		//RightAlt =			801,
		//AltGr =				801
	};
}


class cInputManager : public cSingleton<cInputManager>
{
    friend class cCore;

    friend void keysGlut(unsigned char, int, int);
    friend void keysUpGlut(unsigned char, int, int);
    friend void mouseGlut(int button, int state, int x, int y);
    friend void motionGlut(int x, int y);
    friend void specialKeysGlut(int, int, int);
    friend void specialKeysUpGlut(int, int, int);

    public:
        cInputManager();
        virtual ~cInputManager();

        bool KeyUp(unsigned char key);
        bool KeyDown(unsigned char key);
        bool KeyHit(unsigned char key);

        bool MouseUp(int button);
        bool MouseDown(int button);
        bool MouseHit(int button);
        Vector2<int16> MousePosition() { return m_vMousePos; };
        Vector2<int16> MouseSpin() { return m_vMouseSpin; };

        void FlushKeys();
        void FlushMouse();
    protected:
    private:
        int m_iButtonDown;
        int m_iButtonReleased;
        unsigned char m_ucKeyDown;
        unsigned char m_ucKeyReleased;
        bool m_aKeys[KEYS_NUM];
        bool m_aButtons[MOUSE_BUTTONS_NUM];
        Vector2<int16> m_vMousePos;
        Vector2<int16> m_vMouseSpin;

        void Init();
        void Update();
        void UpdateKeys(unsigned char key, int x, int y);
        void UpdateKeysUp(unsigned char key, int x, int y);
        void UpdateSpecialKeys(int key, int x, int y);
        void UpdateSpecialKeysUp(int key, int x, int y);
        void UpdateMouse(int button, int state, int x, int y);
        void UpdateMouseMotion(int x, int y);
};

inline cInputManager* InputMngr()
{
        return cInputManager::GetSingletonPtr();
};


}

#endif // CINPUTMANAGER_H
