#pragma once

enum ASTEROID_DIRECTION
{
  ASTEROID_UP,
  ASTEROID_DOWN,
  ASTEROID_LEFT,
  ASTEROID_RIGHT
};

class Asteroid : public RenderUnit
{
public:
  Asteroid();
  Asteroid(GameWindow &pWindow);

  void draw(GameWindow &pWindow);
  void update(int elapsedTime);

private:
  float _degree;
};