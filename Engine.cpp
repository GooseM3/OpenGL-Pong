#include "Engine.h"
#include "Sound.h"

#include "OpenGLdata.h"
#include <windows.h>

Engine::Engine(int width, int height)
    : elapsedTimeInSeconds(0.0f), paddleSpeed(0.01f), countdownValue(3),
    gameStarted(false), tickDuration(16), leftPlayerScore(0),
    rightPlayerScore(0), frameCount(0), fps(0.0f), zoomFactor(1.0f) {
    windowWidth = width;
    windowHeight = height;
    previousTime = std::chrono::high_resolution_clock::now();
}

void Engine::Run() {
}

bool Engine::LoadWAVFile(const char* filename, BYTE*& buffer, DWORD& size) {
    return LoadWAVFile(filename, buffer, size);
}

void Engine::PlayBeepSound() {
    PlayBeepSound();
}

void Engine::PlayBackgroundMusic(const char* filename) {
}

void Engine::StopBackgroundMusic() {
    StopBackgroundMusic();
}

void Engine::SetOrthoMatrix(GLfloat* m, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nears, GLfloat fars, float zoom) {
    SetOrthoMatrixs(m, left, right, bottom, top, nears, fars, zoom);
}

void Engine::DrawRectangle(float x, float y, float width, float height, GLuint shaderProgram) {
    GLfloat vertices[] = {
        -width / 2, -height / 2, 0.0f,
         width / 2, -height / 2, 0.0f,
         width / 2,  height / 2, 0.0f,
        -width / 2,  height / 2, 0.0f
    };

    glUseProgram(shaderProgram);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Engine::DrawHitbox(float x, float y, float width, float height) {
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(x - width / 2, y - height / 2);
    glVertex2f(x + width / 2, y - height / 2);
    glVertex2f(x + width / 2, y + height / 2);
    glVertex2f(x - width / 2, y + height / 2);
    glEnd();

    glPopMatrix();
}





void Engine::CalculateFPS() {
    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - previousTime).count();
    if (duration >= 1) {
        fps = frameCount / duration;
        frameCount = 0;
        previousTime = currentTime;
    }
}

void Engine::HandleMouseClick(float x, float y) {
    float startX = -0.8f;
    float startY = 0.5f;
    float endX = startX + 0.8f;
    float endY = startY - 0.1f;

    if (x >= startX && x <= endX && y <= startY && y >= endY) {
        std::cerr << "Hello World" << std::endl;
    }
}

GLuint Engine::LoadShaders(const char* vertexFilePath, const char* fragmentFilePath) {
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

int Engine::GetWindowWidth() const {
    return windowWidth;
}

int Engine::GetWindowHeight() const {
    return windowHeight;
}

void Engine::EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC) {
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    *hDC = GetDC(hwnd);

    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, iFormat, &pfd);

    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}

void Engine::DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

void Engine::LoadOpenGLFunctions() {
   LoadOpenGLFunctions();
}

void Engine::PreloadSound() {
}

void Engine::SetMVP(GLuint shaderProgram, const GLfloat* mvp) {
    GLint mvpLocation = glGetUniformLocation(shaderProgram, "MVP");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp);
}


