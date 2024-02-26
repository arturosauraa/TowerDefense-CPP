#pragma once


#include "Torret.h"
#include "Map.h"
#include "Enemy.h"

class TorretTree
{

public:

    struct Tree
    {
        std::string name;
        std::vector<int> impList;
        std::vector<int> priceList;
        std::vector<bool> buyList;
        std::vector<Color> colorList;
        std::vector<Rectangle> boxImpList;
    };

    std::vector<Tree> archerList;
    std::vector<Tree> cannonList;
    std::vector<Tree> magicList;
    std::vector<Tree> mortarList;
    std::vector<std::vector<Tree>> allTreeList;

    std::vector<std::pair<Rectangle,Tree>> recTreeImp;

    struct TorretButton
    {
        int x;
        int y;
        int width;
        int height;
        Color backColor;
        Color torretColor;
        std::string name;
    };

    bool openTreeWindow;
    std::string selectedTreeName;

    int numberOfTreeList;
    int numberOfImpSelected;
    int numberOfImpLevelSelected;
    bool impSelected;


    Rectangle treeBox;
    Rectangle impBox;

    //Buttons
    Rectangle treeButton;
    Rectangle exitButton;
    Rectangle BuyButton;
    
    TorretButton archerButton;
    TorretButton cannonButton;
    TorretButton magicButton;
    TorretButton mortarButton;
    std::vector<TorretButton> buttonTorretList;
    std::vector<std::string> buttonTorretNameList;

    TorretTree();
    void Update(std::vector<Torret::Torrets>& torretTypeList,int& coins);
    void Draw();
    void ExitTorretTree();
    void OpenTorretTree();
    void DrawTreeBox();
    bool isTreeOpen();
    void DrawImprovements();
    void SelectTorret();
    void CreateTree();
    void SelectImp();
    void BuyImp(std::vector<Torret::Torrets>& torretTypeList,int& coins);



private:

    Map map;
    Enemy enemy;
    Torret torret;

    Rectangle firstLSBox;
    Rectangle secondLSBox;
    Rectangle thirdLSBox;
    Rectangle firstLDisBox;
    Rectangle secondLDisBox;
    Rectangle thirdLDisBox;
    Rectangle firstLDagBox;
    Rectangle secondLDagBox;
    Rectangle thirdLDagBox;


};