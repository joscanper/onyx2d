/*

    cSound - Class that allows sound loading and playing

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

#ifndef CSOUND_H_
#define CSOUND_H_

#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "../core/cobject.h"
#include "../3rdparty/vorbis/vorbisfile.h"
#include "../3rdparty/AL/alut.h"
#include "../core/utils/gen_func.h"

#include "../onyx2d_defs.h"

#define BUFFER_SIZE   32768     // 32 KB buffers

namespace onyx2d{

    namespace SoundState
    {
        enum{
            Played = 0,
            Stoped,
            Paused,
        };
    }

	class cSound : cObject
	{

		private:

			ALuint buffer,source;
			ALenum format;					         //! The sound data format
			ALsizei freq,size;					     //! The frequency of the sound data
			std::vector < char > bufferData;         //! The sound buffer data from file
			uint8 state;                             //! The sound state
			ALvoid  *data;

			char *path;

            /**
			* Function that loads a WAV file
			* @param path Path of the file
			*/
			void LoadWAV(std::string path);

			/**
			* Function that loads a OGG file
			* @param path Path of the file
			*/
			void LoadOGG(std::string path);

		public:

			/**
			* Constructor
			* @param path Path of the sound file
			*/
			cSound(std::string path);

			/**
			* Copy Constructor
			* @param snd Other Sound
			*/
			cSound(cSound* snd);

			/**
			* Destructor
			*/
			~cSound();

			/**
			* Function that loads a sound file
			* @param path Path of the file
			*/
			void Load(std::string path);

			/**
			* Function that sets if the sound is reproduces as a loop
			* @param loop_sound True for loop sounds
			*/
			void Loop(bool loop_sound);

			/**
			* Function that plays the sound
			*/
			void Play();

			/**
			* Function that stops the sound
			*/
			void Stop();

			/**
			* Function that pause the sound
			*/
			void Pause();

			/**
			* Function that returns the sound state
			* @return State of the sound
			*/
			uint8 GetState();

	};
}

#endif
