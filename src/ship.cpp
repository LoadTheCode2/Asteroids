#include <SDL2/SDL.h>

#include "GameWindow.hpp"
#include "Bullet.hpp"
#include "Ship.hpp"

namespace ship_properties
{
  const float TURN_SPEED = 0.005f;
  const float TURN_STRENGTH = 0.00025f;
  const float TURN_DRAG = 0.05f;

  const float BOOST_SPEED = 0.2f;
  const float BOOST_STRENGTH = 0.005f;
  const float BOOST_DRAG = 0.0025f;

  const int WIDTH = 22;
  const int HEIGHT = 50;
  const char *FILE_PATH = "res/gfx/ship.png";
}

Ship::Ship(GameWindow &pWindow) : RenderUnit(pWindow, ship_properties::FILE_PATH, (game_settings::WIDTH - ship_properties::WIDTH) / 2, (game_settings::HEIGHT - ship_properties::HEIGHT) / 2, ship_properties::WIDTH, ship_properties::HEIGHT), _degree(-M_PI / 2), _forwardVel(0.0f), _rotateVel(0.0f), _forwardAcc(0.0f), _rotateAcc(0.0f) {}

void Ship::turnLeft()
{
  this->applyRotateForce(-ship_properties::TURN_STRENGTH);
}

void Ship::turnRight()
{
  this->applyRotateForce(ship_properties::TURN_STRENGTH);
}

void Ship::boost()
{
  this->applyForwardForce(ship_properties::BOOST_STRENGTH);
}

void Ship::brake()
{
  this->applyForwardForce(-ship_properties::BOOST_STRENGTH * this->_forwardVel * 2.0f);
}

void Ship::update(float pElapsedTime)
{
  if (this->_forwardVel != 0.0f)
    applyForwardForce(-ship_properties::BOOST_DRAG * this->_forwardVel);
  if (this->_rotateVel != 0.0f)
    applyRotateForce(ship_properties::TURN_DRAG * this->_rotateVel * -1);

  this->_rotateVel += this->_rotateAcc;
  this->_forwardVel += this->_forwardAcc;

  if (this->_forwardVel > ship_properties::BOOST_SPEED)
    this->_forwardVel = ship_properties::BOOST_SPEED;
  if (this->_forwardVel < ship_properties::BOOST_STRENGTH)
    this->_forwardVel = 0.0f;

  if (std::abs(this->_rotateVel) > ship_properties::TURN_SPEED)
    this->_rotateVel = ship_properties::TURN_SPEED * (this->_rotateVel > 0.0f ? 1 : -1);

  if (this->_rotateVel < ship_properties::TURN_STRENGTH / 10 && this->_rotateVel > ship_properties::TURN_STRENGTH / -10)
    this->_rotateVel = 0.0f;

  this->_x += this->_forwardVel * SDL_cos(this->_degree) * pElapsedTime;
  this->_y += this->_forwardVel * SDL_sin(this->_degree) * pElapsedTime;
  this->_degree += this->_rotateVel * pElapsedTime;

  if (this->_x > game_settings::WIDTH)
    this->_x -= game_settings::WIDTH + ship_properties::WIDTH;
  if (this->_x + ship_properties::WIDTH < 0)
    this->_x += game_settings::WIDTH + ship_properties::WIDTH;
  if (this->_y > game_settings::HEIGHT)
    this->_y -= game_settings::HEIGHT + ship_properties::HEIGHT;
  if (this->_y + ship_properties::HEIGHT < 0)
    this->_y += game_settings::HEIGHT + ship_properties::HEIGHT;

  this->_forwardAcc = 0.0f;
  this->_rotateAcc = 0.0f;
}

void Ship::draw(GameWindow &pWindow)
{
  this->_srcRect.x = SDL_floor(this->_forwardVel / (ship_properties::BOOST_SPEED / 3)) * ship_properties::WIDTH;

  int degree = (this->_degree * 180 / M_PI) - 270;

  RenderUnit::draw(pWindow, 1, degree);
}

void Ship::applyForwardForce(float force)
{
  this->_forwardAcc += force;
}
void Ship::applyRotateForce(float force)
{
  this->_rotateAcc += force;
}

void Ship::shoot(GameWindow &pWindow, std::vector<Bullet> &pBullets)
{
  float centerX = this->_x + ship_properties::WIDTH / 2.0f;
  float centerY = this->_y + ship_properties::HEIGHT / 2.0f;

  pBullets.push_back(Bullet(pWindow, centerX, centerY, this->_degree));
}

bool Ship::collidesWith(SDL_Rect pRect)
{
  return this->_x + ship_properties::WIDTH > pRect.x && this->_x < pRect.x + pRect.w &&
         this->_y<pRect.y + pRect.h &&this->_y + ship_properties::HEIGHT> pRect.y;
}

std::vector<int> Ship::getPos()
{
  return {(int)this->_x, (int)this->_y};
}