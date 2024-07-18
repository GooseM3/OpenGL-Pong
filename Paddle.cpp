#include "Paddle.h"


Paddle::Paddle(float initialY, float initialSpeed) : y(initialY), speed(initialSpeed), upPressed(false), downPressed(false) {}

void Paddle::UpdatePosition() {
    if (upPressed && y < 1.0f) y += speed;
    if (downPressed && y > -1.0f) y -= speed;
}

void Paddle::Draw(float x, GLuint shaderProgram) const {
    GLfloat vertices[] = {
        x - 0.015f, y - 0.15f, 0.0f,
        x + 0.015f, y - 0.15f, 0.0f,
        x + 0.015f, y + 0.15f, 0.0f,
        x - 0.015f, y + 0.15f, 0.0f
    };

    glUseProgram(shaderProgram);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Paddle::UpdateAIPaddlePosition(const Ball& ball) {
    float targetY = ball.y;
    float aiPaddleSpeed = speed;

    if (this->y < targetY) {
        this->y += aiPaddleSpeed;
    }
    else if (this->y > targetY) {
        this->y -= aiPaddleSpeed;
    }

    if (this->y + 0.15f > 1.0f) this->y = 1.0f - 0.15f;
    if (this->y - 0.15f < -1.0f) this->y = -1.0f + 0.15f;
}
