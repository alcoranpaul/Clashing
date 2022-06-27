#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
    : windowWidth(winWidth), windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
};

Vector2 Character::getScreenPos()
{
    return Vector2{(static_cast<float>(windowWidth) / 2.0f) - (knightScale * (0.5f * width)),
                   (static_cast<float>(windowHeight) / 2.0f) - (knightScale * (0.5f * height))};
}

void Character::tick(float deltaTime)
{
    if (!getAlive())
        return;

    // Map movement
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) // Left
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) // Right
        velocity.x += 1.0;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) // Down
        velocity.y += 1.0;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) // Up
        velocity.y -= 1.0;
    BaseCharacter::tick(deltaTime);

    // Sword
    Vector2 origin{}, offset{};
    float rotation;
    if (x_direction > 0.f)
    {
        origin = {0.f, weapon.height * knightScale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * knightScale,
            weapon.width * knightScale,
            weapon.height * knightScale};
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f;
    }
    else
    {
        origin = {weapon.width * knightScale, weapon.height * knightScale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * knightScale,
            getScreenPos().y + offset.y - weapon.height * knightScale,
            weapon.width * knightScale,
            weapon.height * knightScale};
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0.f;
    }
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * x_direction, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * knightScale, weapon.height * knightScale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    // DrawRectangleLines(
    //     weaponCollisionRec.x,
    //     weaponCollisionRec.y,
    //     weaponCollisionRec.width,
    //     weaponCollisionRec.height,
    //     RED);
};

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setAlive(false);
    }
}