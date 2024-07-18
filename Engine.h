#pragma once

#include "OpenGLdata.h"
#include "ShaderUtils.h"
#include <chrono>
#include <string>
#include <iostream>
#include <cmath>
#include <windows.h>

class Engine {
public:
    Engine(int width, int height);
    void Run();
    bool LoadWAVFile(const char* filename, BYTE*& buffer, DWORD& size);
    void PlayBeepSound();
    void PlayBackgroundMusic(const char* filename);
    void StopBackgroundMusic();
    void SetOrthoMatrix(GLfloat* m, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nears, GLfloat fars, float zoom);
    void DrawRectangle(float x, float y, float width, float height, GLuint shaderProgram);
    void DrawHitbox(float x, float y, float width, float height);
    void DrawMenu();
    void DrawFPS();
    void CalculateFPS();
    void HandleMouseClick(float x, float y);
    GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath);
    int GetWindowWidth() const;
    int GetWindowHeight() const;
    void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC);
    void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC);
    void LoadOpenGLFunctions();
    void PreloadSound();
    void SetMVP(GLuint shaderProgram, const GLfloat* mvp);
    
    //void DrawCountdown(int countdown);
    //void DrawText(const char* text, float x, float y, float scale);

    float zoomFactor;

private:
    int windowWidth;
    int windowHeight;
    float elapsedTimeInSeconds;
    float paddleSpeed;
    int countdownValue;
    bool gameStarted;
    int tickDuration;
    int leftPlayerScore;
    int rightPlayerScore;
    GLfloat orthoMatrix[16];
    GLuint shaderProgram;
    std::chrono::high_resolution_clock::time_point previousTime;
    int frameCount;
    float fps;
};
