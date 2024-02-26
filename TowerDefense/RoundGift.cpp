#include "RoundGift.h"
RoundGift::RoundGift() : map(), enemy(), torret(map,enemy)
{
    giftsDecided = false;
    gift1.giftName = "none";
    gift2.giftName = "none";
    gift3.giftName = "none";
    giftsList.push_back(gift1);
    giftsList.push_back(gift2);
    giftsList.push_back(gift3);
    GiftTypes();

    exitButton = {725,150,25,25};
    firstGiftBox = {75,200,200,300};
    secondGiftBox = {300,200,200,300};
    thirdGiftBox = {525,200,200,300};
    giftBoxList.push_back(firstGiftBox);
    giftBoxList.push_back(secondGiftBox);
    giftBoxList.push_back(thirdGiftBox);
}

void RoundGift::Draw()
{
    //Gift BOX Drawned
    DrawRectangle(50, 150,700,400,BLACK);
    DrawRectangleLines(50, 150,700,400,WHITE);
    int i = 0;
    for(auto& giftbox : giftBoxList)
    {
        DrawRectangle(giftbox.x,giftbox.y,giftbox.width,giftbox.height,WHITE);
        
        DrawText("Gift Times Left:",giftbox.x + 10 ,giftbox.y +  20, 15, BLACK);
        DrawText(TextFormat("%i",3 - giftsList[i].timesUsed),giftbox.x + 130 ,giftbox.y +  20, 15, BLACK);

        DrawText("The",giftbox.x + giftbox.width/2 - 20,giftbox.y + 50,20, BLACK);
        DrawText(giftsList[i].giftName.c_str(),giftbox.x + 20,giftbox.y + 100,20,MAROON);
        if(giftsList[i].positiveGift)
        {
        DrawText("will increase",giftbox.x + 20,giftbox.y + 150,20,BLACK);
        }
        else
        {
        DrawText("will decrease",giftbox.x + 25,giftbox.y + 150,20,BLACK);
        }
        i++;
    }

    //X exit Torret Tree
    DrawRectangle(exitButton.x,exitButton.y,exitButton.width,exitButton.height,RED);
    DrawRectangleLines(exitButton.x,exitButton.y,exitButton.width,exitButton.height,WHITE);
    DrawText("x",732,152,20,WHITE);
}

void RoundGift::Update(bool& selectingGift,int& PlayerHealth,int& wallPrice, std::vector<Torret::Torrets>& torretTypeList, std::vector<Enemy::Enemies>& enemyTypeList)
{
    if(!giftsDecided)
    {
        maxGiftLimit();
        RandomGift();
        giftsDecided = true;
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        int selectedCellX = mouseX;
        int selectedCellY = mouseY;
        //Choosing First Gift
        if(selectedCellX >= 75 && selectedCellX <= 275   
        && selectedCellY >= 200 && selectedCellY <= 500)
        {
            int giftNum = 0;
            RecieveGift(giftNum, PlayerHealth, wallPrice, torretTypeList,enemyTypeList);
            selectingGift = false;
        }
        //Choosing Second Gift
        else if(selectedCellX >= 300 && selectedCellX <= 500   
        && selectedCellY >= 200 && selectedCellY <= 500)
        {
            int giftNum = 1;
            RecieveGift(giftNum, PlayerHealth, wallPrice, torretTypeList,enemyTypeList);
            selectingGift = false;
        }
        //Choosing Third Gift
        else if(selectedCellX >= 525 && selectedCellX <= 725   
        && selectedCellY >= 200 && selectedCellY <= 500)
        {
            int giftNum = 2;
            RecieveGift(giftNum, PlayerHealth, wallPrice, torretTypeList,enemyTypeList);
            selectingGift = false;
        }
    }
}
void RoundGift::RecieveGift(int choiceNum,int& PlayerHealth,int& wallPrice, std::vector<Torret::Torrets>& torretTypeList, std::vector<Enemy::Enemies>& enemyTypeList)
{
    if(giftsList[choiceNum].giftName == "Wall Price")
    {
        wallPrice += giftsList[choiceNum].gift;
    }
    else if(giftsList[choiceNum].giftName == "Player Health")
    {
        PlayerHealth += giftsList[choiceNum].gift;
    }
    else if(giftsList[choiceNum].giftName == "Torret Damage")
    {
        for(auto& torret : torretTypeList)
        {
            torret.damage +=giftsList[choiceNum].gift;
        }
    }
    else if(giftsList[choiceNum].giftName == "Torret Speed")
    {
        for(auto& torret : torretTypeList)
        {
            torret.speed +=giftsList[choiceNum].gift;
        }
    }
    else if(giftsList[choiceNum].giftName == "Torret Distance")
    {
        for(auto& torret : torretTypeList)
        {
            torret.distance +=giftsList[choiceNum].gift;
        }
    }
    else if(giftsList[choiceNum].giftName == "Torret Price")
    {
        for(auto& torret : torretTypeList)
        {
            torret.price +=giftsList[choiceNum].gift;
        }
    }
    else if(giftsList[choiceNum].giftName == "Kill Coins")
    {
        for(auto& enemyType : enemyTypeList)
        {
            enemyType.deathPrice += giftsList[choiceNum].gift;
        }
    }
    else if(giftsList[choiceNum].giftName == "Enemy Health")
    {
        for(auto& enemyType : enemyTypeList)
        {
            enemyType.health += giftsList[choiceNum].gift;
        }
    }
    else if(giftsList[choiceNum].giftName == "Enemy Speed")
    {
        for(auto& enemyType : enemyTypeList)
        {
            enemyType.speed += giftsList[choiceNum].gift;
        }
    }
    for(auto& gift: giftTypeList)
    {
        if(giftsList[choiceNum].giftName == gift.giftName) gift.timesUsed++;
    }
    giftsDecided = false;
}

void RoundGift::GiftTypes()
{
    Gift giftWall;
    Gift giftPlayerHealth;
    Gift giftTorretDamage;
    Gift giftTorretSpeed;
    Gift giftTorretDistance;
    Gift giftEnemyDeathPrice;
    Gift giftTorretPrice;
    Gift giftEnemyHealth;
    Gift giftEnemySpeed;
    giftTypeList.clear();

    giftWall.giftName = "Wall Price";
    giftWall.gift = -1;
    giftWall.timesUsed = 0;
    giftWall.positiveGift = false;
    giftTypeList.push_back(giftWall);
    
    giftPlayerHealth.giftName = "Player Health";
    giftPlayerHealth.gift = 1;
    giftPlayerHealth.timesUsed = 0;
    giftPlayerHealth.positiveGift = true;
    giftTypeList.push_back(giftPlayerHealth);
    
    giftTorretDamage.giftName = "Torret Damage";
    giftTorretDamage.gift = 10;
    giftTorretDamage.timesUsed = 0;
    giftTorretDamage.positiveGift = true;
    giftTypeList.push_back(giftTorretDamage);
    
    giftTorretSpeed.giftName = "Torret Speed";
    giftTorretSpeed.gift = -1;
    giftTorretSpeed.timesUsed = 0;
    giftTorretSpeed.positiveGift = true;
    giftTypeList.push_back(giftTorretSpeed);
    
    giftTorretDistance.giftName = "Torret Distance";
    giftTorretDistance.gift = 10;
    giftTorretDistance.timesUsed = 0;
    giftTorretDistance.positiveGift = true;
    giftTypeList.push_back(giftTorretDistance);
    
    giftEnemyDeathPrice.giftName = "Kill Coins";
    giftEnemyDeathPrice.gift = 5;
    giftEnemyDeathPrice.timesUsed = 0;
    giftEnemyDeathPrice.positiveGift = true;
    giftTypeList.push_back(giftEnemyDeathPrice);
    
    giftTorretPrice.giftName = "Torret Price";
    giftTorretPrice.gift = -10;
    giftTorretPrice.timesUsed = 0;
    giftTorretPrice.positiveGift = false;
    giftTypeList.push_back(giftTorretPrice);
    
    giftEnemyHealth.giftName = "Enemy Health";
    giftEnemyHealth.gift = -50;
    giftEnemyHealth.timesUsed = 0;
    giftEnemyHealth.positiveGift = false;
    giftTypeList.push_back(giftEnemyHealth);
    
    giftEnemySpeed.giftName = "Enemy Speed";
    giftEnemySpeed.gift = -0.2;
    giftEnemySpeed.timesUsed = 0;
    giftEnemySpeed.positiveGift = false;
    giftTypeList.push_back(giftEnemySpeed);
}

void RoundGift::maxGiftLimit()
{
    for(int i = 0; i < giftTypeList.size();i++)
    {
        if(giftTypeList[i].timesUsed >=3)
        {
            giftTypeList.erase(giftTypeList.begin() + i);
        }
    }
}

void RoundGift::ExitGift(bool& selectingGift)
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        if(mouseX >= 725 && mouseY >= 150 
        && mouseX <=750 && mouseY <= 175)
        {
            selectingGift = false;
        }
    }
}

void RoundGift::RandomGift()
{
    std::vector<Gift> giftTypes = giftTypeList;
    for(auto& gift : giftsList)
    {
        int randNum = rand() % giftTypes.size();
        gift.giftName = giftTypes[randNum].giftName;
        gift.gift = giftTypes[randNum].gift;
        gift.timesUsed = giftTypes[randNum].timesUsed;
        giftTypes.erase(giftTypes.begin() + randNum);
    } 
}

