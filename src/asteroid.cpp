#include <SDL2/SDL.h>
#include <iostream>

#include "GameWindow.hpp"
#include "RenderUnit.hpp"
#include "Asteroid.hpp"

namespace asteroid_properties
{
  const float SPEED = 0.1f;

  const int WIDTH = 32;
  const int HEIGHT = 32;
  const char *FILE_PATH = "res/gfx/asteroid.png";

  const int COLLISION_ANGLE = 40;
}

Asteroid::Asteroid(GameWindow &pWindow) : RenderUnit(pWindow, asteroid_properties::FILE_PATH, 0, 0, asteroid_properties::WIDTH, asteroid_properties::HEIGHT), _scale(1.5f)
{
  float randomDegree = (rand() % 180 - 90) * M_PI / 180;

  switch ((ASTEROID_DIRECTION)(rand() % 4))
  {
  case ASTEROID_UP:
    this->_x = rand() % game_settings::WIDTH;
    this->_y = game_settings::HEIGHT;
    this->_degree = -M_PI / 2 + randomDegree;
    break;
  case ASTEROID_DOWN:
    this->_x = rand() % game_settings::WIDTH;
    this->_y = 0;
    this->_degree = M_PI / 2 + randomDegree;
    break;
  case ASTEROID_LEFT:
    this->_x = game_settings::WIDTH;
    this->_y = rand() % game_settings::HEIGHT;
    this->_degree = M_PI + randomDegree;
    break;
  case ASTEROID_RIGHT:
    this->_x = 0;
    this->_y = rand() % game_settings::HEIGHT;
    this->_degree = randomDegree;
    break;
  }
}

void Asteroid::update(int pElapsedTime)
{
  this->_x += asteroid_properties::SPEED * SDL_cos(this->_degree) * pElapsedTime;
  this->_y += asteroid_properties::SPEED * SDL_sin(this->_degree) * pElapsedTime;
}

void Asteroid::draw(GameWindow &pWindow)
{
  int degree = (this->_degree * 180 / M_PI) - 270;
  RenderUnit::draw(pWindow, this->_scale, degree);
}

SDL_Rect Asteroid::getBoundingBox()
{
  return {(int)this->_x, (int)this->_y, (int)(asteroid_properties::WIDTH * this->_scale), (int)(asteroid_properties::HEIGHT * this->_scale)};
}

Asteroid Asteroid::smash(GameWindow &pWindow)
{
  // this->_srcRect.x = asteroid_properties::WIDTH;
  this->_scale -= 0.5f;
  Asteroid newAsteroid(pWindow);
  newAsteroid.set(this->_scale, this->_degree + asteroid_properties::COLLISION_ANGLE * M_PI / 180, this->_x, this->_y);
  this->_degree -= asteroid_properties::COLLISION_ANGLE * M_PI / 180;
  return newAsteroid;
}

void Asteroid::set(float pScale, float pDegree, float pX, float pY)
{
  this->_scale = pScale;
  this->_degree = pDegree;
  this->_x = pX;
  this->_y = pY;
}

bool Asteroid::offScreen()
{
  return this->_x + asteroid_properties::WIDTH * this->_scale < 0 || this->_x - asteroid_properties::WIDTH * this->_scale > game_settings::WIDTH || this->_y + asteroid_properties::HEIGHT * this->_scale < 0 || this->_y - asteroid_properties::HEIGHT * this->_scale > game_settings::HEIGHT;
}