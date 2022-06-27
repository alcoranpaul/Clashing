#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
    // Window details
    const int windowDimensions = 384;
    InitWindow(windowDimensions, windowDimensions, "Clashing");
    SetTargetFPS(60);

    // Textures
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale = 4.0f;

    // Character
    Character knight(windowDimensions, windowDimensions);
    // Prop
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    // Enemy
    Enemy goblin{
        Vector2{300.f, 500.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy goblin2{
        Vector2{500.f, 850.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy goblin3{
        Vector2{600.f, 1200.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};
    Enemy slime2{
        Vector2{790.f, 900.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};
    Enemy slime3{
        Vector2{1000.f, 860.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &goblin2,
        &goblin3,
        &slime,
        &slime2,
        &slime3};
    // Number of Enemies
    int numEnemies = sizeof(enemies) / sizeof(enemies[0]);

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE); // Map

        // Draw the props
        for (Prop prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        // Win condition
        if (numEnemies == 0)
        {
            DrawText("You Win!", 55.f, 45.f, 60, RED);
            EndDrawing();
            continue;
        }
        else if (!knight.getAlive())
        {
            DrawText("Game OVER!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        // Knight
        knight.tick(GetFrameTime());
        // Check map bounds
        if (knight.getWorldPos().x < 0.0f ||
            knight.getWorldPos().y < 0.0f ||
            knight.getWorldPos().x + windowDimensions > map.width * mapScale ||
            knight.getWorldPos().y + windowDimensions > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // Props
        for (Prop prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        // Enemies
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                    numEnemies--;
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();
}