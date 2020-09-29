#include "game.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <memory>

Game::Game() : mWindow(sf::VideoMode(1280, 1024), "SFML window") {
    mDtFixed = sf::seconds(1.0f/120.0f);

    mAllStates[GameState::Score] = new ScoreState(this);
    mAllStates[GameState::Playing] = new PlayState(this);
    mAllStates[GameState::Welcome] = new WelcomeState(this); 
}

void Game::run(){
    // Start the game loop
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {   
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate >= mDtFixed){
            timeSinceLastUpdate -= mDtFixed;
            processEvents();
            update(mDtFixed);
        }       
        render();
    }

}

void Game::processEvents(){
        // Process events
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
           mAllStates[mState]->handleEvents(event); 
        }
}

void Game::update(sf::Time dt){
    mAllStates[mState]->update(dt);   
}

void Game::render(){
       // Clear screen
        mWindow.clear();
        
        mAllStates[mState]->render();

        mWindow.display();
}

void Game::end(){
    mWindow.close();
}

Game::~Game(){
    delete  mAllStates[GameState::Playing];
    delete  mAllStates[GameState::Score];
    delete  mAllStates[GameState::Welcome];
}

void Game::setState(GameState::State newState){
    mState = newState;
    //vraćamo na inicijalizacijske postavke kada vratimo na Playing
    //i nemamo više života ili smo povećali score

    if(mState == GameState::Playing && (numberOfLives == 0 || score>0)){
        mAllStates[mState]->init();
    }
    mAllStates[mState]->update(mDtFixed);
}

sf::RenderWindow* Game::getWindow(){
    return &mWindow;
}
