//
//  Game.cpp
//  PacFinal
//
//  Created by Zach Gleason on 9/4/15.
//  Copyright (c) 2015 Zach Gleason. All rights reserved.
//

#include "Game.h"

Game::Game(){
    gameState = menu;
    levelNumber = 1;
}

void Game::Start(){
    
    mainWindow.create(sf::VideoMode(800,600), "Pac-Man");
    sf::Clock clock;
    
    modify* level = new modify::modify();
    draw* game1 = new draw::draw();
    while(mainWindow.isOpen()){
        level->elapsedTime = clock.getElapsedTime(); //used for pacs speed. So it doesn't vary with frames
        clock.restart();
        
        if(gameState == menu)
            ShowMenu();
        else if(gameState == playing)
            GameRun(level, game1);
        else if(gameState == gameOver)
            GameOver(level, game1);
        renderWindow();
    }
    delete level;
    delete game1;
}

void Game::ShowMenu(){
    sf::Event event;
    sf::Texture image;
    if (!image.loadFromFile(resourcePath()+"Pac_Start.png"))
        return;
    sf::Sprite sprite(image);
    sprite.setPosition(72.5, 0);
    mainWindow.draw(sprite);
    
    sf::RectangleShape line(sf::Vector2f(175, 5));
    line.setPosition(300, 425);
    line.setFillColor(sf::Color::White);
    
    if(mainWindow.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            mainWindow.close();
        mousePos = sf::Mouse::getPosition(mainWindow);
    }

    if (mousePos.x > 300 && mousePos.x < 475 && mousePos.y > 395 && mousePos.y < 425){
        mainWindow.draw(line);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            gameState = playing;
        }
    }
}

void Game::GameRun(modify* level, draw* game1){
    level->gameModify(); //moves pac then checks to see if level was completed
    game1->gameDraw(level, mainWindow);
    if(level->win)
        gameState = gameOver;
    sf::Event event;
    if(mainWindow.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            mainWindow.close();
    }
}

void Game::GameOver(modify* level, draw* game1){
    sf::Event event;
    if(mainWindow.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            mainWindow.close();
      /*  if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            levelNumber = 2;
            gameState = menu;
        }       */
    }
    game1->drawGameOver(level, mainWindow);

}

void Game::renderWindow(){
    mainWindow.display();
    mainWindow.clear();
}