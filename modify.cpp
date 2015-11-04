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
        }
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
    this->PacAction();
    this->checkLevel();
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
    
    this->movePac(direction, pacX, pacY);
}

void modify::movePac(char*direction, float& pac_x, float& pac_y){
    
    if((loadedMap[((int)pac_y-1)/30][((int)pac_x+4)/30]=='1' || loadedMap[((int)pac_y-1)/30][((int)pac_x+26)/30]=='1'))
        moveUp = false;
    else
        moveUp = true;
    
    if(loadedMap[((int)pac_y+31)/30][((int)pac_x+4)/30]=='1' || loadedMap[((int)pac_y+31)/30][((int)pac_x+26)/30]=='1')
        moveDown = false;
    else
        moveDown = true;
    
    if(loadedMap[((int)pac_y+4)/30][((int)pac_x-1)/30]=='1' || loadedMap[((int)pac_y+26)/30][((int)pac_x-1)/30]=='1')
        moveLeft = false;
    else
        moveLeft = true;
    
    if(loadedMap[((int)pac_y+4)/30][((int)pac_x+31)/30]=='1' || loadedMap[((int)pac_y+26)/30][((int)pac_x+31)/30]=='1')
        moveRight = false;
    else
        moveRight = true;
    
    float speedFrame = ((int)elapsedTime.asMicroseconds()/1000)/5.0;
    
    if(direction[0] == 'u' && moveUp){
        pac_y -=(speed*speedFrame);
        switchPac++;
    }
    else if(direction[0] == 'd' && moveDown){
        pac_y +=(speed*speedFrame);
        switchPac++;
    }
    else if(direction[0] == 'r' && moveRight){
        pac_x +=(speed*speedFrame);
        switchPac++;
    }
    else if(direction[0] == 'l' && moveLeft){
        pac_x -=(speed*speedFrame);
        switchPac++;
    }
    
    if(switchPac==75){
        pacOpen = !pacOpen;
        switchPac = 0;
    }

    if(loadedMap[((int)pac_y+10)/30][((int)pac_x+10)/30]=='3'){
        loadedMap[((int)pac_y+10)/30][((int)pac_x+10)/30]='0';
        score+=100;
    }
    if(loadedMap[((int)pac_y+20)/30][((int)pac_x+10)/30]=='3'){
        loadedMap[((int)pac_y+20)/30][((int)pac_x+10)/30]='0';
        score+=100;
    }
    if(loadedMap[((int)pac_y+20)/30][((int)pac_x+20)/30]=='3'){
        loadedMap[((int)pac_y+20)/30][((int)pac_x+20)/30]='0';
        score+=100;
    }
    if(loadedMap[((int)pac_y+10)/30][((int)pac_x+20)/30]=='3'){
        loadedMap[((int)pac_y+10)/30][((int)pac_x+20)/30]='0';
        score+=100;
    }
    
}

void modify::checkLevel(){
    this->win = true;
    for (int j=1; j<21; j++)
        for (int i=1; i<21; i++)
        {
            if(this->loadedMap[i][j]=='3')
                this->win = false;
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