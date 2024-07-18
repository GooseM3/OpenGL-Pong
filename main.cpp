#include "OpenGLdata.h"
#include "ShaderUtils.h"
#include <cmath>
#include <iostream>
#include <string>
#include <cstring> 
#include <chrono>  
#include <fstream>  
#include <mmsystem.h> 
#include "m_text.h"  
#include "Sound.h"
#include "Ball.h"
#include "hud.h"
#include "game.h"
#include "Paddle.h"


bool LoadWAVFile(const char* filename, BYTE*& buffer, DWORD& size);
void PlayBeepSound();
void PlayBackgroundMusic(const char* filename);
void StopBackgroundMusic();

GLfloat orthoMatrix[16];


void handleMouseClick(float x, float y) {
    float startX = -0.8f;
    float startY = 0.5f;
    float endX = startX + 0.8f;
    float endY = startY - 0.1f;

    if (x >= startX && x <= endX && y <= startY && y >= endY) {
        std::cerr << "Hello World" << std::endl;
    }
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static int windowWidth = 1920;
    static int windowHeight = 1080;

    Game* game = reinterpret_cast<Game*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)); 

    switch (uMsg) {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE: {
        windowWidth = LOWORD(lParam);
        windowHeight = HIWORD(lParam);

        float aspectRatio = 16.0f / 9.0f;
        int viewportWidth, viewportHeight;
        if (windowWidth / (float)windowHeight > aspectRatio) {
            viewportWidth = (int)(windowHeight * aspectRatio);
            viewportHeight = windowHeight;
        }
        else {
            viewportWidth = windowWidth;
            viewportHeight = (int)(windowWidth / aspectRatio);
        }
        int viewportX = (windowWidth - viewportWidth) / 2;
        int viewportY = (windowHeight - viewportHeight) / 2;
        glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
        SetOrthoMatrixs(orthoMatrix, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f);
        return 0;
    }
    case WM_KEYDOWN:
        if (wParam == VK_UP && game != nullptr) { 
            game->playerPaddle.upPressed = true;
            std::cerr << "UP" << std::endl;
        }
        if (wParam == VK_DOWN && game != nullptr) { 
            game->playerPaddle.downPressed = true;
            std::cerr << "DOWN" << std::endl;
        }
        if (wParam == VK_RIGHT && game != nullptr) {
            game->increase_tickDuration();
            std::cerr << game->tickDuration << std::endl;
            game->currentState = PLAYING;
        }
        if (wParam == VK_LEFT && game != nullptr) { 
            game->tickDuration += 2;
            std::cerr << game->tickDuration << std::endl;
            float ballScreenX = (game->ball.x + 1.0f) * 0.5f * windowWidth;
            float ballScreenY = (1.0f - (game->ball.y + 1.0f) * 0.5f) * windowHeight;
            float leftPaddleScreenX = (-0.9f + 1.0f) * 0.5f * windowWidth;
            float leftPaddleScreenY = (1.0f - (game->playerPaddle.y - 0.15f + 1.0f) * 0.5f) * windowHeight;
            float rightPaddleScreenX = (0.85f + 1.0f) * 0.5f * windowWidth;
            float rightPaddleScreenY = (1.0f - (game->aiPaddle.y + 0.15f) * 0.5f) * windowHeight;
            std::cerr << "Ball Position: (" << ballScreenX << ", " << ballScreenY << ")" << std::endl;
            std::cerr << "Left Paddle Position: (" << leftPaddleScreenX << ", " << leftPaddleScreenY << ")" << std::endl;
            std::cerr << "Right Paddle Position: (" << rightPaddleScreenX << ", " << rightPaddleScreenY << ")" << std::endl;
        }
        return 0;
    case WM_KEYUP:
        if (game != nullptr) { 
            if (wParam == VK_UP) game->playerPaddle.upPressed = false;
            if (wParam == VK_DOWN) game->playerPaddle.downPressed = false;
        }
        return 0;
    case WM_LBUTTONDOWN: {
        std::cerr << "Mouse Clicked" << std::endl;
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);
        std::cerr << "Mouse Click at: (" << mouseX << ", " << mouseY << ")" << std::endl;
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath) {
    std::string vertexShaderSource = ReadFile(vertexFilePath);
    std::string fragmentShaderSource = ReadFile(fragmentFilePath);

    if (vertexShaderSource.empty() || fragmentShaderSource.empty()) {
        std::cerr << "Failed to load shader files" << std::endl;
        return 0;
    }

    const char* vertexShaderCode = vertexShaderSource.c_str();
    const char* fragmentShaderCode = fragmentShaderSource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void DrawRectangle(float x, float y, float width, float height, GLuint shaderProgram) {
    GLfloat vertices[] = {
     -0.015f, -0.15f, 0.0f,
      0.015f, -0.15f, 0.0f,
      0.015f,  0.15f, 0.0f,
     -0.015f,  0.15f, 0.0f
    };

    glUseProgram(shaderProgram);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

int frameCount = 0;
auto previousTime = std::chrono::high_resolution_clock::now();
float fps = 0.0f;

void CalculateFPS() {
    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - previousTime).count();
    if (duration >= 1) {
        fps = frameCount / duration;
        frameCount = 0;
        previousTime = currentTime;
    }
}

void DrawFPS() {
    std::string fpsText = "FPS : " + std::to_string(static_cast<int>(fps));
    Text fpsDisplay(fpsText, -0.98f, 0.98f, 1.0f, 0.07f);
    DrawScore(-0.8f, 0.98f, static_cast<int>(fps));
    fpsDisplay.draw();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    PreloadSound();
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONIN$", "r", stdin);
    freopen_s(&file, "CONOUT$", "w", stdout);
    freopen_s(&file, "CONOUT$", "w", stderr);

    auto startTime = std::chrono::high_resolution_clock::now();
    std::cerr << "Debugging Console Initialized" << std::endl;

    WNDCLASS wc;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL quit = FALSE;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"OpenGLApp";
    RegisterClass(&wc);
    hwnd = CreateWindow(
        L"OpenGLApp", L"OpenGL Pong Game",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
        NULL, NULL, hInstance, NULL);
    EnableOpenGL(hwnd, &hDC, &hRC);
    LoadOpenGLFunctions();
    

    if (!LoadWAVFile("beep.wav", beepWAVBuffer, beepWAVSize)) {
        std::cerr << "Failed to load beep.wav" << std::endl;
    }
    PlayBackgroundMusic("jaz.wav");
    SetBackgroundMusicVolume(45);

    GLuint shaderProgram = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");

    auto previousTime = std::chrono::high_resolution_clock::now();

    Game game; 
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&game));

    while (!quit) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                quit = TRUE;
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else {
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();
            
            if (elapsedTime >= game.tickDuration) {
                previousTime = currentTime;
                game.elapsedTimeInSeconds += elapsedTime / 1000.0f;

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                game.Draw(shaderProgram);
                CalculateFPS();
                DrawFPS();
                SwapBuffers(hDC);
            }
        }
    }

    StopBackgroundMusic();
    DisableOpenGL(hwnd, hDC, hRC);
    DestroyWindow(hwnd);

    return msg.wParam;
}
