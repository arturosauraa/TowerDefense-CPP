#include <raylib.h>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Enemy.h"
#include "Torret.h"
#include "Game.h"

using namespace std;



int main()
{

    InitWindow(1200, 800, "Test");
    SetTargetFPS(60);


    Game game = Game();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        game.DrawGame();

        ClearBackground(BLACK);

        game.UpdateGame();
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
} 