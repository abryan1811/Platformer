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
    enum AnimationState {
            Idle,
            Running
        };
    
    Texture2D textureIdle;
    Texture2D textureRunning;
    int currentFrame = 0;
    float frameTime = 0; // Time since last frame change
    float frameChangeRate = 1.0f / 12.0f; // Change frame every 1/12th of a second
    int maxFrames = 4; // Default to idle frames count
    bool facingRight = true; // Character starts facing right
    AnimationState animationState = Idle; // Start with idle animation

    
    
};

#endif 
