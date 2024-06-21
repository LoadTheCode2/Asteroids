#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

#include "Ship.hpp"
#include "RenderUnit.hpp"
#include "GameWindow.hpp"

namespace ship_properties
{
  const float TURN_SPEED = 0.005f;
  const float TURN_STRENGTH = 0.001f;
  const float TURN_DRAG = 0.05f;

  const float BOOST_SPEED = 0.2f;
  const float BOOST_STRENGTH = 0.005f;
  const float BOOST_DRAG = 0.02f;
}

Ship::Ship(GameWindow &pWindow, const char *pFilePath, int pW, int pH) : RenderUnit(pWindow, pFilePath, (game_settings::WIDTH - pW / 2) / 2, (game_settings::HEIGHT - pH / 2) / 2, pW, pH), _degree(-M_PI / 2), _forwardVel(0.0f), _rotateVel(0.0f), _forwardAcc(0.0f), _rotateAcc(0.0f) {}

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
  if (this->_forwardVel < 0.0f)
    this->_forwardVel = 0.0f;

  if (abs(this->_rotateVel) > ship_properties::TURN_SPEED)
    this->_rotateVel = ship_properties::TURN_SPEED * (this->_rotateVel > 0.0f ? 1 : -1);

  if (this->_rotateVel < ship_properties::TURN_STRENGTH / 10 && this->_rotateVel > ship_properties::TURN_STRENGTH / -10)
    this->_rotateVel = 0.0f;

  this->_x += this->_forwardVel * SDL_cos(this->_degree) * pElapsedTime;
  this->_y += this->_forwardVel * SDL_sin(this->_degree) * pElapsedTime;
  this->_degree += this->_rotateVel * pElapsedTime;

  if (this->_x > game_settings::WIDTH)
    this->_x -= game_settings::WIDTH + this->_srcRect.w / 2;
  if (this->_x + this->_srcRect.w / 2 < 0)
    this->_x += game_settings::WIDTH + this->_srcRect.w / 2;
  if (this->_y > game_settings::HEIGHT)
    this->_y -= game_settings::HEIGHT + this->_srcRect.h / 2;
  if (this->_y + this->_srcRect.h / 2 < 0)
    this->_y += game_settings::HEIGHT + this->_srcRect.h / 2;

  this->_forwardAcc = 0.0f;
  this->_rotateAcc = 0.0f;
}

void Ship::draw(GameWindow &pWindow)
{
  this->_srcRect.x = floor(this->_forwardVel / (ship_properties::BOOST_SPEED / 3)) * this->_srcRect.w;

  SDL_Rect destRect = {(int)this->_x * game_settings::SCALE,
                       (int)this->_y * game_settings::SCALE,
                       this->_srcRect.w * game_settings::SCALE / 2,
                       this->_srcRect.h * game_settings::SCALE / 2};

  SDL_Point center = {this->_srcRect.w / 2, this->_srcRect.h / 2};
  int degree = (this->_degree * 180 / M_PI) - 270;

  pWindow.renderTexture(this->_texture, &this->_srcRect, &destRect, degree, NULL);
}

void Ship::applyForwardForce(float force)
{
  this->_forwardAcc += force;
}
void Ship::applyRotateForce(float force)
{
  this->_rotateAcc += force;
}