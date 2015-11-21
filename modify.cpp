//
//  modify.cpp
//  PacFinal
//
//  Created by Zach Gleason on 10/6/15.
//  Copyright (c) 2015 Zach Gleason. All rights reserved.
//

#include "modify.h"

modify::modify(){
    pacLevel.open("/Users/Zach/Projects/PacFinal/PacFinal/myLevel1.txt");
    if(pacLevel.fail())
        return;
    for (int j=0; j<20; j++)
        for (int i=0; i<20; i++)
        {
            pacLevel >> loadedMap[j][i];
            if(loadedMap[j][i]=='2'){
                pacX = 30*i;
                pacY = 30*j;
            }
            
            if(loadedMap[j][i]=='X'){
                ghostX = 30*i;
                ghostY = 30*j;
            }
        }
    pastDirection = 1;
    levelNumber = 0;
    score = 0;
    switchPac = 0;
    win = false;
    pacDirection[0] = false; //up
    pacDirection[1] = true; //right
    pacDirection[2] = false; //down
    pacDirection[3] = false; //left
    pacOpen = false;
    pacLevel.close();
}

void modify::gameModify(){
    PacAction();
    GhostAction();
    checkLevel();
}

void modify::PacAction(){
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        direction[0] = 'u';
        pacDirection[0] = true;
        pacDirection[1]=pacDirection[2]=pacDirection[3]=false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        direction[0] = 'd';
        pacDirection[2] = true;
        pacDirection[1]=pacDirection[0]=pacDirection[3]=false;
    }
    
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        direction[0] = 'r';
        pacDirection[1] = true;
        pacDirection[0]=pacDirection[2]=pacDirection[3]=false;
    }
    
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        direction[0] = 'l';
        pacDirection[3] = true;
        pacDirection[1]=pacDirection[2]=pacDirection[0]=false;
    }
    else
        direction[0] = 'n';
    
    movePac(direction);
}

void modify::GhostAction(){
    bool intersection = isIntersection();
    if(!intersection){
        pastDirection = findOpenSpace();
//        if(intersection)
//            atIntersection = false;
    }
    else{
        ggoalX = pacX+15;
        ggoalY = pacY+15;
        
        if(ggoalX-ghostX >= 0 && ggoalY-ghostY <= 0){ //top right
            //deterimne to go up
            if(ggoalX-ghostX < -(ggoalY-ghostY) && loadedMap[(int)(ghostY-1)/30][(int)(ghostX+4)/30]!='1' && loadedMap[(int)(ghostY-1)/30][(int)(ghostX+26)/30]!='1' && pastDirection!=3){
                pastDirection = 1;
            }
            else if(ggoalX-ghostX > -(ggoalY-ghostY) && loadedMap[(int)(ghostY+1)/30][(int)(ghostX+31)/30]!='1' && loadedMap[(int)(ghostY+29)/30][(int)(ghostX+31)/30]!='1' && pastDirection!=4){
                pastDirection = 2;
            }
            else
                pastDirection = findOpenSpace();
        }
        
        else if(ggoalX-ghostX >= 0 && ggoalY-ghostY > 0){ //bottom right
            if(ggoalX-ghostX < ggoalY-ghostY && loadedMap[(int)(ghostY+31)/30][(int)(ghostX)/30]!='1' && loadedMap[(int)(ghostY+31)/30][(int)(ghostX+29)/30]!='1' && pastDirection!='1'){
                pastDirection = 3;
            }
            else if(ggoalX-ghostX > ggoalY-ghostY && loadedMap[(int)(ghostY)/30][(int)(ghostX+31)/30]!='1' && loadedMap[(int)(ghostY+29)/30][(int)(ghostX+31)/30]!='1' && pastDirection!=4){
                pastDirection = 2;
            }
            else
                pastDirection = findOpenSpace();
        }
        
        else if(ggoalX-ghostX < 0 && ggoalY-ghostY <= 0){ //top left
            if(-(ggoalX-ghostX) < -(ggoalY-ghostY) && loadedMap[(int)(ghostY-1)/30][(int)(ghostX)/30]!='1' && loadedMap[(int)(ghostY-1)/30][(int)(ghostX+29)/30]!='1' && pastDirection!=3){
                pastDirection = 1;
            }
            else if(-(ggoalX-ghostX) > -(ggoalY-ghostY) && loadedMap[(int)(ghostY)/30][(int)(ghostX-1)/30]!='1' && loadedMap[(int)(ghostY+29)/30][(int)(ghostX-1)/30]!='1' && pastDirection!=2){
                pastDirection = 4;
            }
            else
                pastDirection = findOpenSpace();
        }
        
        else{ //bottom left
            if(-(ggoalX-ghostX) < ggoalY-ghostY && loadedMap[(int)(ghostY+31)/30][(int)(ghostX)/30]!='1' && loadedMap[(int)(ghostY+31)/30][(int)(ghostX+29)/30]!='1' && pastDirection!=1){
                pastDirection = 3;
            }
            else if(-(ggoalX-ghostX) > ggoalY-ghostY && loadedMap[(int)(ghostY)/30][(int)(ghostX-1)/30]!='1' && loadedMap[(int)(ghostY+29)/30][(int)(ghostX-1)/30]!='1' && pastDirection!=2){
                pastDirection = 4;
            }
            else
                pastDirection = findOpenSpace();
            
        }
    //    atIntersection = true;
    }
    moveGhost();
}

bool modify::isIntersection(){
    int i = 0;
    if(loadedMap[(int)(ghostY+31)/30][(int)(ghostX)/30]=='1' || loadedMap[(int)(ghostY+31)/30][(int)(ghostX+29)/30]=='1')
        i++;
    if(loadedMap[(int)(ghostY-1)/30][(int)(ghostX)/30]=='1' || loadedMap[(int)(ghostY-1)/30][(int)(ghostX+29)/30]=='1')
        i++;
    if(loadedMap[(int)(ghostY)/30][(int)(ghostX-1)/30]=='1' || loadedMap[(int)(ghostY+29)/30][(int)(ghostX-1)/30-1]=='1')
        i++;
    if(loadedMap[(int)(ghostY)/30][(int)(ghostX+31)/30]=='1' || loadedMap[(int)(ghostY+29)/30][(int)(ghostX+31)/30]=='1')
        i++;
    return i < 2;
}

int modify::findOpenSpace(){
    if(loadedMap[(int)(ghostY-1)/30][(int)(ghostX)/30]!='1' && loadedMap[(int)(ghostY-1)/30][(int)(ghostX+29)/30]!='1' && pastDirection!=3)
        return 1;
    else if(loadedMap[(int)(ghostY+31)/30][(int)(ghostX)/30]!='1' && loadedMap[(int)(ghostY+31)/30+1][(int)(ghostX+29)/30]!='1' && pastDirection!=1)
        return 3;
    else if(loadedMap[(int)(ghostY)/30][(int)(ghostX-1)/30]!='1' && loadedMap[(int)(ghostY+29)/30][(int)(ghostX-1)/30-1]!='1' && pastDirection!=2)
        return 4;
    else
        return 2;
}
           
void modify::movePac(char* direction){
    
    if((loadedMap[((int)pacY-1)/30][((int)pacX+4)/30]=='1' || loadedMap[((int)pacY-1)/30][((int)pacX+26)/30]=='1'))
        moveUp = false;
    else
        moveUp = true;
    
    if(loadedMap[((int)pacY+31)/30][((int)pacX+4)/30]=='1' || loadedMap[((int)pacY+31)/30][((int)pacX+26)/30]=='1')
        moveDown = false;
    else
        moveDown = true;
    
    if(loadedMap[((int)pacY+4)/30][((int)pacX-1)/30]=='1' || loadedMap[((int)pacY+26)/30][((int)pacX-1)/30]=='1')
        moveLeft = false;
    else
        moveLeft = true;
    
    if(loadedMap[((int)pacY+4)/30][((int)pacX+31)/30]=='1' || loadedMap[((int)pacY+26)/30][((int)pacX+31)/30]=='1')
        moveRight = false;
    else
        moveRight = true;
    
    float speedFrame = ((int)elapsedTime.asMicroseconds()/1000)/5.0;
    
    if(direction[0] == 'u' && moveUp){
        pacY -=(speed*speedFrame);
        switchPac++;
    }
    else if(direction[0] == 'd' && moveDown){
        pacY +=(speed*speedFrame);
        switchPac++;
    }
    else if(direction[0] == 'r' && moveRight){
        pacX +=(speed*speedFrame);
        switchPac++;
    }
    else if(direction[0] == 'l' && moveLeft){
        pacX -=(speed*speedFrame);
        switchPac++;
    }
    
    if(switchPac==75){
        pacOpen = !pacOpen;
        switchPac = 0;
    }

    if(loadedMap[((int)pacY+10)/30][((int)pacX+10)/30]=='3'){
        loadedMap[((int)pacY+10)/30][((int)pacX+10)/30]='0';
        score+=100;
    }
    if(loadedMap[((int)pacY+20)/30][((int)pacX+10)/30]=='3'){
        loadedMap[((int)pacY+20)/30][((int)pacX+10)/30]='0';
        score+=100;
    }
    if(loadedMap[((int)pacY+20)/30][((int)pacX+20)/30]=='3'){
        loadedMap[((int)pacY+20)/30][((int)pacX+20)/30]='0';
        score+=100;
    }
    if(loadedMap[((int)pacY+10)/30][((int)pacX+20)/30]=='3'){
        loadedMap[((int)pacY+10)/30][((int)pacX+20)/30]='0';
        score+=100;
    }
    
}

void modify::moveGhost(){
    float speedFrame = ((int)elapsedTime.asMicroseconds()/1000)/5.0/1.2;
    if(pastDirection == 1)
        ghostY-=(speed*speedFrame);
    else if(pastDirection == 2)
        ghostX+=(speed*speedFrame);
    else if(pastDirection == 3)
        ghostY+=(speed*speedFrame);
    else
        ghostX-=(speed*speedFrame);
}

void modify::checkLevel(){
    win = true;
//    if((int)ghostX/30 == (int)pacX/30 && (int)ghostY/30 == (int)pacY/30)
//        win = false;
//    else
        for (int j=1; j<21; j++)
            for (int i=1; i<21; i++)
            {
                if(this->loadedMap[i][j]=='3')
                    win = false;
            }
}

void modify::modifyLevel(){
    if(this->levelNumber==2){
        pacLevel.open("Resources/level2.rtf");
    }
    for (int j=1; j<21; j++)
        for (int i=1; j<21; i++)
        {
            pacLevel >> this->loadedMap[i][j];
            if(this->loadedMap[i][j]==2){
                this->pacX = 30*i;
                this->pacY = 30*j;
            }
        }
    this->win = false;
    this->levelNumber++;
}