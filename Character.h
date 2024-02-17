#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include <vector>

class Platform;

class Character {
public:
    Vector2 position;
    Vector2 velocity;
    float gravity = 980.0f;
    float jumpVelocity = -300.f;
    float speed = 200.0f;
    bool isOnGround = false;

    Character();

    void Update(float deltaTime, const std::vector<Platform>& staticPlatforms, const std::vector<Platform>& movingPlatforms);
    
    // Apply gravity);
    float GetGravity() const { return gravity; }
    void SetGravity(float newGravity) { gravity = newGravity; }
    
    void Draw();
    Rectangle getCollisionRec() const;
private:
    
};

#endif 
