#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>

#pragma once
#define H_MUSICPLAYER

class MusicPlayer
{
private:
	bool m_IsPlaying;
	Mix_Music* m_CurrentTrack;
	Mix_Chunk* m_SoundEffectChunks[5];
	void Initialise();

public:
	MusicPlayer();
	void PlayMenu();
	void PlayBkgd();
	void BulletSoundEffect();
	void PlayerHitEffect();
	void OtherHitEffect();
	void GameOver();
	void StopCurrentTrack();
	bool IsPlaying();
};