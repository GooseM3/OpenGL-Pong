#include "Game.h"
#include <cstring>  
#include  <iostream>

Game::Game()
    : currentState(PLAYING), gameDifficulty(MEDIUM), gameStarted(false),
    elapsedTimeInSeconds(0.0f), countdownValue(3), tickDuration(16),
    playerPaddle(0.0f, 0.01f), aiPaddle(0.0f, 0.01f),
    ball(0.0f, 0.0f, 0.02f, 0.02f, 0.05f) {}

void Game::increase_score(bool player) {
    if (player) {
        this->leftPlayerScore++;
    }
    else {
        this->rightPlayerScore++;
    }
}

void Game::UpdateAIPaddlePosition() {
    float targetY = ball.y;
    float aiPaddleSpeed = aiPaddle.speed;

    switch (gameDifficulty) {
    case EASY:
        aiPaddleSpeed *= 0.6f;
        break;
    case MEDIUM:
        break;
    case HARD:
        aiPaddleSpeed *= 1.5f;
        break;
    }

    if (aiPaddle.y < targetY) {
        aiPaddle.y += aiPaddleSpeed;
    }
    else if (aiPaddle.y > targetY) {
        aiPaddle.y -= aiPaddleSpeed;
    }

    if (aiPaddle.y + 0.15f > 1.0f) aiPaddle.y = 1.0f - 0.15f;
    if (aiPaddle.y - 0.15f < -1.0f) aiPaddle.y = -1.0f + 0.15f;
}

void Game::increase_tickDuration() {
    this->tickDuration += 2;
}

void Game::DrawMenu() {
    glColor3f(1.0f, 1.0f, 1.0f);
    Text title("PONG GAME", -0.3f, 0.3f, 1.f, 0.065);
    Text Menu("Press right arrow to Start", -0.4f, 0.1f, 1.f, 0.065);
    Text Easy("Press R for Easy", -0.4f, -0.1f, 1.f, 0.065);
    Text Medium("Press T for Medium", -0.4f, -0.2f, 1.f, 0.065);
    Text Hard("Press S for Hard", -0.4f, -0.3f, 1.f, 0.065);
    Text Options("Press O for Options", -0.4f, -0.4f, 1.f, 0.065);

    title.draw();
    Menu.draw();
    Easy.draw();
    Medium.draw();
    Hard.draw();
    Options.draw();
}

void Game::Draw(GLuint shaderProgram) {
    if (currentState == MENU) {
        DrawMenu();
    }
    else if (currentState == PLAYING) {
        if (!gameStarted) {
            countdownValue = 3.75 - static_cast<int>(elapsedTimeInSeconds);
            DrawCountdown(countdownValue);
            if (countdownValue <= 0) {
                gameStarted = true;
                elapsedTimeInSeconds = 0.0f;
            }
        }
        else {
            DrawCenterLine(); 
            playerPaddle.UpdatePosition();
            UpdateAIPaddlePosition();
            int score = ball.UpdatePosition(playerPaddle.y, aiPaddle.y);
            if (score == 1) {
               Game::increase_score(true);
            }
            else if (score == 2) {
                Game::increase_score(false);
            }
            DrawText("HELLO   WORLD", -0.8f, 0.5f, 0.055f);

            GLfloat ortho[16];
            SetOrthoMatrixs(ortho, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, zoomFactor); 

            GLfloat leftPaddleX = -1.0f / zoomFactor + 0.1f;
            GLfloat rightPaddleX = 1.0f / zoomFactor - 0.1f;

            GLfloat mvp[16];
            memcpy(mvp, ortho, sizeof(mvp));
            SetMVP(shaderProgram, mvp); 
            playerPaddle.Draw(leftPaddleX, shaderProgram);

            memcpy(mvp, ortho, sizeof(mvp));
            SetMVP(shaderProgram, mvp);
            aiPaddle.Draw(rightPaddleX, shaderProgram);

            memcpy(mvp, ortho, sizeof(mvp));
            SetMVP(shaderProgram, mvp);
            ball.Draw(shaderProgram);

            DrawScore(-0.90f, 0.85f, this->leftPlayerScore); 
            DrawScore(0.6f, 0.85f, this->rightPlayerScore);
            
            
            
            
            std::cerr << "Left player score: " << this->leftPlayerScore << std::endl;
            //std::cerr << "Right player score: " << this->rightPlayerScore << std::endl;
            DrawTimer(-0.05f, 0.9f, elapsedTimeInSeconds);
        }
    }
}
