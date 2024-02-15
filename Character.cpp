#include "Character.h"
#include "Platform.h"

Character::Character() {
    position = {350.0f, 280.0f}; // Starting position
    velocity = {0.0f, 0.0f}; // Initial velocity (0 so rectangle is still on startup)
}

void Character::Update(float deltaTime, const std::vector<Platform>& platforms) {
    // Apply gravity
    if (!isOnGround) {
        velocity.y += gravity * deltaTime;
    } else {
        velocity.y = 0;
    }

    // Reset ground check
    isOnGround = false;

    // Check collision with platforms
    Rectangle charRec = getCollisionRec();
    for (const auto& platform : platforms) {
        if (CheckCollisionRecs(charRec, platform.rect)) {
            isOnGround = true;
            position.y = platform.rect.y - charRec.height; // Characters position on the platform
            break;
        }
    }

    // Update position
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // Simple left and right movement (no jumping included yet)
    if (IsKeyDown(KEY_RIGHT)) position.x += speed * deltaTime;
    if (IsKeyDown(KEY_LEFT)) position.x -= speed * deltaTime;
}

void Character::Draw() {
    DrawRectangle(position.x, position.y, 20, 40, RED); // Character represented as a rectangle
}

Rectangle Character::getCollisionRec() const {
    return { position.x, position.y, 20.0f, 40.0f }; // This creates a collision around the character (same size as the rectangle)
}
