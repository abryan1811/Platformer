#include "main.h"

    // Number of tiles horizontally and vertically
    int numTilesX = 200; 
    int numTilesY = 24;  

    //Window Width in tiles
    int WindowTilesX = 25;  
    
    // Size of each tile in pixels
    int tileSize = 32;

    // Calculate the window width and height
    int windowWidth = WindowTilesX * tileSize;
    int windowHeight = numTilesY * tileSize;
    char windowTitle[]{"Platformer"};

    // Variables for the image
    Texture2D worldMap;
    Vector2 mapPosition;

int main(int argc, char const *argv[])
{
    InitWindow(windowWidth, windowHeight, windowTitle);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {     
        BeginDrawing();
        ClearBackground(DARKBLUE); 

        // Set up the background
        worldMap = LoadTexture("Assets/levelplatformer.png");
        mapPosition = {0.0, 0.0};

        DrawTextureEx(worldMap, mapPosition, 0.0, 1.0, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


