#ifndef UPGRADE_H
#define UPGRADE_H

#include "raylib.h"

class Character; // Forward declaration

class Upgrade {
public:
    Vector2 position;
    Color color; // Add a Color attribute to upgrades (will later be an image)
    bool active;
    float duration; // Duration the upgrade is active for 
    float timer; // A timer to track how long the upgrade has been active (may be unnecessary)

    Upgrade(float x, float y, Color color) : position({x, y}), color(color), active(true), duration(10.0f), timer(0.0f) {}
    virtual ~Upgrade() = default; // Ensure a virtual destructor for proper cleanup

    void Update(float deltaTime) {
        if (active) {
            timer += deltaTime;
            if (timer >= duration) {
                active = false; // Deactivate the upgrade after the duration ends
            }
        }
    }
    void Draw() const {
        if (active) {
            DrawRectangleV(position, {20, 20}, BLUE);
        }
    }

    virtual void ApplyEffect(Character& character) = 0; // Pure virtual function

    Rectangle GetCollisionRec() const {
        return Rectangle{ position.x, position.y, 20, 20 };
    }
};

#endif // UPGRADE_H