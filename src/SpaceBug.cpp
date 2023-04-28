
#include "SpaceBug.h"

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Logger/Logger.h"

SpaceBug::SpaceBug()
{
    std::cout << "SpaceBug Constructor" << std::endl;
}

SpaceBug::SpaceBug(glm::vec2 initPos, glm::vec2 initDirection) : spaceBugPos{initPos}, spaceBugDirection{initDirection}
{
}

SpaceBug::~SpaceBug()
{
    std::cout << "SpaceBug Destructor" << std::endl;
}

void SpaceBug::UpdateSpaceBug(double deltaTime)
{
    spaceBugPos.x += spaceBugDirection.x * deltaTime;
    spaceBugPos.y += spaceBugDirection.y * deltaTime;
    if (spaceBugPos.x <= 0 || spaceBugPos.x >= (1280 - 64))
    {
        spaceBugDirection.x *= -1;
    }
    if (spaceBugPos.y <= 0 || spaceBugPos.y >= (720 - 64))
    {
        spaceBugDirection.y *= -1;
    }

    animCounter += deltaTime * ANIM_SPEED;
}

void SpaceBug::RenderSpaceBug(SDL_Renderer *gameRenderer)
{
    if (static_cast<int>(animCounter) % BUG_SPRITESHEET_SIZE == 0)
    {
        spaceBugSurface = IMG_Load(bugSpriteSheet[0]);
    }
    else if (static_cast<int>(animCounter) % BUG_SPRITESHEET_SIZE == 1)
    {
        spaceBugSurface = IMG_Load(bugSpriteSheet[1]);
    }
    else if (static_cast<int>(animCounter) % BUG_SPRITESHEET_SIZE == 2)
    {
        spaceBugSurface = IMG_Load(bugSpriteSheet[2]);
    }
    else
    {
        spaceBugSurface = IMG_Load(bugSpriteSheet[3]);
    }
    SDL_Texture *spaceBugTexture = SDL_CreateTextureFromSurface(gameRenderer, spaceBugSurface);
    SDL_FreeSurface(spaceBugSurface);
    spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 64, 64};
    SDL_RenderCopy(gameRenderer, spaceBugTexture, NULL, &spaceBugRect);
    SDL_DestroyTexture(spaceBugTexture);
}

bool SpaceBug::CheckCollision(SDL_Rect other) const
{
    if (SDL_HasIntersection(&spaceBugRect, &other))
    {
        return true;
    }
    return false;
}

void SpaceBug::Destroy()
{
    delete this;
}
