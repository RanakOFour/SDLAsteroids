#include "MusicPlayer.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>


MusicPlayer::MusicPlayer()
{
	m_CurrentTrack = nullptr;
	Initialise();
}

void MusicPlayer::Initialise()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << ("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	m_SoundEffectChunks[0] = Mix_LoadWAV((char*)"Assets/Music/bullet.wav");
	m_SoundEffectChunks[1] = Mix_LoadWAV((char*)"Assets/Music/explosion.wav");
	m_SoundEffectChunks[2] = Mix_LoadWAV((char*)"Assets/Music/ufodeath.wav");
	m_SoundEffectChunks[3] = Mix_LoadWAV((char*)"Assets/Music/death.wav");
}

void MusicPlayer::StopCurrentTrack()
{
	Mix_FreeMusic(m_CurrentTrack);
	m_IsPlaying = false;
}

void MusicPlayer::PlayMenu()
{
	if (m_IsPlaying)
	{
		StopCurrentTrack();
	}
	m_CurrentTrack = Mix_LoadMUS((char*)"Assets/Music/menu.wav");
	Mix_PlayMusic(m_CurrentTrack, 9);
	m_IsPlaying = true;
}

void MusicPlayer::PlayBkgd()
{
	if (m_IsPlaying)
	{
		StopCurrentTrack();
	}
	m_CurrentTrack = Mix_LoadMUS((char*)"Assets/Music/bkgd.wav");
	Mix_PlayMusic(m_CurrentTrack, 9);
	m_IsPlaying = true;
}

void MusicPlayer::BulletSoundEffect()
{
	Mix_PlayChannel(1, m_SoundEffectChunks[0], 0);
}

void MusicPlayer::PlayerHitEffect()
{
	Mix_PlayChannel(2, m_SoundEffectChunks[1], 0);
}

void MusicPlayer::OtherHitEffect()
{
	Mix_PlayChannel(2, m_SoundEffectChunks[2], 0);
}

void MusicPlayer::GameOver()
{
	Mix_PlayChannel(2, m_SoundEffectChunks[3], 0);
}

bool MusicPlayer::IsPlaying()
{
	return m_IsPlaying;
}