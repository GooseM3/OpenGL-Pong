
#include "Hud.h"

void DrawCountdown(int countdownValue) {
    if (countdownValue > 0) {
        glColor3f(1.0f, 1.0f, 1.0f);
        DrawDigit(-0.02f, 0.0f, countdownValue);
    }
}

void DrawCenterLine() {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(8.0f);

    glBegin(GL_LINES);
    for (float y = -1.0f; y < 1.0f; y += 0.1f) {
        glVertex2f(0.0f, y);
        glVertex2f(0.0f, y + 0.05f);
    }
    glEnd();

    glPopMatrix();
}

void draw_hud(int leftPlayerScore, int rightPlayerScore, int elapsedTimeInSeconds) {
    DrawScore(-0.90f, 0.85f, leftPlayerScore);
    DrawScore(0.6f, 0.85f, rightPlayerScore);
    DrawTimer(-0.05f, 0.9f, elapsedTimeInSeconds);
};