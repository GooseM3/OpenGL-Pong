#include "Sound.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma comment(lib, "winmm.lib")  

#include <mmsystem.h>
extern BYTE* beepWAVBuffer = nullptr;
extern DWORD beepWAVSize = 0;


bool LoadWAVFile(const char* filename, BYTE*& buffer, DWORD& size) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open WAV file." << std::endl;
        return false;
    }

    size = static_cast<DWORD>(file.tellg());
    buffer = new BYTE[size];

    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(buffer), size);
    file.close();

    return true;
}

void PreloadSound() {
    if (!LoadWAVFile("beeps.wav", beepWAVBuffer, beepWAVSize)) {
        std::cerr << "Failed to load beep sound." << std::endl;
    }
    else {
        std::cout << "HERE\n" << std::endl;
    }
    std::cout << "HERE2\n";
}

std::wstring StringToWString(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], size_needed);
    return wstr;
}

void PlayBackgroundMusic(const char* filename) {
    std::wstring command = L"open ";
    command += StringToWString(filename) + L" type mpegvideo alias bgm";
    mciSendString(command.c_str(), NULL, 0, NULL);
    mciSendString(L"play bgm repeat", NULL, 0, NULL);
}
void PlayBeepSound() {
    if (beepWAVBuffer && beepWAVSize > 0) {
        PlaySound(reinterpret_cast<LPCWSTR>(beepWAVBuffer), NULL, SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
    }
}
void StopBackgroundMusic() {
    mciSendString(L"stop bgm", NULL, 0, NULL);
    mciSendString(L"close bgm", NULL, 0, NULL);
}

void SetBackgroundMusicVolume(int volume) {
    std::wstring command = L"setaudio bgm volume to " + std::to_wstring(volume);
    mciSendString(command.c_str(), NULL, 0, NULL);
}