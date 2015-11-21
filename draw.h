//
//  draw.h
//  PacFinal
//
//  Created by Zach Gleason on 9/28/15.
//  Copyright © 2015 Zach Gleason. All rights reserved.
//

#ifndef draw_h
#define draw_h

#include "stdafx.h"
#include "modify.h"

class draw{
public:
    draw();
    void gameDraw(const modify* level, sf::RenderWindow &mainWindow);
    void drawGameOver(const modify* level, sf::RenderWindow &mainWindow);
    
private:
    void drawMap(sf::RenderWindow &mainWindow, const char (&loadedMap)[20][20], bool gameOver);
    void drawPac(sf::RenderWindow &mainWindow, const int pacX, const int pacY, const bool pacDirection[4], bool switchPac, bool isPacOpen);
    void drawGhost(sf::RenderWindow &mainWindow, const int ghostX, const int ghostY);
    void wallType(int n, int m, char const (&map)[20][20], sf::RenderWindow &mainWindow);
    void drawPebble(sf::RenderWindow &mainWindow, int n, int m);
    void drawPower(sf::RenderWindow &mainWindow, int n, int m);
    sf::Texture wall;
    sf::Texture pebble;
    sf::Texture pacClosed;
    sf::Texture pacOpen;
    sf::Texture blinky;
    sf::Font endFont;
    sf::Text endText;
    
//    sf::Sprite PacMan;
//    sf::Sprite Blinky;
};
#endif /* draw_h */