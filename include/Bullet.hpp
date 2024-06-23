#pragma once

#include "RenderUnit.hpp"

struct SDL_Rect;

class Bullet : public RenderUnit
{
public:
  Bullet(GameWindow &pWindow, float pX, float pY, float pDegree);
  void draw(GameWindow &pWindow);
  void update(int pElapsedTime);

  bool collidesWith(SDL_Rect pRect);
  bool offScreen();

private:
  float _degree;
};