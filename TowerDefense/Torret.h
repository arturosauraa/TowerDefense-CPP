#pragma once
#include <vector>
#include "Map.h"
#include "Enemy.h"
#include <string>

class Torret
{
public:

    struct Torrets
    {
        int x;
        int y;
        int damage;
        int price;
        int distance;
        double speed;
        double timePassed;
        std::string torretName;
        Color color;
    };

    std::vector<Torrets> torretsList;
    int selectedWallX;
    int selectedWallY;
    bool selectedWall;
    std::string choosenTowerName;

    //Typee of torrets;
    Torrets archerTorret,cannonTorret,magicTorret,mortarTorret;
    std::vector<Torrets> torretTypeList;

    //torret rec for buy/sell
    Rectangle archerBox;
    Rectangle cannonBox;
    Rectangle magicBox;
    Rectangle mortarBox;


    Torret(Map& map, Enemy& enemy);
    void Update(int& coins);
    void Draw();

    void ChooseWall(int& coins);
    void ChooseTorret(int& coins);
    void PlaceTorret(int& coins, int selectedWallX, int selectedWallY);
    void DestroyTorret(Map::Cell& selectedCell,int& coins);
    void TorretAttack(Enemy& enemy);
    void RestartTorret();
    void UpdatingTorretChanges();
    void CheckTorretStats();
    

private:
    Map map;
    Enemy enemy;
    int statsX;
    int statsY;
    int torretStatsSelected;

};