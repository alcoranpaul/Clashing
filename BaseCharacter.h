#include "raylib.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; };
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return alive; };
    void setAlive(bool isAlive) { alive = isAlive; };

protected:
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1: To the right; -1: to the left
    float x_direction = 1.f;

    // Animation variables
    float runningTime;
    float updateTime{1.0f / 12.0f}, speed{4.0f};
    int frame;
    int maxFrames{6};
    float width, height, knightScale = 4.0f;
    Vector2 velocity{};

private:
    bool alive = true;
};

#endif