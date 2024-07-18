#include "m_text.h"

int winWidth = 1920;
int winHeight = 1080;
const char letters[26][letterHeight][letterWidth + 1] = {
    {
        " 1 ",
        "101",
        "111",
        "101",
        "101"
    },
    {
        "110",
        "101",
        "110",
        "101",
        "110"
    },
    {
        "111",
        "100",
        "100",
        "100",
        "111"
    },
    {
        "110",
        "101",
        "101",
        "101",
        "110"
    },
    {
        "111",
        "100",
        "111",
        "100",
        "111"
    },
    {
        "111",
        "100",
        "111",
        "100",
        "100"
    },
    {
        "111",
        "100",
        "101",
        "101",
        "111"
    },
    {
        "101",
        "101",
        "111",
        "101",
        "101"
    },
    {
        "111",
        " 1 ",
        " 1 ",
        " 1 ",
        "111"
    },
    {
        " 11",
        "  1",
        "  1",
        "101",
        "111"
    },
    {
        "101",
        "101",
        "110",
        "101",
        "101"
    },
    {
        "100",
        "100",
        "100",
        "100",
        "111"
    },
    {
        "11111",
        "10101",
        "10101",
        "10101",
        "10101"
    },
    {
        "101",
        "111",
        "111",
        "101",
        "101"
    },
    {
        "111",
        "101",
        "101",
        "101",
        "111"
    },
    {
        "111",
        "101",
        "111",
        "100",
        "100"
    },
    {
        "111",
        "101",
        "101",
        "111",
        "  1"
    },
    {
        "110",
        "101",
        "110",
        "101",
        "101"
    },
    {
        "111",
        "100",
        "111",
        "001",
        "111"
    },
    {
        "111",
        " 1 ",
        " 1 ",
        " 1 ",
        " 1 "
    },
    {
        "101",
        "101",
        "101",
        "101",
        "111"
    },
    {
        "101",
        "101",
        "101",
        "101",
        " 1 "
    },
    {
        "10101",
        "10101",
        "10101",
        "10101",
        "11111"
    },
    {
        "101",
        "101",
        " 1 ",
        "101",
        "101"
    },
    {
        "101",
        "101",
        " 1 ",
        " 1 ",
        " 1 "
    },
    {
        "111",
        "  1",
        " 1 ",
        "1  ",
        "111"
    }
};
const float letterWidths[26] = {
    0.8,  // A
    0.7,  // B
    0.7,  // C
    0.7,  // D
    0.6,  // E
    0.6,  // F
    0.7,  // G
    0.7,  // H
    0.7,  // I
    0.5,  // J
    0.7,  // K
    0.6,  // L
    0.9,  // M
    0.8,  // N
    0.7,  // O
    0.6,  // P
    0.7,  // Q
    0.7,  // R
    0.6,  // S
    0.6,  // T
    0.7,  // U
    0.7,  // V
    1.0,  // W
    0.7,  // X
    0.7,  // Y
    0.6   // Z
};



void DrawLetter(float x, float y, char letter, float scale) {
    int index = letter - 'A';
    if (index < 0 || index > 25) return;

    for (int i = 0; i < letterHeight; ++i) {
        for (int j = 0; j < letterWidth; ++j) {
            if (letters[index][i][j] == '1') {
                glRectf(x + j * numberScale * scale, y - i * numberScale * scale,
                    x + (j + 1) * numberScale * scale, y - (i + 1) * numberScale * scale);
            }
        }
    }
}

void DrawText(const std::string& text, float startX, float startY, float letterSpacing) {
    float x = startX;
    float y = startY;

    for (char ch : text) {
        if (ch == ' ') {
            x += letterSpacing * spaceWidth;  
            continue;
        }
        if (ch >= 'A' && ch <= 'Z') {  
            DrawLetter(x, y, ch, 1);
            x += letterSpacing * letterWidths[ch - 'A']; 
        }
    }
}



void DrawAlphabet(float startX, float startY, float letterSpacing, float lineSpacing) {
    char letter = 'A';
    float x = startX;
    float y = startY;

    for (int i = 0; i < 26; ++i) {
        DrawLetter(x, y, letter + i, 1);
        x += letterSpacing * letterWidths[letter + i - 'A'];  
        if ((i + 1) % 13 == 0) {  
            y -= lineSpacing;
            x = startX;
        }
    }

}
Text::Text(const std::string& content, float x, float y, float scale, float letterSpacing)
        : content(content), x(x), y(y), scale(scale), letterSpacing(letterSpacing) {}




void Text::draw() {
    makeUppercase();
    float currentX = x;
    charPositions.clear();

    for (char ch : content) {
        if (ch == ' ') {
            currentX += letterSpacing * spaceWidth * scale;
            continue;
        }
        if (ch >= 'A' && ch <= 'Z') {
            int index = ch - 'A';
            DrawLetter(currentX, y, ch, scale);
            charPositions.push_back(std::make_pair(currentX, y)); 
            currentX += letterSpacing * letterWidths[index] * scale;
        }
    }
}
void Text::makeUppercase() {
    for (char& c : content) {
        c = std::toupper(static_cast<unsigned char>(c));
    }
}

bool Text::Clicked(float mouseX, float mouseY) {
    float screenMouseX = (mouseX + 1.0f) * 0.5f * winWidth;
    float screenMouseY = (1.0f - mouseY) * 0.5f * winHeight;
    float screenX = (x + 1.0f) * 0.5f * winWidth;
    float screenY = (1.0f - y) * 0.5f * winHeight;
    float currentX = screenX;
    for (size_t i = 0; i < content.length(); i++) {
        char ch = content[i];
        if (ch == ' ') {
            currentX += letterSpacing * spaceWidth * scale * winWidth * 0.5f;
            continue;
        }
        if (ch >= 'A' && ch <= 'Z') {
            int index = ch - 'A';
            float width = letterSpacing * letterWidths[index] * scale * winWidth * 0.5f;
            float height = letterHeight * scale * numberScale * winWidth * 0.5f;
            if (screenMouseX >= currentX && screenMouseX <= currentX + width &&
                screenMouseY >= screenY - height && screenMouseY <= screenY) {
                return true;
            }
            currentX += width;
        }
    }
    return false;
}
const int fontWidth = 3;
const int fontHeight = 5;
const GLchar font[][fontHeight][fontWidth + 1] = {
    {
        "111",
        "101",
        "101",
        "101",
        "111"
    },
    {
        "010",
        "110",
        "010",
        "010",
        "111"
    },
    {
        "111",
        "001",
        "111",
        "100",
        "111"
    },
    {
        "111",
        "001",
        "111",
        "001",
        "111"
    },
    {
        "101",
        "101",
        "111",
        "001",
        "001"
    },
    {
        "111",
        "100",
        "111",
        "001",
        "111"
    },
    {
        "111",
        "100",
        "111",
        "101",
        "111"
    },
    {
        "111",
        "001",
        "001",
        "001",
        "001"
    },
    {
        "111",
        "101",
        "111",
        "101",
        "111"
    },
    {
        "111",
        "101",
        "111",
        "001",
        "111"
    }
};
void DrawDigit(float x, float y, int digit) {
    if (digit < 0 || digit > 9) return;

    for (int i = 0; i < fontHeight; ++i) {
        for (int j = 0; j < fontWidth; ++j) {
            if (font[digit][i][j] == '1') {
                glRectf(x + j * numberScale, y - i * numberScale, x + (j + 1) * numberScale, y - (i + 1) * numberScale);
            }
        }
    }
}

void DrawScore(float x, float y, int score) {
    int digit1 = score / 10;
    int digit2 = score % 10;

    DrawDigit(x, y, digit1);
    DrawDigit(x + 4 * numberScale, y, digit2);
}

void DrawTimer(float x, float y, float time) {
    int minutes = static_cast<int>(time) / 60;
    int seconds = static_cast<int>(time) % 60;

    DrawDigit(x, y, minutes / 10);
    DrawDigit(x + 4 * numberScale, y, minutes % 10);

    glRectf(x + 8 * numberScale, y - 2 * numberScale, x + 9 * numberScale, y - 3 * numberScale);

    DrawDigit(x + 10 * numberScale, y, seconds / 10);
    DrawDigit(x + 14 * numberScale, y, seconds % 10);
}