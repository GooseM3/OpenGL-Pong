#include "OpenGLdata.h"
HWND hwnd = NULL;  
HDC hDC = NULL;    
HGLRC hRC = NULL; 
float zoomFactor = 1.0f;

PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;

void LoadOpenGLFunctions() {
    glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
    glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
    glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
    glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
}
void CreateOpenGLWindow(HINSTANCE hInstance, int nCmdShow) {
    WNDCLASS wc;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = DefWindowProc; 
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"OpenGLClass";
    RegisterClass(&wc);

    hwnd = CreateWindow(L"OpenGLClass", L"OpenGL Application", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    EnableOpenGL(hwnd, &hDC, &hRC);
}
void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC) {
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    int format;

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    *hDC = GetDC(hwnd);
    format = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, format, &pfd);

    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}


void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
    DestroyWindow(hwnd);
}
void SetOrthoMatrixs(GLfloat* m, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nears, GLfloat fars, float zoom) {
    float width = right - left;
    float height = top - bottom;
    float zoomWidth = width / zoom;
    float zoomHeight = height / zoom;
    float centerX = (right + left) / 2.0f;
    float centerY = (top + bottom) / 2.0f;

    memset(m, 0, sizeof(GLfloat) * 16);
    m[0] = 2.0f / zoomWidth;
    m[5] = 2.0f / zoomHeight;
    m[10] = -2.0f / (fars - nears);
    m[12] = -(centerX * 2.0f) / zoomWidth;
    m[13] = -(centerY * 2.0f) / zoomHeight;
    m[14] = -(fars + nears) / (fars - nears);
    m[15] = 1.0f;
}
/*
GLuint LoadShaders(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}*/
void SetMVP(GLuint shaderProgram, GLfloat* mvp) {
    GLint mvpLocation = glGetUniformLocation(shaderProgram, "uMVPMatrix");
    if (mvpLocation != -1) {
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp);
    }
    else {
        return;
    }
}