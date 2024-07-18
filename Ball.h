#ifndef BALL_H
#define BALL_H
#include "Sound.h"
#include "OpenGLdata.h"

class Ball {
public:
    float x, y;
    float velocityX, velocityY;
    float size;

    Ball(float initialX, float initialY, float initialVelocityX, float initialVelocityY, float initialSize);
    void Reset();
    int UpdatePosition(float paddleY, float aiPaddleY);

    void Draw(GLuint shaderProgram) const;
};
#endif