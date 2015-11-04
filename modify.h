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
    int score;
    sf::Time elapsedTime;
    bool pacDirection[4];
    bool pacOpen;
    int switchPac;

    
private:
    void movePac(char* direction, float& pac_x, float& pac_y);
    void PacAction();
    void checkLevel();
    
    char direction[1];
    std::ifstream pacLevel;
    
    const int speed = 1;
    int levelNumber;
    bool moveRight, moveLeft, moveUp, moveDown;
};

#endif /* defined(__PacFinal__modify__) */
