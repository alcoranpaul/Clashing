#include "raylib.h"
class Prop
{
private:
    Vector2 worldPos{};
    Texture2D texture{};
    float scale = 4.f;

public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 knightPos);
    Rectangle getCollisionRec(Vector2 knightPos);
};