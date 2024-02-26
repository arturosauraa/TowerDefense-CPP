#include "Enemy.h"
#include <utility>

Enemy::Enemy()
{
    RestartEnemy();
}

void Enemy::Draw()
{
    if(!listEnemies.empty())    
    {
        for(auto& enemy : listEnemies)
        {
            heathlhWidthDisplay = enemy.health * 0.05;
            DrawCircle(enemy.x,enemy.y,10,enemies.color);
            DrawRectangle(enemy.x - 20, enemy.y - 20,heathlhWidthDisplay,5,RED);
        }
    }
}

void Enemy::Update(std::vector<Vector2> & listPath, int& coins, int& playerHealth,int& round)
{    
    if (!listPath.empty())
    {
        EnemyMovement(listPath,playerHealth);
        SpawnEnemy();
        EnemyDeath(coins);
    }
}

void Enemy::EnemyRound()
{
    enemyAmount++;
    listEnemies.clear();
    for(int i = 0; i < enemyAmount; i++)
    {
        switch((rand() % 4) + 1)
        {
            case 1:
                listEnemies.push_back(enemyTypeList[0]);
                break;
            case 2:
                listEnemies.push_back(enemyTypeList[1]);
                break;
            case 3:
                listEnemies.push_back(enemyTypeList[2]);
                break;
            case 4:
                listEnemies.push_back(enemyTypeList[3]);
                break;
            default:
                listEnemies.push_back(enemyTypeList[0]);
                break;
        }
    }
}

void Enemy::EnemyMovement(std::vector<Vector2> &listPath, int& playerHealth)
{
    if (!listEnemies.empty())
    {
        for (int i = 0; i < spawnEnemies; i++)
        {
            if (listEnemies[i].posCell < listPath.size() - 1) // Ensure there are still points in the path
            {
                Vector2 currentPos = { listEnemies[i].x, listEnemies[i].y };
                Vector2 targetPos = listPath[listEnemies[i].posCell + 1];

                // Calculate the direction of movement
                Vector2 direction = { 0, 0 };
                if (targetPos.x != currentPos.x)
                {
                    direction.x = (targetPos.x > currentPos.x) ? listEnemies[i].speed : -listEnemies[i].speed;
                }
                else if (targetPos.y != currentPos.y)
                {
                    direction.y = (targetPos.y > currentPos.y) ? listEnemies[i].speed : -listEnemies[i].speed;
                }

                // Move the enemy
                listEnemies[i].x += direction.x;
                listEnemies[i].y += direction.y;

                // Check if the enemy reached the target position
                if (listEnemies[i].x == targetPos.x && listEnemies[i].y == targetPos.y)
                {
                    listEnemies[i].posCell++;
                }
            }

            // Check if the enemy reached the end of the path
            if (!listEnemies.empty() && listEnemies[i].posCell >= listPath.size() - 1)
            {
                // Handle reaching the end of the path (e.g., reaching the target)
                // Remove the enemy, update game state, etc.
                listEnemies.erase(listEnemies.begin() + i);
                spawnEnemies--;
                playerHealth--;
            }
        }
    }
}

void Enemy::SpawnEnemy()
{
    // Check for spawning new enemies
    //Waits 1.5 seconds which is 90 frames
    if (!listEnemies.empty() && spawnEnemies < listEnemies.size())
    {
        spawnWaiting++;
        if(spawnWaiting >= spawnTime)
        {
            spawnEnemies++;
            spawnWaiting = 0;
        }
    }
}

void Enemy::EnemyDeath(int& coins)
{
    if(!listEnemies.empty())
    {
        for(int i = 0; i < listEnemies.size();i++)
        {
            if(listEnemies[i].health <= 0)
            {
                listEnemies.erase(listEnemies.begin() + i);
                coins += listEnemies[i].deathPrice;
            } 
        }
    }
}

void Enemy::EnemyTypes()
{
    Enemies enemy1;
    Enemies enemy2;
    Enemies enemy3;
    Enemies enemy4;

    enemy1.health = 500;
    enemy1.x = map.cellEnd->x * map.cellSize + map.cellSize/2;
    enemy1.y = map.cellEnd->y * map.cellSize + map.cellSize/2;
    enemy1.posCell = 0;
    enemy1.speed = 4;
    enemy1.color = YELLOW;
    enemy1.deathPrice = 10;
    
    enemy2.health = 1000;
    enemy2.x = map.cellEnd->x * map.cellSize + map.cellSize/2;
    enemy2.y = map.cellEnd->y * map.cellSize + map.cellSize/2;
    enemy2.posCell = 0;
    enemy2.speed = 2;
    enemy2.color = MAROON;
    enemy2.deathPrice = 10;
    
    enemy3.health = 2000;
    enemy3.x = map.cellEnd->x * map.cellSize + map.cellSize/2;
    enemy3.y = map.cellEnd->y * map.cellSize + map.cellSize/2;
    enemy3.posCell = 0;
    enemy3.speed = 1;
    enemy3.color = BEIGE;
    enemy3.deathPrice = 10;
    
    enemy4.health = 5000;
    enemy4.x = map.cellEnd->x * map.cellSize + map.cellSize/2;
    enemy4.y = map.cellEnd->y * map.cellSize + map.cellSize/2;
    enemy4.posCell = 0;
    enemy4.speed = 0.5;
    enemy4.color = VIOLET;
    enemy4.deathPrice = 10;

    enemyTypeList.push_back(enemy1);
    enemyTypeList.push_back(enemy2);
    enemyTypeList.push_back(enemy3);
    enemyTypeList.push_back(enemy4);

}

bool Enemy::CheckEndOfRound()
{
    if(listEnemies.empty())
    {
        EnemyRound();
        return true;
    }
    return false;
}

void Enemy::RestartEnemy()
{
    spawnWaiting = 0;
    spawnTime = 90; // number of frames to wait == 1.5 seconds
    enemyAmount = 5;
    for(int i = 0; i< enemyAmount;i++)
    {
        enemies.health = 1000;
        enemies.x = map.cellEnd->x * map.cellSize + map.cellSize/2;
        enemies.y = map.cellEnd->y * map.cellSize + map.cellSize/2;
        enemies.posCell = 0;
        enemies.speed = 1;
        enemies.color = YELLOW;
        enemies.deathPrice = 10;
        listEnemies.push_back(enemies);
    }
    spawnEnemies = 1;
    EnemyTypes();
}



