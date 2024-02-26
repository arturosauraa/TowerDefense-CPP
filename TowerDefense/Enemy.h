#pragma once
#include <vector>

#include "Map.h"
#include <raylib.h>

class Enemy
{

public:

    struct Enemies
    {
        std::string enemyName;
        double health;
        double x;
        double y;
        int posCell;
        double speed;
        int deathPrice;
        Color color;
        std::vector<Vector2> pathList;
    };

    Enemies enemies;
    std::vector<Enemies> listEnemies;
    int enemyAmount;
    Map map;
    int spawnEnemies;
    std::vector<Enemies> enemyTypeList;

    //Spawn Timing
    int spawnWaiting;
    int spawnTime;
    int heathlhWidthDisplay;
    
    Enemy();
    void Draw();
    void Update(std::vector<Vector2> & listPath, int& coins, int& playerHealth, int& round);
    void EnemyMovement(std::vector<Vector2> & listPath, int& playerHealth);
    void SpawnEnemy();
    void EnemyDeath(int& coins);
    void RestartEnemy();
    void EnemyRound();
    void EnemyTypes();
    bool CheckEndOfRound();

};