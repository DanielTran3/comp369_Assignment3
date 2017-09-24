#ifndef _SOUND_H

#include "allegro.h"
#include <string>

#define BGM_TOTHETOP "sounds/BGM_Epic.wav"
#define BGM_WIN "sounds/BGM_Win.wav"
#define SFX_JUMP "sounds/SFX_Jump.wav"
#define SFX_DEATH "sounds/SFX_Death.wav"
#define SFX_SPIKES "sounds/SFX_Spikes.wav"

class Sound {
	private:
		int _panning;
		int _pitch;
		int _volume;
		SAMPLE *_bgm;
		SAMPLE *_soundEffect;
		std::string _soundEffectTitle;
		
	public:
		Sound();
		~Sound();
		
		void playMusic();
		void stopMusic();
		
		void playSoundEffect();
		void stopSoundEffect();

		void updateSound(SAMPLE *sound);
		void updateAllSounds();
		
		void PollTurnOnOrOffMusic();
		
		void setPanning(int panning);
		int getPanning();
		
		void setPitch(int pitch);
		int getPitch();
		
		void setVolume(int volume);
		int getVolume();
		
		void setBGM(const char *bgmName);
		SAMPLE *getBGM();
		
		void setSoundEffect(const char *soundEffectName);
		SAMPLE *getSoundEffect();
};

#endif

