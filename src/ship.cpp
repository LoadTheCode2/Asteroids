#include <SDL2/SDL.h>

#include "Ship.hpp"
#include "RenderUnit.hpp"
#include "GameWindow.hpp"

namespace ship_properties
{
  const float TURN_LIMIT = 0.01f;
  const float TURN_ACCELERATION = 0.0025f;
  // const float SPEED = 0.2f;
  const float ACCELERATION = 0.005f;
  const float SPEED_LIMIT = 0.2f;
  const float DRAG_STRENGTH = 0.0001f;
  const float TURN_DRAG_STRENGTH = 0.00005f;
  const float PI = 2 * std::acos(0.0);
}

Ship::Ship(GameWindow &pWindow, const char *pFilePath, int pW, int pH) : RenderUnit(pWindow, pFilePath, game_settings::WIDTH / 2, game_settings::HEIGHT / 2, pW, pH), _degree(-ship_properties::PI / 2), _dSpeed(0.0f), _dDegree(0.0f) {}

void Ship::turnLeft()
{
  this->_dDegree -= ship_properties::TURN_ACCELERATION;
}

void Ship::turnRight()
{
  this->_dDegree += ship_properties::TURN_ACCELERATION;
}

void Ship::stopTurn()
{
  // this->_dDegree = 0;
}

void Ship::boost()
{
  // this->_dx = ship_properties::SPEED * cos(this->_degree);
  // this->_dy = ship_properties::SPEED * sin(this->_degree);
  this->_dSpeed += ship_properties::ACCELERATION;
}

void Ship::stopBoost()
{
  // this->_dx = 0;
  // this->_dy = 0;
}

void Ship::update(float pElapsedTime)
{
  if (this->_dSpeed > ship_properties::SPEED_LIMIT)
    this->_dSpeed = ship_properties::SPEED_LIMIT;
  if (this->_dSpeed > 0.0f)
    this->_dSpeed -= ship_properties::DRAG_STRENGTH * pElapsedTime;
  else
    this->_dSpeed = 0.0f;

  if (abs(this->_dDegree) > ship_properties::TURN_LIMIT)
    this->_dDegree = this->_dDegree > 0.0f ? ship_properties::TURN_LIMIT : -(ship_properties::TURN_LIMIT);
  if (this->_dDegree > ship_properties::TURN_DRAG_STRENGTH)
    this->_dDegree -= ship_properties::TURN_DRAG_STRENGTH * pElapsedTime;
  else if (this->_dDegree < -ship_properties::TURN_DRAG_STRENGTH)
    this->_dDegree += ship_properties::TURN_DRAG_STRENGTH * pElapsedTime;
  else
    this->_dDegree = 0;

  this->_x += this->_dSpeed * cos(this->_degree) * pElapsedTime;
  this->_y += this->_dSpeed * sin(this->_degree) * pElapsedTime;
  this->_degree += this->_dDegree * pElapsedTime;
}

void Ship::draw(GameWindow &pWindow)
{
  SDL_Rect destRect = {(int)this->_x * game_settings::SCALE,
                       (int)this->_y * game_settings::SCALE,
                       this->_srcRect.w * game_settings::SCALE,
                       this->_srcRect.h * game_settings::SCALE};
  SDL_Point center = {this->_srcRect.w / 2, this->_srcRect.h / 2};
  // printf("DEGREE %.2f D DEGREE %.2f\n", this->_degree, this->_dDegree);
  int degree = (this->_degree * 180 / ship_properties::PI) - 270;
  pWindow.renderTexture(this->_texture, &this->_srcRect, &destRect, degree, NULL);
}