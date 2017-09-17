#ifndef _SOUND_H
#include <allegro.h>
#include <string>

#define HARDLINE_BGM "sounds/hardline_bgm.wav"
#define HIT_SFX "sounds/hit_sfx.wav"
#define LEVELUP_SFX "sounds/levelup_sfx.wav"
#define PAUSE_SFX "sounds/pause_sfx.wav"
#define GAMEOVER_SFX "sounds/gameover_sfx.wav"

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

