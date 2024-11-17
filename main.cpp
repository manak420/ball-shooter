#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream> // For file handling

// Struct for Target
struct Target {
    Vector2 position;
    float radius;
    Vector2 speed;
};


void ResetTarget(Target& target) {
    target.position = { static_cast<float>(GetScreenWidth() + rand() % 200), static_cast<float>(rand() % GetScreenHeight()) };
    target.speed = { -static_cast<float>(rand() % 3 + 2), 0 }; 
}

int main() {
    // Initialization
    const int screenWidth = 1200;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "shooting game");
    SetTargetFPS(60);


    const int targetCount = 8;
    std::vector<Target> targets(targetCount);
    srand(static_cast<unsigned>(time(0)));

    for (auto& target : targets) {
        target.radius =30.0f;
        ResetTarget(target);
    }

    // Game variables
    int score = 0;
    float timeLeft = 15.0f;

    while (!WindowShouldClose() && timeLeft > 0.0f) {

        timeLeft -= GetFrameTime();


        for (auto& target : targets) {
            target.position.x += target.speed.x;

            // Reset target if it moves off the screen
            if (target.position.x + target.radius < 0) {
                ResetTarget(target);
            }
        }


        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            for (auto& target : targets) {
                if (CheckCollisionPointCircle(mousePos, target.position, target.radius)) {
                    score += 1; 
                    ResetTarget(target);
                }
            }
        }









        BeginDrawing();
        ClearBackground(Color{ 85, 107, 47, 255 }); 

        for (const auto& target : targets) {
            DrawCircleV(target.position, target.radius, RED);
        }


        Vector2 mousePos = GetMousePosition();
        DrawCircleLines(mousePos.x, mousePos.y, 15, WHITE);
        DrawCircle(mousePos.x, mousePos.y, 5, WHITE);       


        DrawText(TextFormat("Time: %.1f", timeLeft), 10, 10, 20, WHITE);
        DrawText(TextFormat("Score: %d", score), 10, 40, 20, WHITE);
        

        EndDrawing();
    }

    
    std::string playerName;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Game Over", screenWidth / 2 - MeasureText("Game Over", 40) / 2, screenHeight / 2 - 50, 40, WHITE);
        DrawText(TextFormat("Final Score: %d", score), screenWidth / 2 - MeasureText(TextFormat("Final Score: %d", score), 20) / 2, screenHeight / 2, 20, WHITE);
        EndDrawing();
        // DrawText("Enter your name: In terminal", 10, 10, 30, WHITE);
        // DrawText(playerName.c_str(), 10, 50, 30, WHITE);
    }



    // std::cin>>playerName;
    // std::ofstream file("scores.csv", std::ios::app); 

    
    // if (file.is_open()) {
    //     file << playerName << "," << score << "\n";
    //     file.close();
    //     std::cout << "Your score has been saved to scores.csv!\n";
    // } 
    // else {
    //     std::cerr << "Failed to open scores.csv for writing.\n";
    // }


    CloseWindow(); 
    return 0;
}
