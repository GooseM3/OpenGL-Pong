#pragma once

#include "OpenGLdata.h"
#include "Paddle.h"
#include "Ball.h"
#include "hud.h"
enum GameState { MENU, PLAYING, GAME_OVER };
enum Difficulty { EASY, MEDIUM, HARD };

class Game {
public:
    int leftPlayerScore = 0;
    int rightPlayerScore = 0;
    GameState currentState;
    Difficulty gameDifficulty;
    bool gameStarted;
    float elapsedTimeInSeconds;
    int countdownValue;
    int tickDuration;
    Paddle playerPaddle;
    Paddle aiPaddle;
    Ball ball;

    Game();
    void increase_score(bool player);
    void UpdateAIPaddlePosition();
    void increase_tickDuration();
    void DrawMenu();
    void Draw(GLuint shaderProgram);
};
