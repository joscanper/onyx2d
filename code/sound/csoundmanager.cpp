#include "csoundmanager.h"

#include "../core/cconsole.h"

namespace onyx2d
{

	cSoundManager::cSoundManager()
	{

		ALCdevice* pDevice;
        ALCcontext* pContext;

/*
        // Get handle to device.
        pDevice = alcOpenDevice(NULL);

        // Get the device specifier.
        const ALCchar *deviceSpecifier = alcGetString(pDevice, ALC_DEVICE_SPECIFIER);

		std::string msg = "CORRECTLY SET THE AUDIO DEVICE : ";
		msg += deviceSpecifier;
		Console()->AddRecord(msg, RecordType::Info);

        //printf("Using device '%s'.\n", szDeviceSpecifier);

        // Create audio context.
        pContext = alcCreateContext(pDevice, NULL);

        // Set active context.
        alcMakeContextCurrent(pContext);

        // Check for an error.
        ALCenum err = alcGetError(pDevice);
        if (err != ALC_NO_ERROR)
		{
			std::string str= "ERROR WHILE SET AUDIO DEVICE";
			str += alutGetErrorString(err);
			Console()->AddRecord(str, RecordType::Error);
		}
*/

		alutInit(0,0);



	}

	cSoundManager::~cSoundManager()
	{
/*
        ALCcontext* pCurContext;
        ALCdevice* pCurDevice;

        // Get the current context.
        pCurContext = alcGetCurrentContext();

        // Get the device used by that context.
        pCurDevice = alcGetContextsDevice(pCurContext);

        // Reset the current context to NULL.
        alcMakeContextCurrent(NULL);

        // Release the context and the device.
        alcDestroyContext(pCurContext);
        alcCloseDevice(pCurDevice);
*/

        //Clear the sound list
        for (uint16 c=0; c<m_vSounds.size(); c++)
        {
            SAFE_RELEASE(m_vSounds.at(c));
        }


        m_vSounds.clear();

        alutExit();
	}


	void cSoundManager::AddSound(cSound *sound)
	{
		m_vSounds.push_back(sound);
	}

	bool cSoundManager::RemoveSound(cSound *sound)
	{
		std::vector<cSound*> aux;
		bool removed = false;

		for (uint16 c=0; c<m_vSounds.size(); c++)
		{
			if (m_vSounds.at(c)!=sound)
				aux.push_back(m_vSounds.at(c));
			else
				removed = true;

		}

		return removed;

	}




}

