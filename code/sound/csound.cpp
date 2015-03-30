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

#include "csound.h"

#include "csoundmanager.h"
#include "../core/cconsole.h"
#include "../core/ccore.h"

namespace onyx2d{

	cSound::cSound(cSound* snd){

        buffer = snd->buffer;
        source = snd->source;
        format = snd->format;
        freq = snd->freq;
        size =  snd->size;
        bufferData = snd->bufferData;
        state = snd->state;
        data =  snd->data;

	}

	cSound::cSound(std::string path){


        Load(path);

        //Add the sound to the sound list
        SoundMngr()->AddSound(this);

	}

	cSound::~cSound(){

		//Delete buffer and source of the sound
		alDeleteBuffers(1, &buffer);
		alDeleteSources(1, &source);
	}

    void cSound::Load(std::string path){

        std::string format = FileExtension(path);

		//Check if the file exist
		if (!FileExist(path))
		{
		    std::string msg = "cSound : File not found : ";
			msg += path;
            Console()->AddRecord(msg,RecordType::Warning);
            return;
		}

		if (format == "WAV")
		{
			LoadWAV(path);
		}else if (format == "OGG"){
			LoadOGG(path);
		}else{
			std::string msg = "cSound : Unknow File format : ";
			msg += path;
			msg += " (" + format + ")";
            Console()->AddRecord(msg,RecordType::Warning);
		}

		state = SoundState::Stoped;
    }

	void cSound::LoadWAV(std::string file_name){

		ALboolean loop;

		//Clear error messages
		alGetError();

        alGenBuffers(1,&buffer);

        buffer = alutCreateBufferFromFile(file_name.c_str());
		//alutLoadWAVFile((ALbyte*)file_name.c_str(),&format,&data,&size,&freq,&loop);
        //alBufferData(buffer,format,data,size,freq);
        //alutUnloadWAV(format,data,size,freq);

        alGenSources(1, &source);

		ALenum error = alGetError();
		if(error != AL_NO_ERROR) {

            std::string msg = "cSound : Error generating source : ";
            msg += file_name;
            msg += "( ";
			msg.append(alutGetErrorString(error));
            msg += " )";
			Console()->AddRecord(msg,RecordType::Error);
        }


//		alBufferData (buffer, format, wave, size, freq);
		//free(wave);

		//alGenSources(1, &source);


		alSourcef(source, AL_PITCH, 1.0f);
        alSourcef(source, AL_GAIN, 1.0f);
		alSourcei(source, AL_BUFFER, buffer);
/*
        ALfloat listenerPos[]={0.0,0.0,0.0};
        ALfloat listenerVel[]={0.0,0.0,0.0};
        ALfloat listenerOri[]={0.0,0.0,-1.0, 0.0,1.0,0.0};

        alSourcefv(source,AL_POSITION, listenerPos);
        alSourcefv(source,AL_VELOCITY, listenerVel);
		alSourcefv(source,AL_ORIENTATION, listenerOri);
*/
		/*int error = alGetError();
		if (error != AL_NO_ERROR){


		}*/

	}

	void cSound::LoadOGG(std::string file_name){

		int bitStream;
		long bytes;
		int endian=0;
		char array[BUFFER_SIZE];    // Local fixed size array
		std::string msg;
		FILE *f;
		OggVorbis_File oggFile;
		 vorbis_info *pInfo;

		// Create sound buffer and source
		alGenBuffers(1, &buffer);
		alGenSources(1, &source);

		// Open for binary reading
		f = fopen(file_name.c_str(), "rb");

		ov_open_callbacks(f, &oggFile, NULL, 0,OV_CALLBACKS_DEFAULT);


		// Get some information about the OGG file
		pInfo = ov_info(&oggFile, -1);

		// Check the number of channels... always use 16-bit samples
		if (pInfo->channels == 1)
		format = AL_FORMAT_MONO16;
		else
		format = AL_FORMAT_STEREO16;

		// The frequency of the sampling rate
		freq = pInfo->rate;


		do {
		// Read up to a buffer's worth of decoded sound data
		bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);
		// Append to end of buffer
		bufferData.insert(bufferData.end(), array, array + bytes);
		} while (bytes > 0);

		ov_clear(&oggFile);


		// Upload sound data to buffer
		alBufferData(buffer, format, &bufferData[0], static_cast < ALsizei > (bufferData.size()), freq);

		// Attach sound buffer to source
		alSourcei(source, AL_BUFFER, buffer);

		int error = alGetError();
		if (error != AL_NO_ERROR){

			msg = "cSound : Error Attaching buffer to source : ";
            msg += file_name;
			msg.append(alutGetErrorString(error));

			Console()->AddRecord(msg,RecordType::Error);
		}
	}

	void cSound::Play(){

        alSourcePlay(source);
		state = SoundState::Played;

	}

	void cSound::Stop(){

		alSourceStop(source);
		state = SoundState::Stoped;

	}

	void cSound::Pause(){

		alSourcePause(source);
		state = SoundState::Paused;

	}

	void cSound::Loop(bool loop_sound){
		alSourcei(source, AL_LOOPING, loop_sound);
	}

	uint8 cSound::GetState(){

		return state;
	}
}
