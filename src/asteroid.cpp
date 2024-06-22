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
}

Asteroid::Asteroid() {}

Asteroid::Asteroid(GameWindow &pWindow) : RenderUnit(pWindow, asteroid_properties::FILE_PATH, 0, 0, asteroid_properties::WIDTH, asteroid_properties::HEIGHT)
{
  float randomDegree = (rand() % 180 - 90) * M_PI / 180;

  std::cout << (ASTEROID_DIRECTION)(rand() % 4) << std::endl;

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

void Asteroid::update(int elapsedTime)
{
  this->_x += asteroid_properties::SPEED * SDL_cos(this->_degree) * elapsedTime;
  this->_y += asteroid_properties::SPEED * SDL_sin(this->_degree) * elapsedTime;
}

void Asteroid::draw(GameWindow &pWindow)
{
  RenderUnit::draw(pWindow, 1.5, this->_degree);
}