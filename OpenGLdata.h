#ifndef OPENGLDATA_H
#define OPENGLDATA_H

#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "user32.lib")
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30

typedef void (WINAPI* PFNGLDELETEPROGRAMPROC)(GLuint program);
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;



typedef char GLchar;
typedef GLuint(WINAPI* PFNGLCREATESHADERPROC)(GLenum type);
typedef void (WINAPI* PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
typedef void (WINAPI* PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef GLuint(WINAPI* PFNGLCREATEPROGRAMPROC)(void);
typedef void (WINAPI* PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (WINAPI* PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void (WINAPI* PFNGLUSEPROGRAMPROC)(GLuint program);
typedef void (WINAPI* PFNGLDELETESHADERPROC)(GLuint shader);
typedef void (WINAPI* PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef GLint(WINAPI* PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar* name);

extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

void LoadOpenGLFunctions();
void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC);
void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC);
void CreateOpenGLWindow(HINSTANCE hInstance, int nCmdShow);

void SetOrthoMatrixs(GLfloat* m, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nears, GLfloat fars, float zoom);

extern float zoomFactor;
void SetMVP(GLuint shaderProgram, GLfloat* mvp);
#endif 
OPENGLDATA_H
