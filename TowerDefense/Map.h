#pragma once
#include <vector>
#include <raylib.h>
#include <utility>
#include <string>

#define FRAMES 60

class Map
{

public:
    //Map and cellSize info
    int mapWidth = 20;
    int mapHeight = 20;
    int cellSize = 40;
    int borderSize = 1;
    
    //Struct that contains all the cell info
    struct Cell
    {
        bool wall;
        bool torret;
        int x;
        int y;
        bool visited = false;
        float globalGoal;
        float localGoal;
        std::vector<Cell*> neighbours;
        Cell* parent;
        std::string torretType;
    };
    Cell *cell = nullptr;
    Cell *cellStart = nullptr;
    Cell *cellEnd = nullptr;
    std::vector<Vector2> pathList;
    int wallPrice;

    //Coin System
    int coins;

    
    Map();
    void Update();
    void Draw();
    bool Path();
    void PlaceWall(int selectedCellX, int selectedCellY);
    void RestartMap();

};