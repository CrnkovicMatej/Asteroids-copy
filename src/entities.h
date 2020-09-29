#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable {
public:
    Entity(sf::Texture const & texture);
    void setVelocity(sf::Vector2f const &  vel) { mVelocity = vel;}
    bool mColision(Entity entity);
    sf::Vector2f getCentre(); 
    virtual void update(sf::Time dt = sf::Time::Zero); 
    virtual std::string sizeOfEntity();
    bool isAlive;
    bool isOutOfBounds(float a, float b);
    virtual ~Entity() {}
protected:
    std ::string mSize = "regular";
    sf::Sprite mSprite;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Vector2f mVelocity;
    sf::CircleShape mCircle;
    float mRadius;
};

class Animation : public Entity{
public:
    Animation(sf::Texture const & texture, int rows, int cols, int width, int height, float vel);
    virtual void update(sf::Time dt = sf::Time::Zero)  override; 
private:
    std ::string mSize;
    int mRows, mCols, mWidth, mHeight;
    float mSpeed;
    float mCurrentCol;
    int   mCurrentRow;
};

// dopuniti
class Asteroid : public Entity{
public:
    Asteroid(sf::Texture const & texture, std::string mAsteroidSize);
    virtual void update(sf::Time dt = sf::Time::Zero) override;
    virtual std::string sizeOfEntity() override;
    void isHit(); 
private:
    std::string mSize;
    int mRotationRate;
    bool isBig;
};


// dopuniti
class Player : public Entity{
public:
    Player(sf::Texture const & texture);
    virtual void update(sf::Time dt = sf::Time::Zero) override;
    //funkcije koje nam koriste za update mPlayer-a
    void mRotateLeft(sf::Time dt);
    void mRotateRight(sf::Time dt);
    //funkcija mGoStraight() zamijenjena funkcijom mMove()
    //koja pomiče mPlayer (ubrzava i usporava)
    void mMove(sf::Time dt);
    void mStop();  
    void mGo();
    void isHit();
    void mRestart(float a, float b);
private:
    std ::string mSize;
    float mVelocity = 0.0f; // pixel/sec
    bool mIsGoing = false;
    float mMaxSpeed = 200.0f;
    int mNumberOfLives = 3;
};

//klasa Bullet
class Bullet : public Entity{
public:
    Bullet(sf::Texture const & texture);  
    virtual void update(sf::Time dt = sf::Time::Zero) override;
private:
    std ::string mSize;
    float mVelocityBullet = 700.0f; 
};

class Life : public Entity{
public:
    Life(sf::Texture const & texture);
    virtual void update(sf::Time dt = sf::Time::Zero) override;
private:
    float mVelocityLife = 50.0f;
};
