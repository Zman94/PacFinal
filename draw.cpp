//
//  draw.cpp
//  PacFinal
//
//  Created by Zach Gleason on 9/28/15.
//  Copyright © 2015 Zach Gleason. All rights reserved.
//

#include "draw.h"

draw::draw(){
    if (!wall.loadFromFile("/Users/Zach/Projects/PacFinal/PacFinal/Pacman Wall Final.png"))
        return;
    if (!pebble.loadFromFile("/Users/Zach/Projects/PacFinal/PacFinal/Pebble.jpeg"))
        return;
    if (!pacClosed.loadFromFile("/Users/Zach/Projects/PacFinal/PacFinal/PacClosed.jpeg"))
        return;
    if (!pacOpen.loadFromFile("/Users/Zach/Projects/PacFinal/PacFinal/PacOpen.jpg"))
        return;
    if (!endFont.loadFromFile("/Users/Zach/Projects/PacFinal/PacFinal/Minecraft.ttf"))
        return;
    if(!blinky.loadFromFile("/Users/Zach/Projects/PacFinal/PacFinal/Blinky.jpg"))
        return;
    endText.setFont(endFont);
    endText.setPosition(300,263);
    endText.setColor(sf::Color::White);
    endText.setCharacterSize(35);

}

void draw::gameDraw(const modify *level, sf::RenderWindow &mainWindow){
    drawMap(mainWindow, level->loadedMap, false);
    drawGhost(mainWindow, level->ghostX, level->ghostY);
    drawPac(mainWindow, level->pacX, level->pacY, level->pacDirection, level->switchPac, level->pacOpen);
}

void draw::drawGameOver(const modify* level, sf::RenderWindow &mainWindow){
    drawMap(mainWindow, level->loadedMap, true);
    endText.setString("Game Over");
    mainWindow.draw(endText);
}

void draw::drawMap(sf::RenderWindow &mainWindow, const char (&loadedMap)[20][20], bool gameOver){
    for(int j = 0; j < 20; j++){
        for(int i = 0; i < 20; i++){
            if(loadedMap[i][j] == '1')
                wallType(i, j, loadedMap, mainWindow);
            else if(loadedMap[i][j] == '3' && !gameOver)
                drawPebble(mainWindow, i, j);
            else if(loadedMap[i][j] == '4' && !gameOver)
                drawPower(mainWindow, i, j);
        }
    }
}

void draw::drawPebble(sf::RenderWindow &mainWindow, int n, int m){
    sf::Sprite Pebble(pebble);
    Pebble.setPosition(100 + ((m) * 30), ((n) *30));
    mainWindow.draw(Pebble);
}

void draw::drawPower(sf::RenderWindow &mainWindow, int n, int m){

    sf::Sprite Pebble(pebble);
    Pebble.setPosition(100 + ((m) * 30), ((n) *30));
    mainWindow.draw(Pebble);
}

void draw::drawPac(sf::RenderWindow &mainWindow, const int pacX, const int pacY, const bool pacDirection[4], bool switchPac, bool isPacOpen){
    sf::Sprite PacMan;
    if(isPacOpen)
        PacMan.setTexture(pacOpen);
    else
        PacMan.setTexture(pacClosed);
    
    if(pacDirection[0]){
        PacMan.rotate(270);
        PacMan.setPosition(100+pacX, pacY+30);
    }
    else if(pacDirection[1]){
        PacMan.setPosition(100+pacX, pacY);
    }
    else if(pacDirection[2]){
        PacMan.rotate(270);
        PacMan.scale(-1,1);
        PacMan.setPosition(100+pacX, pacY);
    }
    else{
        PacMan.scale(-1,1);
        PacMan.setPosition(130+pacX, pacY);
    }
    mainWindow.draw(PacMan);
}

void draw::drawGhost(sf::RenderWindow &mainWindow, const int ghostX, const int ghostY){
    sf::Sprite Blinky;
    Blinky.setTexture(blinky);
    Blinky.setPosition(100+ghostX, ghostY);
    mainWindow.draw(Blinky);
}

//WALL/////////////////////////////////////////////////////////////////////////
void draw::wallType(int n, int m, char const (&map)[20][20], sf::RenderWindow &mainWindow)
{
    sf::Sprite gameWall(wall);
    gameWall.setPosition(100 + ((m) * 30),(n) * 30);
    mainWindow.draw(gameWall);
}
//WALL//////////////////////////////////////////////////////////////////////////////////////////////