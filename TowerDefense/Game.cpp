#include "Game.h"

Game::Game() :  map(), enemy(), torret(map,enemy), roundGift(), torretTree()
{
    start = false;
    round = 1;
    nextRound = 2;
    playerHealth = 10;
    selectingGift = false;
}



void Game::UpdateGame()
{
    if(!selectingGift)
    {
        if(!torretTree.isTreeOpen())
        {
            if(!start)
            {
                StartGame();
                map.Update();
            }
            if(start)
            {
                enemy.Update(map.pathList, map.coins,playerHealth,round);
                torret.TorretAttack(enemy);

                if(playerHealth <= 0)
                {
                    RestartGame();
                }
            }
            
            torret.Update(map.coins);
            torretTree.OpenTorretTree();

            if(enemy.CheckEndOfRound())
            {
                if(round % 1 == 0 && round < 25)
                {
                    selectingGift = true;
                }
                round++;
                start = false;
            }
        }
        if(torretTree.isTreeOpen())
        {
            torretTree.Update(torret.torretTypeList,map.coins);
        }
        
    }
    if(selectingGift)
    {
        roundGift.Update(selectingGift,playerHealth,map.wallPrice,torret.torretTypeList, enemy.enemyTypeList);
        roundGift.ExitGift(selectingGift);       
    }
    torret.UpdatingTorretChanges();
}

void Game::DrawGame()
{


    map.Draw();
    enemy.Draw();
    torret.Draw();
    if(!start)
    {
        //draws the Start round button
        DrawRectangle(GetScreenWidth() - 350, GetScreenHeight() - 100, 250,50, WHITE);
        DrawText("Start Round", GetScreenWidth() - 325, GetScreenHeight() - 90, 30, BLACK);
    }
    //Draws Player health
    DrawRectangle(map.mapWidth * map.cellSize + 10, 50, 20,30,RED);
    DrawText(TextFormat("%i",playerHealth),map.mapWidth * map.cellSize + 40,50,30,WHITE);

    //Draws Rounds
    DrawText("Round",GetScreenWidth()-200,10,30,WHITE);
    DrawText(TextFormat("%i",round),GetScreenWidth()-160,50,25,WHITE);

    //Draws the amount of money
    DrawCircle(map.mapWidth * map.cellSize + 20, 20, 10, GOLD);
    DrawText(TextFormat("%i",map.coins),map.mapWidth * map.cellSize + 40, 7, 30, WHITE);

    torretTree.DrawTreeBox();


    if(selectingGift)
    {
        roundGift.Draw();
    }
    if(torretTree.isTreeOpen())
    {
        torretTree.Draw();
    }
}

void Game::RestartGame()
{
    map.RestartMap();
    torret.RestartTorret();
    enemy.RestartEnemy();
    start = false;
    round = 1;
    nextRound = 2;
    playerHealth = 10;
    selectingGift = false;
}

void Game::StartGame()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        int selectedCellX = mouseX;
        int selectedCellY = mouseY;
        if(selectedCellX >= GetScreenWidth() - 350 && selectedCellY >= GetScreenHeight() - 100 
        && selectedCellX <=GetScreenWidth() - 150 && selectedCellY <= GetScreenHeight() - 50)
        {
            start = true;
        }
    }
}
