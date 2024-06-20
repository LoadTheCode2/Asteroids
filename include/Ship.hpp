#pragma once

#include <RenderUnit.hpp>

class Ship : public RenderUnit
{
public:
  Ship(GameWindow &pWindow, const char *pFilePath, int pW, int pH);

  void turnLeft();
  void turnRight();
  void stopTurn();

  void boost();
  void stopBoost();

  void draw(GameWindow &pWindow);
  void update(float pElapsedTime);

private:
  float _degree, _dSpeed, _dDegree;
};