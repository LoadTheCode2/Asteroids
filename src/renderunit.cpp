#include <SDL2/SDL.h>

#include "GameWindow.hpp"
#include "RenderUnit.hpp"

RenderUnit::RenderUnit() {}

RenderUnit::RenderUnit(GameWindow &pWindow, const char *pFilePath, float pX, float pY, int pW, int pH)
    : _x(pX), _y(pY), _texture(pWindow.loadTexture(pFilePath))
{
  this->_srcRect = {0, 0, pW, pH};
}

void RenderUnit::draw(GameWindow &pWindow, float pScale, float pAngle)
{
  SDL_Rect destRect = {(int)this->_x,
                       (int)this->_y,
                       (int)(this->_srcRect.w * pScale),
                       (int)(this->_srcRect.h * pScale)};

  SDL_Point center = {this->_srcRect.w / 2, this->_srcRect.h / 2};

  pWindow.renderTexture(this->_texture, &this->_srcRect, &destRect, pAngle, &center);
}

void RenderUnit::update(int elapsedTime) {}