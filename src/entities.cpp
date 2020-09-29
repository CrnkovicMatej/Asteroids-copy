#include "entities.h"
#include <cmath>

// Dopuniti po potrebi.

Entity::Entity(sf::Texture const & texture){
    mSprite.setTexture(texture);
    auto lb = mSprite.getLocalBounds();
    mSprite.setOrigin(lb.width/2, lb.height/2);
    mVelocity.x=mVelocity.y = 30.0f; 
    isAlive = true;

    mRadius = 1.0*std::min(lb.width/2,lb.height/2);
    mCircle.setRadius(mRadius);
    mCircle.setFillColor(sf::Color(0, 255, 0, 0));
    mCircle.setOutlineThickness(1);
    mCircle.setOutlineColor(sf::Color::Yellow);
    mCircle.setOrigin(mRadius, mRadius);
}

sf::Vector2f Entity::getCentre(){
   sf::Vector2f temp (0.0f, 0.0f);
   temp.x += mRadius;
   temp.y += mRadius;
   return temp; 
}

bool Entity::isOutOfBounds(float a, float b){
   if(getPosition().x < 0 || getPosition().x>a ||getPosition().y < 0 || getPosition().y>b ){
      return true;
   }
   else return false;
}

bool Entity::mColision(Entity entity){
   float tempX = (this->getPosition().x + mRadius) - (entity.getPosition().x + entity.mRadius);
   float tempY = (this->getPosition().y + mRadius) - (entity.getPosition().y + entity.mRadius);
   float tempR = mRadius + entity.mRadius;
   if(sqrt((tempX)*(tempX) + (tempY)*(tempY)) <= std::abs(tempR)){
      return true;
   }
   else{
      return false;
   }
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const{
   states.transform *= getTransform();
   target.draw(mSprite, states);
   //target.draw(mCircle, states);
}

void Entity::update(sf::Time dt){
   auto pos = getPosition();
   float x = pos.x + mVelocity.x*dt.asSeconds();
   float y = pos.y + mVelocity.y*dt.asSeconds();
   setPosition(x,y);
}

std::string Entity::sizeOfEntity(){
   return mSize;
}

Animation::Animation(sf::Texture const & texture, int rows, int cols, int width, int height, float vel) :
  Entity(texture), mRows(rows), mCols(cols), mWidth(width/cols), mHeight(height/rows), mSpeed(vel),
  mCurrentCol(0.0f),  mCurrentRow(0) {
   auto lb = mSprite.getLocalBounds();
   mSprite.setOrigin(lb.width/float(2*cols), lb.height/float(2*rows));
   mSprite.setTextureRect(sf::IntRect(0, 0, mWidth, mHeight));
}

void Animation::update(sf::Time dt){
    if(!isAlive) return;
    mCurrentCol += mSpeed;
    if(static_cast<int>(mCurrentCol) == mCols){
        mCurrentCol = 0.0f;
        ++mCurrentRow;
    }
    if(mCurrentRow == mRows){
        mCurrentCol = 0.0f;
        mCurrentRow = 0;
        isAlive = false;
        return;
    }

    int i = mCurrentCol;
    int j = mCurrentRow; 
    mSprite.setTextureRect(sf::IntRect(i*mWidth, j*mHeight, mWidth, mHeight));
} 

Asteroid::Asteroid(sf::Texture const & texture , std::string mAsteroidSize) : Entity(texture), mSize(mAsteroidSize){
   int a = rand()%100;
   //slučajna brzina okretanja
   mRotationRate = rand()%300;
   //slučajna brzina kretanja
   mVelocity.x = mVelocity.y = (float)a;
   //jedan od načina zadavanja slučajnog smjera kretanja
   if(a%2==0) mVelocity.x = mVelocity.x*(-1);
   if(a%3==0) mVelocity.y = mVelocity.y*(-1);
}

//update asteroida
void Asteroid::update(sf::Time dt){
   auto pos = getPosition();
   //gledamo je li izašao izvan granica
   if(pos.x < 0) pos.x=1280+pos.x;
   if(pos.x > 1280) pos.x = pos.x-1280; 
   if(pos.y < 0) pos.y = 1024 + pos.y;
   if(pos.y > 1024) pos.y = pos.y -1024;
   float x = pos.x + mVelocity.x*dt.asSeconds();
   float y = pos.y + mVelocity.y*dt.asSeconds();
   setPosition(x,y);
   //rotiramo za fiksni, ali randomizirani mRotationRate
   rotate(mRotationRate*dt.asSeconds());
      
}

std::string Asteroid::sizeOfEntity(){
   return mSize;
}

void Asteroid::isHit(){
   isAlive=false;
}

Player::Player(sf::Texture const & texture) : Entity(texture){
}

void Player::update(sf::Time dt){
   if(mIsGoing || mVelocity > 0){
      mMove(dt);
   }
}

void Player::mRestart(float a, float b){
   setPosition(a,b);
   setRotation(0.0f);
   mStop(); 
   mVelocity = 0; 
   setVelocity(sf::Vector2f(0.0f,0.0f));
};

//rotiranje broda kontra od kazaljke na satu
void Player::mRotateLeft(sf::Time dt){
   rotate((-100)*dt.asSeconds());
}

//rotiranje broda u smjeru kazaljke na satu
void Player::mRotateRight(sf::Time dt){
   rotate((100)*dt.asSeconds());
}

void Player::mMove(sf::Time dt){
   //if uvjet koji osigurava da brod ubrzava postepeno 
   //prema maksimalnoj brzini
   if (mIsGoing && (mVelocity < mMaxSpeed)){
      mVelocity +=0.5f;
   }
   //if uvjet koji osigurava da brod ubrzava usporava 
   //prema stajanju
   else if(!mIsGoing && (mVelocity > 0)){
      mVelocity -=4.f;
      if(mVelocity < 0){
         mVelocity = 0;
      }
   }
   auto pos = getPosition();
   bool oneCase = false;
   //provjeravamo je li mPlayer izašao izvan granica prozora
   if(pos.x < 0){ pos.x=1280+pos.x;oneCase =true;}
   if(pos.x > 1280){ pos.x = pos.x-1280; oneCase =true;}
   if(pos.y < 0) {pos.y = 1024 + pos.y; oneCase =true;}
   if(pos.y > 1024) {pos.y = pos.y -1024; oneCase =true;}
   //ako je prebacujemo ga na "drugu stranu"
   if(oneCase ==true){
      float x = pos.x + mVelocity*dt.asSeconds();
      float y = pos.y + mVelocity*dt.asSeconds();
      setPosition(x,y);
   }
   sf::Vector2f mOrientation(0.f, 0.f);
   //kut rotacije prebacujemo u radijane jer njima rade sin i cos
   auto angleInRads = (M_PI/180)*getRotation();
   //koristimo modificirane polarne koordinate koje odgovaraju 
   //SFML-u
   mOrientation.x = (sin(angleInRads))*mVelocity;
   mOrientation.y = (-cos(angleInRads))*mVelocity;
   move(mOrientation*dt.asSeconds());
}

void Player::mStop(){
   mIsGoing = false;
}

void Player::mGo(){
   mIsGoing = true;
}

void Player::isHit(){
   mNumberOfLives-=1;
}
//konstruktor za Bullet
Bullet::Bullet(sf::Texture const & texture) : Entity(texture){
}

Life::Life(sf::Texture const & texture) : Entity(texture){
}

void Life::update(sf::Time dt){
   auto pos = getPosition();
   bool oneCase = false;
   if(pos.x < 0){ pos.x=1280+pos.x;oneCase =true;}
   if(pos.x > 1280){ pos.x = pos.x-1280; oneCase =true;}
   if(pos.y < 0) {pos.y = 1024 + pos.y; oneCase =true;}
   if(pos.y > 1024) {pos.y = pos.y -1024; oneCase =true;}
   if(oneCase ==true){
      float x = pos.x + mVelocityLife*dt.asSeconds();
      float y = pos.y + mVelocityLife*dt.asSeconds();
      setPosition(x,y);
   }
   sf::Vector2f mOrientation(0.f, 0.f);
   auto angle = dt.asMicroseconds()*M_PI/180;
   mOrientation.x = (cos(angle))*mVelocityLife;
   mOrientation.y = (sin(angle))*mVelocityLife;
   move(mOrientation*dt.asSeconds());

}

void Bullet::update(sf::Time dt){
   sf::Vector2f mOrientation(0.f, 0.f);
   //kut rotacije prebacujemo u radijane jer njima rade sin i cos
   auto angleInRads = (M_PI/180)*getRotation();
   //koristimo modificirane polarne koordinate koje odgovaraju 
   //SFML-u
   mOrientation.x = (sin(angleInRads))*mVelocityBullet;
   mOrientation.y = (-cos(angleInRads))*mVelocityBullet;
   move(mOrientation*dt.asSeconds());
}
