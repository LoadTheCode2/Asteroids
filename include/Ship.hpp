#pragma once

#include <RenderUnit.hpp>

class Ship : public RenderUnit
{
public:
  Ship(GameWindow &pWindow);

  void turnLeft();
  void turnRight();

  void boost();
  void brake();

  void shoot(GameWindow &pWindow, std::vector<Bullet> &pBullets);
  bool collidesWith(SDL_Rect pRect);

  void draw(GameWindow &pWindow);
  void update(float pElapsedTime);

private:
  float _degree, _rotateVel, _forwardVel;
  float _rotateAcc, _forwardAcc;

  void applyForwardForce(float force);
  void applyRotateForce(float force);
};