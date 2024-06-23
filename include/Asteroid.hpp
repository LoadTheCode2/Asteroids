#pragma once

enum ASTEROID_DIRECTION
{
  ASTEROID_UP,
  ASTEROID_DOWN,
  ASTEROID_LEFT,
  ASTEROID_RIGHT
};

#include <RenderUnit.hpp>

class Ship;

struct SDL_Rect;

class Asteroid : public RenderUnit
{
public:
  Asteroid();
  Asteroid(GameWindow &pWindow, Ship &pShip);

  void draw(GameWindow &pWindow);
  void update(int pElapsedTime);
  Asteroid smash(GameWindow &pWindow, Ship &pShip);

  void set(float pScale, float pDegree, float pX, float pY);

  bool offScreen();

  SDL_Rect getBoundingBox();

private:
  float _degree, _scale;
};