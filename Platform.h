#include "raylib.h"
#include "config.h"
#include <vector>

class Platform {
public:
    Rectangle rect;
    bool isSolid;

    // Constructor
    Platform(float x, float y, float width, float height);

    // Method to draw the platform
    void Draw();

    static std::vector<Platform> GetAllPlatforms();
};