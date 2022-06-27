#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}
Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * knightScale,
        height * knightScale,
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // update Character animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if (frame > maxFrames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // Set world velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.0f ? x_direction = -1.f : x_direction = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // Draw Character
    Rectangle source{frame * width, 0.0f, x_direction * width, height};
    Rectangle dist{getScreenPos().x, getScreenPos().y, knightScale * width, knightScale * height};
    DrawTexturePro(texture, source, dist, Vector2{}, 0.0f, WHITE);
    // DrawRectangleLines(getCollisionRec().x,
    //                    getCollisionRec().y,
    //                    getCollisionRec().width,
    //                    getCollisionRec().height,
    //                    RED);
};
