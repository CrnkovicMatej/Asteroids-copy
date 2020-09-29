#include "playstate.h"
#include "game.h"
#include <iostream>

PlayState::PlayState(Game * pGame) : GameState(pGame), mWindow(mpGame->getWindow()){
    //mWindow = (mpGame->mWindow);
    mBackgroundSprite.setTexture(mTextureHolder.getTexture(Textures::background));
    mDtFixed = sf::seconds(1.0f/120.0f);

    mFont.loadFromFile("neuropol_x_rg.ttf");

    mScore.setString("Score = " + std::to_string(score));
    mScore.setFont(mFont);
    mScore.setCharacterSize(30);
    mScore.setFillColor(sf::Color::White);
    mScore.setOutlineColor(sf::Color::White);
    mScore.setPosition(1000,30);

    srand(time(nullptr));

    mLives.setString("Number of lives = " + std::to_string(numberOfLives));
    mLives.setFont(mFont);
    mLives.setCharacterSize(30);
    mLives.setFillColor(sf::Color::White);
    mLives.setOutlineColor(sf::Color::White);
    mLives.setPosition(50,30);

    mPlayer.reset(new Player(mTextureHolder.getTexture(Textures::player)));
    mPlayer->setPosition(mWindow->getSize().x/2, mWindow->getSize().y/2);

    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorBig1), "big")));
    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorBig3), "big")));
    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorMedium1), "medium")));
    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorMedium2),"medium")));
    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorSmall1),"small")));
    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorSmall2), "small")));
    for(auto i= allVector.begin(); i < allVector.end(); i++){
        (*i)->setPosition(rand()%1280,rand()%1024);
    }

}

void PlayState::init(){
    allVector.clear();

    score=0;
    numberOfLives = 3;

    mScore.setString("Score = " + std::to_string(score));
    mScore.setFont(mFont);
    mScore.setCharacterSize(30);
    mScore.setFillColor(sf::Color::White);
    mScore.setOutlineColor(sf::Color::White);
    mScore.setPosition(1000,30);

    mLives.setString("Number of lives = " + std::to_string(numberOfLives));
    mLives.setFont(mFont);
    mLives.setCharacterSize(30);
    mLives.setFillColor(sf::Color::White);
    mLives.setOutlineColor(sf::Color::White);
    mLives.setPosition(50,30);

    mPlayer.reset(new Player(mTextureHolder.getTexture(Textures::player)));
    mPlayer->setPosition(mWindow->getSize().x/2, mWindow->getSize().y/2);

    mIsMovingUp    = false;
    mIsMovingDown  = false;
    mIsMovingLeft  = false;
    mIsMovingRight = false;

    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorBig1), "big")));
    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorBig3), "big")));
    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorMedium1), "medium")));
    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorMedium2),"medium")));
    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorSmall1),"small")));
    allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorSmall2), "small")));
    for(auto i= allVector.begin(); i < allVector.end(); i++){
        (*i)->setPosition(rand()%1280,rand()%1024);
    }
}

void PlayState::handleEvents(sf::Event event){
    //while (mpGame->mWindow.pollEvent(event))
    //{
            // Close window : exit
        switch(event.type){
            case sf::Event::Closed: 
                mpGame->end();
                break;
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::MouseButtonPressed:
                mMouseButtonPressed = true;
                break;
            case sf::Event::MouseButtonReleased:
                mMouseButtonPressed = false;
                break;
        }        
    //}
}

void PlayState::handlePlayerInput(sf::Keyboard::Key code, bool isPressed){
    if(code == sf::Keyboard::Key::Up)
        mIsMovingUp = isPressed;
    if(code == sf::Keyboard::Key::Down)
        mIsMovingDown = isPressed;
    if(code == sf::Keyboard::Key::Left)
        mIsMovingLeft = isPressed;
    if(code == sf::Keyboard::Key::Right)
        mIsMovingRight = isPressed;  
    //dodan uvjet za pritisak tipke space 
    //stvaramo novi Bullet, ubacujemo ga u vaktor mBullet i dajemo
    //mu poziciju i rotaciju mPlayer-a, odnosno svemirskog broda
    if(code == sf::Keyboard::Key::Space && isPressed==true ){
        allVector.push_back(std::unique_ptr<Bullet>(new Bullet(mTextureHolder.getTexture(Textures::bullet))));
        allVector[allVector.size()-1]->setRotation(mPlayer->getRotation());
        allVector[allVector.size()-1]->setPosition(mPlayer->getPosition());
    }    
}

void PlayState::render(){
    mpGame->mWindow.draw(mBackgroundSprite);
    mpGame->mWindow.draw(*mPlayer);
    for(auto i=allVector.begin(); i<allVector.end(); i++){
        mpGame->mWindow.draw(**i);
    }

    mpGame->mWindow.draw(mLives);
    mpGame->mWindow.draw(mScore);

}

void PlayState::update(sf::Time dt){
    if(mIsMovingUp)
        mPlayer->mGo();
    if(mIsMovingDown)
        mPlayer->mStop();
    if(mIsMovingLeft)
        mPlayer->mRotateLeft(dt);
    if(mIsMovingRight)
        mPlayer->mRotateRight(dt);
    mPlayer->update(dt);
    
    for(auto i= 0; i <allVector.size(); i++){
        if((allVector[i])->isAlive ==false){ 
            allVector.erase(allVector.begin()+i);
        }
        else if(typeid(*allVector[i])==typeid(Bullet) && (allVector[i])->isOutOfBounds(mWindow->getSize().x, mWindow->getSize().y)){
            allVector.erase(allVector.begin()+i);
        }
        else{
            (allVector[i])->update(dt);
        }
    }
    
    if(!allVector.empty()){
        for(auto i=0; i<allVector.size(); i++){
            if(typeid(*allVector[i]) == typeid(Asteroid) && allVector[i]->mColision(*mPlayer)){
                this->numberOfLives-=1; 
                allVector.push_back(std::unique_ptr<Animation>(new Animation(mTextureHolder.getTexture(Textures::explosion), 4, 4, 256, 256, 0.2f)));
                allVector[allVector.size()-1]->setPosition(allVector[i]->getPosition());
                allVector.erase(allVector.begin()+i);
                mLives.setString("Number of lives = " + std::to_string(numberOfLives));
                mPlayer->mRestart(mWindow->getSize().x/2, mWindow->getSize().y/2);
            }
            else if(typeid(*allVector[i]) == typeid(Asteroid)){
                for(auto j=0; j<allVector.size(); j++){
                    if(typeid(*allVector[j]) == typeid(Bullet) && allVector[i]->mColision(*allVector[j])){
                        allVector.push_back(std::unique_ptr<Animation>(new Animation(mTextureHolder.getTexture(Textures::explosion), 4, 4, 256, 256, 0.2f)));
                        allVector[allVector.size()-1]->setPosition(allVector[i]->getPosition());
                        score+=10;
                        mScore.setString("Score : " + std::to_string(score));
                        if((allVector[i]->sizeOfEntity())=="big"){
                            auto temp = allVector[i]->getPosition();
                            allVector.erase(allVector.begin()+i);
                            allVector.erase(allVector.begin()+j-1);
                            allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorSmall1),"small")));
                            allVector.push_back(std::unique_ptr<Asteroid>(new Asteroid(mTextureHolder.getTexture(Textures::meteorSmall2),"small"))); 
                            allVector[allVector.size()-2]->setPosition(temp);
                            allVector[allVector.size()-1]->setPosition(temp);
                            float temp1 = (float)(rand()%100);
                            float temp12 = (float)(rand()%100);
                            sf::Vector2f temp2(temp1, temp12);
                            sf::Vector2f temp3(-temp1, -temp12);
                            allVector[allVector.size()-2]->setVelocity(temp2);
                            allVector[allVector.size()-1]->setVelocity(temp3);
                        }
                        else{
                            allVector.erase(allVector.begin()+i);
                            allVector.erase(allVector.begin()+j-1); 
                        }
                    }
                }  
            }
        }
    }
    if(numberOfLives == 0 || allVector.empty()){
        mpGame->numberOfLives = numberOfLives;
        mpGame->score = score;
        mpGame->setState(Score);
    }
}


