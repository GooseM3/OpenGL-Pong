#ifndef SOUND_H
#define SOUND_H

#include <Windows.h>
#include <string>

extern BYTE* beepWAVBuffer;
extern DWORD beepWAVSize;

bool LoadWAVFile(const char* filename, BYTE*& buffer, DWORD& size);
void PreloadSound();
std::wstring StringToWString(const std::string& str);
void PlayBackgroundMusic(const char* filename);
void PlayBeepSound();
void StopBackgroundMusic();
void SetBackgroundMusicVolume(int volume);

#endif 
