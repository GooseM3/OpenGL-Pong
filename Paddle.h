#ifndef PADDLE_H
#define PADDLE_H

#include "OpenGLdata.h"
#include "Ball.h"

class Paddle {
public:
    float y;
    float speed;
    bool upPressed;
    bool downPressed;
    Paddle(float initialY, float initialSpeed);
    void UpdatePosition();
    void Draw(float x, GLuint shaderProgram) const;
    void UpdateAIPaddlePosition(const Ball& ball);
};

#endif
