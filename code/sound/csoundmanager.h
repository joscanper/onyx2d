/*

    cSoundManager - Class that controls all the audio elements

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

#ifndef CSOUNDMANAGER_H_
#define CSOUNDMANAGER_H_

#include <vector>

#include "../core/csingleton.h"
#include "csound.h"

#include "../onyx2d_defs.h"

namespace onyx2d{

	class cSoundManager : public cSingleton<cSoundManager>
	{
	    friend class cSound;
	private:
        ALuint buffer[BUFFER_SIZE],source;

		std::vector<cSound*> m_vSounds; //! List of loaded sounds

		/**
		* Function that adds a sound to the list
		*/
		void AddSound(cSound* sound);

		/**
		* Function that remove a sound from the list
		*/
		bool RemoveSound(cSound* sound);

	public:

		/**
		* Default Constructor
		*/
		cSoundManager();

		/**
		* Destructor
		*/
		~cSoundManager();

	};

	inline cSoundManager* SoundMngr()
	{
		return cSoundManager::GetSingletonPtr();
	};

};

#endif
