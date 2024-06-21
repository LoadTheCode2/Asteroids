#pragma once

#include <RenderUnit.hpp>

class Ship : public RenderUnit
{
public:
  Ship(GameWindow &pWindow, const char *pFilePath, int pW, int pH);

  void turnLeft();
  void turnRight();

  void boost();
  void brake();

  void draw(GameWindow &pWindow);
  void update(float pElapsedTime);

private:
  float _degree, _rotateVel, _forwardVel;
  float _rotateAcc, _forwardAcc;

  void applyForwardForce(float force);
  void applyRotateForce(float force);
};