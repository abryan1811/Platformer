#include "Character.h"
#include "Platform.h"

Character::Character() {
    position = {350.0f, 280.0f}; // Starting position
    velocity = {0.0f, 0.0f}; // Initial velocity (0 so rectangle is still on startup)
}

void Character::Update(float deltaTime, const std::vector<Platform>& platforms, const std::vector<Platform>& movingPlatforms) {
    // Apply gravity if not on the ground
    if (!isOnGround) {
        velocity.y += gravity * deltaTime;
    }

    // Update position based on velocity
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // Check for ground and adjust position and velocity
    isOnGround = false;
    Rectangle charRec = getCollisionRec();
    for (const auto& platform : platforms) {
        if (CheckCollisionRecs(charRec, platform.rect)) {
            isOnGround = true;
            velocity.y = 0;
            position.y = platform.rect.y - charRec.height;
            break;
        }
    }

    // Special handling for moving platforms
    for (const auto& platform : movingPlatforms) {
        if (CheckCollisionRecs(charRec, platform.rect)) {
            isOnGround = true;
            velocity.y = 0;
            // Adjust character position to stand on the moving platform
            position.y = platform.rect.y - charRec.height;

            // If the platform is moving, make the character move along with it
            if (platform.movesUpAndDown) {
                // Adjust position.y based on platform's movement direction and speed
                if (platform.movingUp) {
                    position.y -= platform.movingSpeed * deltaTime;
                } else {
                    position.y += platform.movingSpeed * deltaTime;
                }
            }
            break;
        }
    }

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
