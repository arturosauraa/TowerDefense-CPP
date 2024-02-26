#include "TorretTree.h"

TorretTree::TorretTree() : map(), enemy(), torret(map,enemy)
{
    openTreeWindow = false;
    treeButton = {(float)GetScreenWidth() - 300, (float)GetScreenHeight() - 250, 150,50};

    //tree layout
    treeBox = {50, 150,700,400};
    impBox = {150, 150,600,400};

    //Exit and Buy button
    exitButton = {725,150,25,25};
    BuyButton = {430, 490,100,50};
    

    //Torret Buttons
    buttonTorretList = {archerButton,cannonButton,magicButton,mortarButton};
    buttonTorretNameList = {"Archer Tree","Cannon Tree", "Magic Tree", "Mortar Tree"};
    int i= 150;
    int j= 0;
    std::vector<Color> torretColorList = {WHITE,VIOLET,LIME,BROWN};
    for(auto& button: buttonTorretList)
    {
        button.x = 50;
        button.y = i;
        button.width = 100;
        button.height = 100;
        button.backColor = BLACK;
        button.torretColor = torretColorList[j];
        button.name = buttonTorretNameList[j];
        i += 100;
        j++;
    }

    CreateTree();
    numberOfTreeList = 0;
    selectedTreeName = "";

    

    recTreeImp.push_back(std::make_pair(firstLSBox,allTreeList[numberOfTreeList][0]));
    recTreeImp.push_back(std::make_pair(secondLSBox,allTreeList[numberOfTreeList][0]));
    recTreeImp.push_back(std::make_pair(thirdLSBox,allTreeList[numberOfTreeList][0]));
    recTreeImp.push_back(std::make_pair(firstLDisBox,allTreeList[numberOfTreeList][1]));
    recTreeImp.push_back(std::make_pair(secondLDisBox,allTreeList[numberOfTreeList][1]));
    recTreeImp.push_back(std::make_pair(thirdLDisBox,allTreeList[numberOfTreeList][1]));
    recTreeImp.push_back(std::make_pair(firstLDagBox,allTreeList[numberOfTreeList][2]));
    recTreeImp.push_back(std::make_pair(secondLDagBox,allTreeList[numberOfTreeList][2]));
    recTreeImp.push_back(std::make_pair(thirdLDagBox,allTreeList[numberOfTreeList][2]));

    impSelected = false;

}
//Allows the user to exit the tree window
void TorretTree::ExitTorretTree()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        if(mouseX >= 725 && mouseY >= 150 
        && mouseX <=750 && mouseY <= 175)
        {
            selectedTreeName = "";
            openTreeWindow = false;
        }
    }
}
//Opens the tree windows - this function is called in the game.cpp
void TorretTree::OpenTorretTree()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        if(mouseX >= treeButton.x && mouseY >= treeButton.y 
        && mouseX <=treeButton.x + treeButton.width && mouseY <= treeButton.y + treeButton.height)
        {
            openTreeWindow = true;
        }
    }
}
//Thid draws the button to open the tree window bellow the torrets buttons
void TorretTree::DrawTreeBox()
{
    //Draw TreeBox
    DrawRectangle(treeButton.x,treeButton.y,treeButton.width,treeButton.height,BLUE);
    DrawText("Torret Tree",treeButton.x + 10,treeButton.y + 10,20,WHITE);
}
//this checks if the tree window is open or not
bool TorretTree::isTreeOpen()
{
    if(openTreeWindow) return true;
    return false;
}

void TorretTree::Update(std::vector<Torret::Torrets>& torretTypeList,int& coins)
{
    ExitTorretTree();
    SelectTorret();
    SelectImp();
    BuyImp(torretTypeList,coins);
}

void TorretTree::Draw()
{
    //Tree BOX Drawned
    DrawRectangle(treeBox.x,treeBox.y,treeBox.width,treeBox.height,BLACK);
    DrawText(selectedTreeName.c_str(),impBox.x + impBox.width/2 - 100,impBox.y + 10, 30, WHITE);
    
    //X exit Torret Tree
    DrawRectangle(exitButton.x,exitButton.y,exitButton.width,exitButton.height,RED);
    DrawRectangleLines(exitButton.x,exitButton.y,exitButton.width,exitButton.height,WHITE);
    DrawText("x",732,152,20,WHITE);

    //Draw Torret Buttons
    for(auto& button : buttonTorretList)
    {
        DrawRectangle(button.x,button.y,button.width,button.height,button.backColor);
        DrawCircle(button.x + button.width/2,button.y + button.height/2,20,button.torretColor);
        DrawRectangleLines(button.x,button.y,button.width,button.height,WHITE);
    }

    DrawImprovements();

    //Draws the exterior lines after everything
    DrawRectangleLines(treeBox.x,treeBox.y,treeBox.width,treeBox.height,WHITE);
    DrawRectangleLines(impBox.x,impBox.y,impBox.width,impBox.height,WHITE);
}
void TorretTree::SelectImp()
{
    if(!impSelected)
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            int i = 0;
            for(auto& imp : allTreeList[numberOfTreeList])
            {
                if(mouseX >= imp.boxImpList[0].x && mouseX <= imp.boxImpList[0].x + imp.boxImpList[0].width
                && mouseY >= imp.boxImpList[0].y && mouseY <= imp.boxImpList[0].y + imp.boxImpList[0].height)
                {
                    if(!imp.buyList[0])
                    {
                        numberOfImpLevelSelected = 0;
                        numberOfImpSelected = i;
                        impSelected = true;
                    }
                }
                if(mouseX >= imp.boxImpList[1].x && mouseX <= imp.boxImpList[1].x + imp.boxImpList[1].width
                && mouseY >= imp.boxImpList[1].y && mouseY <= imp.boxImpList[1].y + imp.boxImpList[1].height)
                {
                    if(!imp.buyList[1] && imp.buyList[0])
                    {
                        numberOfImpLevelSelected = 1;
                        numberOfImpSelected = i;
                        impSelected = true;
                    }
                }
                if(mouseX >= imp.boxImpList[2].x && mouseX <= imp.boxImpList[2].x + imp.boxImpList[2].width
                && mouseY >= imp.boxImpList[2].y && mouseY <= imp.boxImpList[2].y + imp.boxImpList[2].height)
                {
                    if(!imp.buyList[2] && imp.buyList[1] && imp.buyList[0])
                    {
                        numberOfImpLevelSelected = 2;
                        numberOfImpSelected = i;
                        impSelected = true;
                    }
                }
                i++;
            }
        }
    }
    
}

void TorretTree::BuyImp(std::vector<Torret::Torrets>& torretTypeList,int& coins)
{
    if(impSelected)
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            if(mouseX >= BuyButton.x && mouseX <= BuyButton.x + BuyButton.width
            && mouseY >= BuyButton.y && mouseY <= BuyButton.y + BuyButton.height)
            {
                if(allTreeList[numberOfTreeList][numberOfImpSelected].priceList[numberOfImpLevelSelected] <= coins)
                {
                    for(auto& torret : torretTypeList)
                    {
                        if(numberOfImpSelected == 0)
                        {
                            torret.speed += allTreeList[numberOfTreeList][numberOfImpSelected].impList[numberOfImpLevelSelected];
                            impSelected = false;
                            allTreeList[numberOfTreeList][numberOfImpSelected].buyList[numberOfImpLevelSelected] = true;
                            allTreeList[numberOfTreeList][numberOfImpSelected].colorList[numberOfImpLevelSelected] = WHITE;
                        }
                        if(numberOfImpSelected == 1)
                        {
                            torret.distance += allTreeList[numberOfTreeList][numberOfImpSelected].impList[numberOfImpLevelSelected];
                            impSelected = false;
                            allTreeList[numberOfTreeList][numberOfImpSelected].buyList[numberOfImpLevelSelected] = true;
                            allTreeList[numberOfTreeList][numberOfImpSelected].colorList[numberOfImpLevelSelected] = WHITE;
                        }
                        if(numberOfImpSelected == 2)
                        {
                            torret.damage += allTreeList[numberOfTreeList][numberOfImpSelected].impList[numberOfImpLevelSelected];
                            impSelected = false;
                            allTreeList[numberOfTreeList][numberOfImpSelected].buyList[numberOfImpLevelSelected] = true;
                            allTreeList[numberOfTreeList][numberOfImpSelected].colorList[numberOfImpLevelSelected] = WHITE;
                        }
                    }
                    coins -= allTreeList[numberOfTreeList][numberOfImpSelected].priceList[numberOfImpLevelSelected]; 
                }
            }
        }
    }
}

void TorretTree::SelectTorret()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        for(auto& button : buttonTorretList)
        {
            if(mouseX >= button.x && mouseX <= button.x + button.width
            && mouseY >= button.y && mouseY <= button.y + button.height)
            {
                button.backColor = Color{130, 130, 130, 100};
                selectedTreeName = button.name;
                if(button.name == "Archer Tree")
                {
                    numberOfTreeList = 0;
                }
                else if(button.name == "Cannon Tree")
                {
                    numberOfTreeList = 1;
                }
                else if(button.name == "Magic Tree")
                {
                    numberOfTreeList = 2;
                }
                else if(button.name == "Mortar Tree")
                {
                    numberOfTreeList = 3;
                }
            }
            else
            {
                button.backColor = BLACK;
            }
        }
    }
}



void TorretTree::DrawImprovements()
{
    if(selectedTreeName != "")
    {
        //Text Indicating Imp
        DrawText("Speed",impBox.x + 10, impBox.y + 90, 20, WHITE);
        DrawText("Distance",impBox.x + 10, impBox.y + 190, 20, WHITE);
        DrawText("Damage",impBox.x + 10, impBox.y + 290, 20, WHITE);
        //Draw Buy Button
        DrawRectangle(BuyButton.x, BuyButton.y,BuyButton.width,BuyButton.height,BLUE);
        DrawText("BUY",BuyButton.x + 30,BuyButton.y + 20,20,WHITE);


        Color colorLevelSp1 = LIGHTGRAY;
        Color colorLevelSp2 = LIGHTGRAY;
        Color colorLevelDis1 = LIGHTGRAY;
        Color colorLevelDis2 = LIGHTGRAY;
        Color colorLevelDag1 = LIGHTGRAY;
        Color colorLevelDag2 = LIGHTGRAY;

        if(allTreeList[numberOfTreeList][0].buyList[0])
        {
            colorLevelSp1 = BLUE;
        }
        if(allTreeList[numberOfTreeList][0].buyList[1])
        {
            colorLevelSp2 = BLUE;
        }
        if(allTreeList[numberOfTreeList][1].buyList[0])
        {
            colorLevelDis1 = BLUE;
        }
        if(allTreeList[numberOfTreeList][1].buyList[1])
        {
            colorLevelDis2 = BLUE;
        }
        if(allTreeList[numberOfTreeList][2].buyList[0])
        {
            colorLevelDag1 = BLUE;
        }
        if(allTreeList[numberOfTreeList][2].buyList[1])
        {
            colorLevelDag2 = BLUE;
        }

        //First Imp Level 1 - 2
        DrawLineBezier({impBox.x + 175,impBox.y + 100},{impBox.x + 310,impBox.y + 100},5,colorLevelSp1);
        //First Imp Level 2 - 3
        DrawLineBezier({impBox.x + 360,impBox.y + 100},{impBox.x + 500,impBox.y + 100},5,colorLevelSp2);
        //Second Imp Level 1 - 2
        DrawLineBezier({impBox.x + 175,impBox.y + 200},{impBox.x + 310,impBox.y + 200},5,colorLevelDis1);
        //Second Imp Level 2 - 3
        DrawLineBezier({impBox.x + 360,impBox.y + 200},{impBox.x + 500,impBox.y + 200},5,colorLevelDis2);
        //Third Imp Level 1 - 2
        DrawLineBezier({impBox.x + 175,impBox.y + 300},{impBox.x + 310,impBox.y + 300},5,colorLevelDag1);
        //Third Imp Level 2 - 3
        DrawLineBezier({impBox.x + 360,impBox.y + 300},{impBox.x + 500,impBox.y + 300},5,colorLevelDag2);

        //Draw Tree Improvements of Speed
        DrawRectangle(firstLSBox.x,firstLSBox.y,firstLSBox.width,firstLSBox.height,allTreeList[numberOfTreeList][0].colorList[0]);
        DrawRectangle(secondLSBox.x,secondLSBox.y,secondLSBox.width,secondLSBox.height,allTreeList[numberOfTreeList][0].colorList[1]);
        DrawRectangle(thirdLSBox.x,thirdLSBox.y,thirdLSBox.width,thirdLSBox.height,allTreeList[numberOfTreeList][0].colorList[2]);
        //Draw Tree Improvements of Distance
        DrawRectangle(firstLDisBox.x,firstLDisBox.y,firstLDisBox.width,firstLDisBox.height,allTreeList[numberOfTreeList][1].colorList[0]);
        DrawRectangle(secondLDisBox.x,secondLDisBox.y,secondLDisBox.width,secondLDisBox.height,allTreeList[numberOfTreeList][1].colorList[1]);
        DrawRectangle(thirdLDisBox.x,thirdLDisBox.y,thirdLDisBox.width,thirdLDisBox.height,allTreeList[numberOfTreeList][1].colorList[2]);
        //Draw Tree Improvements of Damage
        DrawRectangle(firstLDagBox.x,firstLDagBox.y,firstLDagBox.width,firstLDagBox.height,allTreeList[numberOfTreeList][2].colorList[0]);
        DrawRectangle(secondLDagBox.x,secondLDagBox.y,secondLDagBox.width,secondLDagBox.height,allTreeList[numberOfTreeList][2].colorList[1]);
        DrawRectangle(thirdLDagBox.x,thirdLDagBox.y,thirdLDagBox.width,thirdLDagBox.height,allTreeList[numberOfTreeList][2].colorList[2]);
    }
    
}

void TorretTree::CreateTree()
{
    //Boxes Improvements
    firstLSBox = {impBox.x + 125,impBox.y + 75, 50,50};
    secondLSBox = {impBox.x + 310,impBox.y + 75, 50,50};
    thirdLSBox = {impBox.x + 500,impBox.y + 75, 50,50};
    firstLDisBox = {impBox.x + 125,impBox.y + 175, 50,50};
    secondLDisBox = {impBox.x + 310,impBox.y + 175, 50,50};
    thirdLDisBox = {impBox.x + 500,impBox.y + 175, 50,50};
    firstLDagBox = {impBox.x + 125,impBox.y + 275, 50,50};
    secondLDagBox = {impBox.x + 310,impBox.y + 275, 50,50};
    thirdLDagBox = {impBox.x + 500,impBox.y + 275, 50,50};


        Tree archerSpeed;
    archerSpeed.name = "speed";
    archerSpeed.impList = {-1,-1,-1};
    archerSpeed.priceList = {150,250,350};
    archerSpeed.buyList = {false,false,false};
    archerSpeed.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    archerSpeed.boxImpList = {firstLSBox,secondLSBox,thirdLSBox};
        Tree archerDistance;
    archerDistance.name = "distance";
    archerDistance.impList = {10,10,10};
    archerDistance.priceList = {150,250,350};
    archerDistance.buyList = {false,false,false};
    archerDistance.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    archerDistance.boxImpList = {firstLDisBox,secondLDisBox,thirdLDisBox};
        Tree archerDamage;
    archerDamage.name = "damage";
    archerDamage.impList = {10,10,10};
    archerDamage.priceList = {150,250,350};
    archerDamage.buyList = {false,false,false};
    archerDamage.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    archerDamage.boxImpList = {firstLDagBox,secondLDagBox,thirdLDagBox};
    
    archerList.push_back(archerSpeed);
    archerList.push_back(archerDistance);
    archerList.push_back(archerDamage);

    allTreeList.push_back(archerList);

        Tree cannonSpeed;
    cannonSpeed.name = "speed";
    cannonSpeed.impList = {-5,-5,-5};
    cannonSpeed.priceList = {250,350,450};
    cannonSpeed.buyList = {false,false,false};
    cannonSpeed.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    cannonSpeed.boxImpList = {firstLSBox,secondLSBox,thirdLSBox};
        Tree cannonDistance;
    cannonDistance.name = "distance";
    cannonDistance.impList = {10,10,10};
    cannonDistance.priceList = {250,350,450};
    cannonDistance.buyList = {false,false,false};
    cannonDistance.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    cannonDistance.boxImpList = {firstLDisBox,secondLDisBox,thirdLDisBox};
        Tree cannonDamage;
    cannonDamage.name = "damage";
    cannonDamage.impList = {10,10,10};
    cannonDamage.priceList = {250,350,450};
    cannonDamage.buyList = {false,false,false};
    cannonDamage.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    cannonDamage.boxImpList = {firstLDagBox,secondLDagBox,thirdLDagBox};
    
    cannonList.push_back(cannonSpeed);
    cannonList.push_back(cannonDistance);
    cannonList.push_back(cannonDamage);

    allTreeList.push_back(cannonList);

    Tree magicSpeed;
    magicSpeed.name = "speed";
    magicSpeed.impList = {-5,-5,-5};
    magicSpeed.priceList = {350,450,550};
    magicSpeed.buyList = {false,false,false};
    magicSpeed.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    magicSpeed.boxImpList = {firstLSBox,secondLSBox,thirdLSBox};
        Tree magicDistance;
    magicDistance.name = "distance";
    magicDistance.impList = {10,10,10};
    magicDistance.priceList = {350,450,550};
    magicDistance.buyList = {false,false,false};
    magicDistance.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    magicDistance.boxImpList = {firstLDisBox,secondLDisBox,thirdLDisBox};
        Tree magicDamage;
    magicDamage.name = "damage";
    magicDamage.impList = {10,10,10};
    magicDamage.priceList = {350,450,550};
    magicDamage.buyList = {false,false,false};
    magicDamage.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    magicDamage.boxImpList = {firstLDagBox,secondLDagBox,thirdLDagBox};
    
    magicList.push_back(cannonSpeed);
    magicList.push_back(cannonDistance);
    magicList.push_back(cannonDamage);

    allTreeList.push_back(magicList);

    Tree mortarSpeed;
    mortarSpeed.name = "speed";
    mortarSpeed.impList = {-5,-5,-5};
    mortarSpeed.priceList = {350,450,550};
    mortarSpeed.buyList = {false,false,false};
    mortarSpeed.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    mortarSpeed.boxImpList = {firstLSBox,secondLSBox,thirdLSBox};
        Tree mortarDistance;
    mortarDistance.name = "distance";
    mortarDistance.impList = {10,10,10};
    mortarDistance.priceList = {350,450,550};
    mortarDistance.buyList = {false,false,false};
    mortarDistance.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    mortarDistance.boxImpList = {firstLDisBox,secondLDisBox,thirdLDisBox};
        Tree mortarDamage;
    mortarDamage.name = "damage";
    mortarDamage.impList = {10,10,10};
    mortarDamage.priceList = {350,450,550};
    mortarDamage.buyList = {false,false,false};
    mortarDamage.colorList = {LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};
    mortarDamage.boxImpList = {firstLDagBox,secondLDagBox,thirdLDagBox};
    
    mortarList.push_back(cannonSpeed);
    mortarList.push_back(cannonDistance);
    mortarList.push_back(cannonDamage);

    allTreeList.push_back(mortarList);
}


