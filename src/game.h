#pragma once
#include <SFML/Graphics.hpp>
#include "textureHolder.h"
#include "entities.h"
#include <vector>
#include <list>
#include <array>
#include "playstate.h"



// Klasu dopuniti po potrebi.

class Game{

    friend class WelcomeState;
    friend class ScoreState;
    friend class PlayState;
    friend class GameState;

public:
    Game();
    ~Game();
    void run();
    void end();
    void setState(GameState::State newState);
    sf::RenderWindow* getWindow();  
private:
    void processEvents();
    void update(sf::Time dt);
    void render();

    sf::RenderWindow mWindow;
    TextureHolder mTextureHolder;  
    sf::Sprite mSprite;
    sf::Sprite mBackgroundSprite;
    std::unique_ptr<Player> mPlayer;

    int score=0;
    int numberOfLives = 3;


    sf::Time mDtFixed;
    
    GameState::State mState = GameState::State::Welcome;
    std::array<GameState *, 3> mAllStates;
};
