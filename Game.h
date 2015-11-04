//
//  Game.h
//  PacFinal
//
//  Created by Zach Gleason on 9/4/15.
//  Copyright (c) 2015 Zach Gleason. All rights reserved.
//

#ifndef PacFinal_Game_h
#define PacFinal_Game_h

#include "stdafx.h"
#include "modify.h"
#include "draw.h"

class Game{
public:
    Game();
    
    void Start();

private:
    
    void ShowMenu();
    void GameRun(modify* level, draw* game1);
    void GameOver(modify* level, draw* game1);
    void renderWindow();
    
    int levelNumber;
    
    enum GameState{menu, playing, gameOver};
    
    sf::Vector2i mousePos;
    sf::RenderWindow mainWindow;
    
    GameState gameState;
};

#endif
