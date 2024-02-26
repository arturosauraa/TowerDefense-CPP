#include "Map.h"
#include <raylib.h>
#include <math.h>
#include <list>

Map::Map()
{
    //Amount of money at the beggining
    coins = 5000;
    wallPrice = 10;


    //Size of the Cell which is the grid of 20x20
    cell = new Cell[mapWidth * mapHeight];

    //Creates all the cells in the map and set default info
    for(int x = 0; x <mapWidth;x++)
    {
        for( int y = 0; y<mapHeight;y++)
        {
            cell[y * mapWidth + x].x = x;
            cell[y * mapWidth + x].y = y;
            cell[y * mapWidth + x].wall = false;
            cell[y * mapWidth + x].torret = false;
            cell[y * mapWidth + x].visited = false;
            cell[y * mapWidth + x].parent = nullptr;
            cell[y * mapWidth + x].torretType = "none";
        }
    }

    //setting the neighbours of each cell by North/South/East/West
    for(int x = 0; x <mapWidth; x++)
    {
        for(int y = 0; y <mapHeight; y++)
        {
                if(y>0)
                    cell[y*mapWidth + x].neighbours.push_back(&cell[(y - 1) * mapWidth + (x + 0)]);
                if(y<mapHeight-1)
                    cell[y*mapWidth + x].neighbours.push_back(&cell[(y + 1) * mapWidth + (x + 0)]);
                if (x>0)
                    cell[y*mapWidth + x].neighbours.push_back(&cell[(y + 0) * mapWidth + (x - 1)]);
                if(x<mapWidth-1)
                    cell[y*mapWidth + x].neighbours.push_back(&cell[(y + 0) * mapWidth + (x + 1)]);
        }
    }
    //Cells representing the starting and end point
    cellStart = &cell[10];
    cellEnd = &cell[mapWidth * mapHeight - 10];
    Path();
}

void Map::Update()
{
    //Get Position of the cell Selected
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    int selectedCellX = mouseX / cellSize;
    int selectedCellY = mouseY / cellSize;

    //Changes the cell from floor to Wall
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        if(selectedCellX >= 0 && selectedCellX < mapWidth && selectedCellY >= 0 && selectedCellY < mapHeight)
        {
            PlaceWall(selectedCellX,selectedCellY);
        }
    }
}

void Map::PlaceWall(int selectedCellX, int selectedCellY)
{
    if(!cell[selectedCellY * mapWidth + selectedCellX].torret)
    {
        if(cell[selectedCellY * mapWidth + selectedCellX].wall == true)
        {
            cell[selectedCellY * mapWidth + selectedCellX].wall = false;
            coins += wallPrice / 2;
        }
        else if(coins >= wallPrice)
        {
            if(cell[selectedCellY * mapWidth + selectedCellX].wall == false)
            {
                cell[selectedCellY * mapWidth + selectedCellX].wall = true;
                if(!Path())
                {
                    cell[selectedCellY * mapWidth + selectedCellX].wall = false;
                }
                else
                {
                    coins -= wallPrice;
                }
            }
        }
    }
    Path();
}

void Map::Draw()
{
    for(int x = 0; x < mapWidth;x++)
    {
        for(int y = 0; y < mapHeight;y++)
        {
            //Draws a floor tile or wall tile depending if the wall bool is true or not
            DrawRectangle(x*cellSize + borderSize, y*cellSize + borderSize, 
            cellSize - borderSize, cellSize - borderSize, 
            cell[y * mapWidth + x].wall ? GRAY : DARKGREEN);
            //Draws the starting cell
            if(&cell[y * mapWidth + x] == cellStart)
                DrawRectangle(x*cellSize + borderSize, y*cellSize + borderSize, cellSize - borderSize, 
                cellSize - borderSize, GREEN);
            //Draws the ending cell
            if(&cell[y * mapWidth + x] == cellEnd)
                DrawRectangle(x*cellSize + borderSize, y*cellSize + borderSize, cellSize - borderSize, 
                cellSize - borderSize, RED);
        }
    }
    //Draws a line from the starting to end point by using the parent node
    if (cellEnd != nullptr)
    {
        pathList.clear();
        Cell *p = cellEnd;
        while (p->parent != nullptr)
        {
            //Draws the path
            DrawLine(p->x*cellSize + (cellSize + borderSize) / 2, p->y*cellSize + (cellSize + borderSize) / 2,
                p->parent->x*cellSize + (cellSize + borderSize) / 2, p->parent->y*cellSize + (cellSize + borderSize) / 2, YELLOW);
            
            p = p->parent;
            pathList.push_back((Vector2){p->x * cellSize + cellSize/2,p->y * cellSize + cellSize/2});
        }
    }



}

//A* Algorithm
bool Map::Path()
{
    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            cell[y*mapWidth + x].visited = false;
            cell[y*mapWidth + x].globalGoal = __FLT_MAX__;
            cell[y*mapWidth + x].localGoal = __FLT_MAX__;
            cell[y*mapWidth + x].parent = nullptr;	
        }
    }
    auto distance = [](Cell* a, Cell* b) 
    {
        return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
    };

    Cell *cellCurrent = cellStart;
    cellStart->localGoal = 0.0f;
    cellStart->globalGoal = distance(cellStart, cellEnd);

    std::list<Cell*> listNotTestedCells;
    listNotTestedCells.push_back(cellStart);

    while (!listNotTestedCells.empty() && cellCurrent != cellEnd)
    {

        listNotTestedCells.sort([](const Cell* lhs, const Cell* rhs){ return lhs->globalGoal < rhs->globalGoal; } );
        

        while(!listNotTestedCells.empty() && listNotTestedCells.front()->visited)
            listNotTestedCells.pop_front();


        if (listNotTestedCells.empty())
            break;

        cellCurrent = listNotTestedCells.front();
        cellCurrent->visited = true;

        for (auto nodeNeighbour : cellCurrent->neighbours)
        {

            if (!nodeNeighbour->visited && nodeNeighbour->wall == 0)
                listNotTestedCells.push_back(nodeNeighbour);

            float fPossiblyLowerGoal = cellCurrent->localGoal + distance(cellCurrent, nodeNeighbour);

            if (fPossiblyLowerGoal < nodeNeighbour->localGoal)
            {
                nodeNeighbour->parent = cellCurrent;
                nodeNeighbour->localGoal = fPossiblyLowerGoal;
                nodeNeighbour->globalGoal = nodeNeighbour->localGoal + distance(nodeNeighbour, cellEnd);
            }
        }	
    }
    if(listNotTestedCells.empty())
    {
        return false;
    } 
    else
    {
    return true;
    }
}

void Map::RestartMap()
{
    coins = 1000;
    
    for(int x = 0; x <mapWidth;x++)
    {
        for( int y = 0; y<mapHeight;y++)
        {
            cell[y * mapWidth + x].wall = false;
            cell[y * mapWidth + x].torret = false;
            cell[y * mapWidth + x].torretType = "none";
        }
    }
    Path();
}


