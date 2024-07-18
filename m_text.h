#pragma once

#include <vector>
#include <string>
#include "OpenGLdata.h"

const int letterWidth = 5;
const int letterHeight = 5;
const float spaceWidth = 0.5;
const float numberScale = 0.01f;

extern int winWidth;
extern int winHeight;
extern const char letters[26][letterHeight][letterWidth + 1];
extern const float letterWidths[26];

void DrawLetter(float x, float y, char letter, float scale);
void DrawText(const std::string& text, float startX, float startY, float letterSpacing);
void DrawAlphabet(float startX, float startY, float letterSpacing, float lineSpacing);
void DrawDigit(float x, float y, int digit);
void DrawScore(float x, float y, int score);
void DrawTimer(float x, float y, float time);

class Text {
public:
    std::string content;
    float x, y;
    float scale;
    float letterSpacing;
    std::vector<std::pair<float, float>> charPositions;

    Text(const std::string& content, float x, float y, float scale, float letterSpacing);
    void draw();
    bool Clicked(float mouseX, float mouseY);
    void makeUppercase();
};
