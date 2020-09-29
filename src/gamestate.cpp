#include "gamestate.h"
#include "game.h"
#include <iostream> // za debugiranje

GameState::GameState(Game * pGame) : mpGame(pGame){
}


WelcomeState::WelcomeState(Game * pGame) : GameState(pGame){
    mFont.loadFromFile("neuropol_x_rg.ttf");
    
    mTextOne.setFont(mFont);
    mTextOne.setString("Asteroids clone by Matej Crnkovic");
    mTextOne.setPosition(600, 300);
    mTextOne.setOrigin(mTextOne.getLocalBounds().width/2, mTextOne.getLocalBounds().height/2);
    mTextOne.setCharacterSize(30);

    mTextTwo.setFont(mFont);
    mTextTwo.setString("Press any key to continue");
    mTextTwo.setPosition(600, 400);
    mTextTwo.setOrigin(mTextTwo.getLocalBounds().width/2, mTextTwo.getLocalBounds().height/2);
    mTextTwo.setCharacterSize(30);


};

void WelcomeState::render(){
    mpGame->mWindow.draw(mTextOne);
    mpGame->mWindow.draw(mTextTwo);
};

void WelcomeState::handleEvents(sf::Event event){
    if(event.type == sf::Event::KeyPressed){
        mpGame->setState(State::Playing);
    }
};

void WelcomeState::update(sf::Time dt){

};

void WelcomeState::init(){

};



ScoreState::ScoreState(Game * pGame) : GameState(pGame){
    mFont.loadFromFile("neuropol_x_rg.ttf");
    
    mTextOne.setFont(mFont);
    mTextOne.setString("Score = 0");
    mTextOne.setPosition(600, 300);
    mTextOne.setOrigin(mTextOne.getLocalBounds().width/2, mTextOne.getLocalBounds().height/2);
    mTextOne.setCharacterSize(30);

    mTextTwo.setFont(mFont);
    mTextTwo.setString("ENTER to continue, Esc to finish");
    mTextTwo.setPosition(600, 400);
    mTextTwo.setOrigin(mTextTwo.getLocalBounds().width/2, mTextTwo.getLocalBounds().height/2);
    mTextTwo.setCharacterSize(30);
};

void ScoreState::update(sf::Time dt){
    mScore = mpGame->score;
    mTextOne.setString("Score =" + std::to_string(mScore));
};

void ScoreState::render(){
    mpGame->mWindow.draw(mTextOne);
    mpGame->mWindow.draw(mTextTwo);
};

void ScoreState::handleEvents(sf::Event event){
    if(event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Escape){
            mpGame->end();
        }
        else if(event.key.code == sf::Keyboard::Return){
            mpGame->setState(Playing);
        }
    }
};

void ScoreState::init(){
};

