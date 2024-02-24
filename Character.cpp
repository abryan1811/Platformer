#include "Character.h"
#include "Platform.h"

Character::Character() {
    position = {100.0f, 280.0f}; // Starting position
    velocity = {0.0f, 0.0f}; // Initial velocity (0 so rectangle is still on startup)
    textureIdle = LoadTexture("Assets/Knight_player/Idle_KG_1.png");
    textureRunning = LoadTexture("Assets/Knight_player/Walking_KG_1.png");
}

void Character::Update(float deltaTime, const std::vector<Platform>& platforms, const std::vector<Platform>& movingPlatforms) {
    // Apply gravity if not on the ground
    if (!isOnGround) {
        velocity.y += gravity * deltaTime;
    }
    else if (IsKeyDown(KEY_SPACE)){
        velocity.y = jumpVelocity;
        isOnGround=false;
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

    // Simple left and right movement
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) position.x += speed * deltaTime;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) position.x -= speed * deltaTime;

 bool isMoving = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A));
    animationState = isMoving ? Running : Idle;
    facingRight = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) ? true : (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) ? false : facingRight;

    // Animation frame update logic
    frameTime += deltaTime;
    if (frameTime >= frameChangeRate) {
        frameTime = 0;
        currentFrame = (currentFrame + 1) % maxFrames;
    }

    maxFrames = (animationState == Running) ? 7 : 4; // Update based on current animation
}
    

void Character::Draw() {
    Texture2D textureToUse = (animationState == Idle) ? textureIdle : textureRunning;
    Rectangle sourceRec = {currentFrame * (textureToUse.width / maxFrames), 0, facingRight ? (float)textureToUse.width / maxFrames : -(float)textureToUse.width / maxFrames, (float)textureToUse.height};
    Rectangle destRec = {position.x, position.y, 60, 40}; // Adjust size as needed

    DrawTexturePro(textureToUse, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
}

Rectangle Character::getCollisionRec() const {
    return { position.x, position.y, 60.0f, 40.0f }; // This creates a collision around the character (same size as the character texture)
}
