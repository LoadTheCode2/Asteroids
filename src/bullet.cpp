#include <SDL2/SDL.h>
#include <iostream>

#include "GameWindow.hpp"
#include "RenderUnit.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"

namespace bullet_properties
{
  const int WIDTH = 2;
  const int HEIGHT = 8;

  const char *FILE_PATH = "res/gfx/bullet.png";

  const float SPEED = 0.3f;
}

Bullet::Bullet(GameWindow &pWindow, float pX, float pY, float pDegree)
    : RenderUnit(pWindow, bullet_properties::FILE_PATH, pX, pY, bullet_properties::WIDTH, bullet_properties::HEIGHT), _degree(pDegree)
{
}

void Bullet::draw(GameWindow &pWindow)
{
  int degree = (this->_degree * 180 / M_PI) - 270;

  RenderUnit::draw(pWindow, 1, degree);
}

void Bullet::update(int pElapsedTime)
{
  this->_x += bullet_properties::SPEED * SDL_cos(this->_degree) * pElapsedTime;
  this->_y += bullet_properties::SPEED * SDL_sin(this->_degree) * pElapsedTime;
}

bool Bullet::collidesWith(SDL_Rect pRect)
{
  return this->_x + bullet_properties::WIDTH > pRect.x && this->_x < pRect.x + pRect.w &&
         this->_y<pRect.y + pRect.h &&this->_y + bullet_properties::HEIGHT> pRect.y;
}

bool Bullet::offScreen()
{
  return this->_x + bullet_properties::WIDTH < 0 || this->_x - bullet_properties::WIDTH > game_settings::WIDTH || this->_y + bullet_properties::HEIGHT < 0 || this->_y - bullet_properties::HEIGHT > game_settings::HEIGHT;
}