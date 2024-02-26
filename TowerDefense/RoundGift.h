#pragma once


#include "Torret.h"
#include "Map.h"
#include "Enemy.h"


class RoundGift
{

public:
    struct Gift
    {
        double gift;
        std::string giftName;
        int timesUsed;
        bool positiveGift;
    };
    Gift gift1;
    Gift gift2;
    Gift gift3;
    std::vector<Gift> giftsList;
    std::vector<Gift> giftTypeList;
    bool giftsDecided;

    RoundGift();
    void Update(bool& selectingGift,int& PlayerHealth,int& wallPrice, std::vector<Torret::Torrets>& torretTypeList, std::vector<Enemy::Enemies>& enemyTypeList);
    void Draw();
    void RandomGift();
    void RecieveGift(int choiceNum,int& PlayerHealth,int& wallPrice, std::vector<Torret::Torrets>& torretTypeList, std::vector<Enemy::Enemies>& enemyTypeList);
    void GiftTypes();
    void maxGiftLimit();
    void ExitGift(bool& SelectingGift);

private:

    Map map;
    Enemy enemy;
    Torret torret;
    Rectangle exitButton;

    Rectangle firstGiftBox;
    Rectangle secondGiftBox;
    Rectangle thirdGiftBox;
    std::vector<Rectangle> giftBoxList;

};