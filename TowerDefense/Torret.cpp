#include "Torret.h"
#include <math.h>

Torret::Torret(Map& map, Enemy& enemy) : map(map), enemy(enemy)
{
    selectedWall = false;
    choosenTowerName = "none";

    archerBox = {(float)GetScreenWidth() - 350,(float)GetScreenHeight() / 3,100,50};
    cannonBox = {(float)GetScreenWidth() - 200,(float)GetScreenHeight() / 3,100,50};
    magicBox = {(float)GetScreenWidth() - 350,(float)GetScreenHeight() / 2,100,50};
    mortarBox = {(float)GetScreenWidth() - 200,(float)GetScreenHeight() / 2,100,50};

    archerTorret.torretName = "archer";
    archerTorret.price = 100;
    archerTorret.damage = 1;
    archerTorret.distance = 350;
    archerTorret.speed = 6;
    archerTorret.timePassed = 0;
    archerTorret.color = WHITE;
    
    cannonTorret.torretName = "cannon";
    cannonTorret.price = 200;
    cannonTorret.damage = 100;
    cannonTorret.distance = 200;
    cannonTorret.speed = 60;
    cannonTorret.timePassed = 0;
    cannonTorret.color = VIOLET;

    magicTorret.torretName = "magic";
    magicTorret.price = 350;
    magicTorret.damage = 300;
    magicTorret.distance = 150;
    magicTorret.speed = 120;
    magicTorret.timePassed = 0;
    magicTorret.color = LIME;

    mortarTorret.torretName = "mortar";
    mortarTorret.price = 400;
    mortarTorret.damage = 350;
    mortarTorret.distance = 500;
    mortarTorret.speed = 180;
    mortarTorret.timePassed = 0;
    mortarTorret.color = BROWN;

    torretTypeList.push_back(archerTorret);
    torretTypeList.push_back(cannonTorret);
    torretTypeList.push_back(magicTorret);
    torretTypeList.push_back(mortarTorret);

    statsX = GetScreenWidth() + 10;
    statsY = GetScreenHeight() + 10;
    torretStatsSelected = 0;
}

void Torret::Update(int& coins)
{

    if(selectedWall)
    {
        ChooseTorret(coins);
    }
    ChooseWall(coins);
    CheckTorretStats();
}

//draws the torrets and the buy/sell torrets
void Torret::Draw()
{
    //Draw distance of torret
    for(auto& torret : torretsList)
    {
        if(torret.x == selectedWallX * map.cellSize + map.cellSize/2 && torret.y == selectedWallY * map.cellSize + map.cellSize/2)
        {
           DrawCircleLines(torret.x, torret.y,torret.distance, WHITE);
        }
    }

    DrawRectangle(map.mapWidth * map.cellSize,0,400,GetScreenHeight(),BLACK);
    if (!torretsList.empty())
    {
        for (auto& torret : torretsList)
        {
            DrawCircle(torret.x, torret.y, 10, torret.color);
        }
    }

    if(selectedWall)
    {
        DrawRectangle(selectedWallX * map.cellSize, selectedWallY * map.cellSize, map.cellSize - map. borderSize, map.cellSize - map.borderSize, (Color){255,255,255,50});
    }





    DrawRectangle(archerBox.x,archerBox.y,archerBox.width,archerBox.height, BLUE);
    DrawRectangle(cannonBox.x,cannonBox.y,cannonBox.width,cannonBox.height, BLUE);
    DrawRectangle(magicBox.x,magicBox.y,magicBox.width,magicBox.height, BLUE);
    DrawRectangle(mortarBox.x,mortarBox.y,mortarBox.width,mortarBox.height, BLUE);

    DrawCircle(archerBox.x + archerBox.width/2,archerBox.y + archerBox.height/2,20, WHITE);
    DrawCircle(cannonBox.x + cannonBox.width/2,cannonBox.y + cannonBox.height/2,20, VIOLET);
    DrawCircle(magicBox.x + magicBox.width/2,magicBox.y + magicBox.height/2,20, LIME);
    DrawCircle(mortarBox.x + mortarBox.width/2,mortarBox.y + mortarBox.height/2,20, BROWN);

    DrawRectangle(statsX,statsY, 150, 100, BLACK);
    DrawRectangleLines(statsX,statsY, 150, 100, WHITE);
    DrawText(torretTypeList[torretStatsSelected].torretName.c_str(),statsX + 40,statsY + 3, 20, WHITE);
    DrawText("Price: ",statsX + 5, statsY + 25, 15, WHITE);
    DrawText(TextFormat("%i",torretTypeList[torretStatsSelected].price),statsX + 55, statsY + 25,15,WHITE);
    DrawText("Damage: ",statsX + 5, statsY + 40, 15, WHITE);
    DrawText(TextFormat("%i",torretTypeList[torretStatsSelected].damage),statsX + 65, statsY + 40,15,WHITE);
    DrawText("Distance: ",statsX + 5, statsY + 55, 15, WHITE);
    DrawText(TextFormat("%i",torretTypeList[torretStatsSelected].distance),statsX + 75, statsY + 55,15,WHITE);
    DrawText("Speed: ",statsX + 5, statsY + 70, 15, WHITE);
    DrawText(TextFormat("%.2f",torretTypeList[torretStatsSelected].speed / 60.0),statsX + 65, statsY + 70,15,WHITE);
    
}

//Chooses the wall that wants to be selected
void Torret::ChooseWall(int &coins)
{
    // Get Position of the cell Selected
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    int selectedCellX = mouseX / map.cellSize;
    int selectedCellY = mouseY / map.cellSize;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (selectedCellX >= 0 && selectedCellX < map.mapWidth && selectedCellY >= 0 && selectedCellY < map.mapHeight)
        {
            selectedWallX = selectedCellX;
            selectedWallY = selectedCellY;
            selectedWall = true;
        }
    }
}

//Chooses the torret that want to be added to the specific cell
void Torret::ChooseTorret(int& coins)
{
    // Get Position of the cell Selected
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (mouseX >= archerBox.x && mouseX < archerBox.x + archerBox.width 
        && mouseY >= archerBox.y && mouseY < archerBox.y + archerBox.height)
        {
            choosenTowerName = "archer";
            PlaceTorret(coins, selectedWallX, selectedWallY);
            selectedWall = false;
        }
        else if(mouseX >= cannonBox.x && mouseX < cannonBox.x + cannonBox.width 
        && mouseY >= cannonBox.y && mouseY < cannonBox.y + cannonBox.height)
        {
            choosenTowerName = "cannon";
            PlaceTorret(coins, selectedWallX, selectedWallY);
            selectedWall = false;
        }
        else if(mouseX >= magicBox.x && mouseX < magicBox.x + magicBox.width 
        && mouseY >= magicBox.y && mouseY < magicBox.y + magicBox.height)
        {
            choosenTowerName = "magic";
            PlaceTorret(coins, selectedWallX, selectedWallY);
            selectedWall = false;
        }
        else if(mouseX >= mortarBox.x && mouseX < mortarBox.x + mortarBox.width 
        && mouseY >= mortarBox.y && mouseY < mortarBox.y + mortarBox.height)
        {
            choosenTowerName = "mortar";
            PlaceTorret(coins, selectedWallX, selectedWallY);
            selectedWall = false;
        }
    }
}

//places the selceted torret in the cell of the map
void Torret::PlaceTorret(int& coins, int selectedWallX, int selectedWallY)
{
    Map::Cell& selectedCell = map.cell[selectedWallY * map.mapWidth + selectedWallX];

    for(auto& torret: torretTypeList)
    {
        if(choosenTowerName == torret.torretName)
        {
            if(selectedCell.torret && selectedCell.torretType == choosenTowerName)
            {
                DestroyTorret(selectedCell, coins);
                coins += torret.price / 2;    
            }
            else if (selectedCell.wall && !selectedCell.torret)
            {
                if(coins >= torret.price)
                {
                    selectedCell.torret = true;
                    selectedCell.torretType = torret.torretName;
                    Torrets torretCreated;
                    torretCreated.x = selectedWallX * map.cellSize + map.cellSize/2;
                    torretCreated.y = selectedWallY * map.cellSize + map.cellSize/2;
                    torretCreated.torretName = torret.torretName;
                    torretCreated.damage = torret.damage; 
                    torretCreated.distance = torret.distance;
                    torretCreated.price = torret.price;    
                    torretCreated.speed = torret.speed;    
                    torretCreated.timePassed = torret.timePassed;
                    torretCreated.color = torret.color;
                    torretsList.push_back(torretCreated);
                    coins -= torretCreated.price;
                }
            }
        }

    }
}

//Destroyes the torret in the specific cell
void Torret::DestroyTorret(Map::Cell& selectedCell,int &coins)
{
    selectedCell.torret = false;
    for(int i = 0; i <torretsList.size();i++)
    {
        int x = selectedCell.x * map.cellSize + map.cellSize/2;
        int y = selectedCell.y * map.cellSize + map.cellSize/2;
        if(x == torretsList[i].x && y == torretsList[i].y)
        {
            torretsList.erase(torretsList.begin() + i);
        }
    }
}

//this is the update of the torrect attack
void Torret::TorretAttack(Enemy& enemy)
{
    for(auto& torret : torretsList)
    {
        for(auto& enemyTarget: enemy.listEnemies)
        {
            float distanceEnemy = sqrt((torret.x - enemyTarget.x)*(torret.x - enemyTarget.x) + (torret.y - enemyTarget.y)*(torret.y - enemyTarget.y));
            if(torret.distance >= distanceEnemy)
            {
                if(torret.timePassed >= torret.speed)
                {
                    enemyTarget.health -= torret.damage;
                    torret.timePassed = 0;
                }
                else
                {
                    torret.timePassed += 1;
                }
                break;
            }
        }
    }
}

void Torret::RestartTorret()
{
    selectedWall = false;
    choosenTowerName = "none";
    torretsList.clear();
}

void Torret::UpdatingTorretChanges()
{
    if(!torretsList.empty())
    {
        for(auto & torret : torretsList)
        {
            for(auto & torretType : torretTypeList)
            {
                if(torret.torretName == torretType.torretName)
                {
                    torret.damage = torretType.damage;
                    torret.distance = torretType.distance;
                    torret.speed = torretType.speed;
                    torret.price = torretType.price; 
                }
            }
        }
    }
}

void Torret::CheckTorretStats()
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (mouseX >= archerBox.x && mouseX < archerBox.x + archerBox.width 
    && mouseY >= archerBox.y && mouseY < archerBox.y + archerBox.height)
    {
        statsX = mouseX;
        statsY = mouseY;
        torretStatsSelected = 0;
    }
    else if(mouseX >= cannonBox.x && mouseX < cannonBox.x + cannonBox.width 
    && mouseY >= cannonBox.y && mouseY < cannonBox.y + cannonBox.height)
    {
        statsX = mouseX;
        statsY = mouseY;
        torretStatsSelected = 1;
    }
    else if(mouseX >= magicBox.x && mouseX < magicBox.x + magicBox.width 
    && mouseY >= magicBox.y && mouseY < magicBox.y + magicBox.height)
    {
        statsX = mouseX;
        statsY = mouseY;
        torretStatsSelected = 2;
    }
    else if(mouseX >= mortarBox.x && mouseX < mortarBox.x + mortarBox.width 
    && mouseY >= mortarBox.y && mouseY < mortarBox.y + mortarBox.height)
    {
        statsX = mouseX;
        statsY = mouseY;
        torretStatsSelected = 3;
    }
    else 
    {
        statsX = GetScreenWidth() + 10;
        statsY = GetScreenHeight() + 10;
    }
    
    
}
