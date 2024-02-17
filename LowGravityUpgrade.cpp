#include "LowGravityUpgrade.h"

// Constructor implementation
LowGravityUpgrade::LowGravityUpgrade(float x, float y, Color color) : Upgrade(x, y, color) {
    // Initialization specific to LowGravityUpgrade
}

// Override ApplyEffect to implement the effect of this upgrade
void LowGravityUpgrade::ApplyEffect(Character& character) {
    if (active){
    character.SetGravity(0.5f * character.GetGravity()); // Example: Halve the gravity
    }
}
