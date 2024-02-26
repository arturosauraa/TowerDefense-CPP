#pragma once

#include "Map.h"
#include "Torret.h"
#include "Enemy.h"
#include "RoundGift.h"
#include "TorretTree.h"


class Game
{

public:
    Game();
    void UpdateGame();
    void DrawGame();
    void RestartGame();
    void StartGame();

    Map map;
    Enemy enemy;
    Torret torret;
    RoundGift roundGift;
    TorretTree torretTree;
    bool start;
    int round;
    int nextRound;
    int playerHealth;
    bool selectingGift;
};