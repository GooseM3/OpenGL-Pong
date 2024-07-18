#include "Ball.h"

Ball::Ball(float initialX, float initialY, float initialVelocityX, float initialVelocityY, float initialSize)
    : x(initialX), y(initialY), velocityX(initialVelocityX), velocityY(initialVelocityY), size(initialSize) {}


void Ball::Reset() {
    x = 0.0f;
    y = 0.0f;
    velocityX = (rand() % 2 == 0 ? 0.02f : -0.02f);
    velocityY = (rand() % 2 == 0 ? 0.02f : -0.02f);
};

int Ball::UpdatePosition(float paddleY, float aiPaddleY) {
    x += velocityX;
    y += velocityY;

    if (x + size > 1.0f || x - size < -1.0f) {
        if (x + size > 1.0f) {
            PlayBeepSound();
            Reset();
            return 2;
        }
        if (x - size < -1.0f) {
            PlayBeepSound();
            Reset();
            return 1;
        }
    }

    if ((x - size < -0.85f && y < paddleY + 0.15f && y > paddleY - 0.15f) ||
        (x + size > 0.85f && y < aiPaddleY + 0.15f && y > aiPaddleY - 0.15f)) {
        velocityX = -velocityX;
        PlayBeepSound();
    }

    if (y + size > 1.0f || y - size < -1.0f) {
        velocityY = -velocityY;
        PlayBeepSound();
    }
    return 0;
}

void Ball::Draw(GLuint shaderProgram) const {
    float scale = 0.5f;
    GLfloat vertices[] = {
        x - size * scale, y - size * scale, 0.0f,
        x + size * scale, y - size * scale, 0.0f,
        x + size * scale, y + size * scale, 0.0f,
        x - size * scale, y + size * scale, 0.0f
    };
    glUseProgram(shaderProgram);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}