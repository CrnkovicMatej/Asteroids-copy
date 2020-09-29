#pragma once

#include "gamestate.h"

class PlayState : public GameState {
public:
    PlayState(Game * pGame);
    void init() override;
    void handleEvents(sf::Event event)  override;
    void update(sf::Time dt = sf::Time::Zero)  override;
    void render() override;
    void handlePlayerInput(sf::Keyboard::Key code, bool isPressed);
    //void start() override;
private:
    sf::RenderWindow* mWindow;
    TextureHolder mTextureHolder;  
    sf::Sprite mSprite;
    sf::Sprite mBackgroundSprite;
    std::unique_ptr<Player> mPlayer;

    sf::Text mScore;
    sf::Text mLives;
    sf::Font mFont;

    std::vector<std::unique_ptr<Entity>> allVector;

    bool mIsMovingUp    = false;
    bool mIsMovingDown  = false;
    bool mIsMovingLeft  = false;
    bool mIsMovingRight = false;

    bool mMouseButtonPressed = false;

    int score=0;
    int numberOfLives = 3;

    sf::Time mDtFixed;


//ako će trebati
};
