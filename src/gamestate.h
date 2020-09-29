#pragma once

#include "entities.h"
#include "textureHolder.h" 
#include <SFML/Graphics.hpp>
class Game;


class GameState
{
public:
    GameState(Game * pGame);
    virtual ~GameState() {}
    // Sva moguća stanja igre.
        enum State{
            Welcome,
            Playing,
            Score,
            SIZE
        };
    // Metode koje moraju osigurati sva stanja igre.
    virtual void init() = 0;
    virtual void handleEvents(sf::Event event) = 0;
    virtual void update(sf::Time dt = sf::Time::Zero) = 0;
    virtual void render() = 0;
    //virtual void start() = 0;

protected:
    Game * const mpGame; // Pokazivač na Game klasu
    // eventualno i druge varijable  
    //friend class PlayState;
       
};


class WelcomeState : public GameState{
//  Vaš kod ...
public:
    WelcomeState(Game * pGame);
    virtual void init() override;
    virtual void handleEvents(sf::Event event)  override;
    virtual void update(sf::Time dt = sf::Time::Zero)  override;
    virtual void render() override;
private:
    sf::Text mTextOne;
    sf::Text mTextTwo;
    sf::Font mFont;
};

class ScoreState : public GameState{
// Vaš kod ...
public:
    ScoreState(Game * pGame);
    virtual void init() override;
    virtual void handleEvents(sf::Event event)  override;
    virtual void update(sf::Time dt = sf::Time::Zero)  override;
    virtual void render() override;
private:
    sf::Font mFont;
    sf::Text mTextOne;
    sf::Text mTextTwo;

    int mScore=0;

    //što će mi već trebati
};


