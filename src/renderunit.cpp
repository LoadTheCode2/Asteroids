#include <SDL2/SDL.h>

#include "GameWindow.hpp"
#include "RenderUnit.hpp"

RenderUnit::RenderUnit(GameWindow &pWindow, const char *pFilePath, float pX, float pY, int pW, int pH)
    : _x(pX), _y(pY), _texture(pWindow.loadTexture(pFilePath))
{
  this->_srcRect = {0, 0, pW, pH};
}

void RenderUnit::draw(GameWindow &pWindow)
{
  SDL_Rect destRect = {(int)this->_x * game_settings::SCALE,
                       (int)this->_y * game_settings::SCALE,
                       this->_srcRect.w * game_settings::SCALE,
                       this->_srcRect.h * game_settings::SCALE};
  pWindow.renderTexture(this->_texture, &this->_srcRect, &destRect);
}

void RenderUnit::update(int elapsedTime) {}