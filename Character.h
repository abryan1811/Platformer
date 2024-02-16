#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include <vector>

class Platform;

class Character {
public:
    Vector2 position;
    Vector2 velocity;
    float speed = 200.0f;
    bool isOnGround = false;

    Character();

    void Update(float deltaTime, const std::vector<Platform>& staticPlatforms, const std::vector<Platform>& movingPlatforms);

    // Apply gravity);
    void Draw();
private:
    float gravity = 980.0f;
    Rectangle getCollisionRec() const;
};

#endif 
