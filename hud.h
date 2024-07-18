#ifndef HUD_H
#define HUD_H

#include "OpenGLdata.h"
#include "m_text.h"

void DrawCountdown(int countdownValue);

void DrawCenterLine();
void draw_hud(int leftPlayerScore, int rightPlayerScore, int elapsedTimeInSeconds);


#endif