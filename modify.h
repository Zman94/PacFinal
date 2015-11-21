//
//  modify.h
//  PacFinal
//
//  Created by Zach Gleason on 10/6/15.
//  Copyright (c) 2015 Zach Gleason. All rights reserved.
//

#ifndef __PacFinal__modify__
#define __PacFinal__modify__

#include "stdafx.h"
#include <String.h>
#include <fstream>

class modify{
public:
    modify();
    void modifyLevel();
    void gameModify();
    char loadedMap[20][20];
    bool win;
    float pacX;
    float pacY;
    float ghostX;
    float ghostY;
    float ggoalX;
    float ggoalY;
    int pastDirection; //1=N,2=E...
    int goalDirection;
    int score;
    sf::Time elapsedTime;
    bool pacDirection[4];
    bool pacOpen;
    int switchPac;

    
private:
    void movePac(char* direction);
    void PacAction();
    void GhostAction();
    void checkLevel();
    
    bool isIntersection();
    int findOpenSpace();
    void moveGhost();
    
    char direction[1];
    std::ifstream pacLevel;
    
    const int speed = 1;
    int levelNumber;
    bool moveRight, moveLeft, moveUp, moveDown;
//    bool atIntersection = false;
};

#endif /* defined(__PacFinal__modify__) */
