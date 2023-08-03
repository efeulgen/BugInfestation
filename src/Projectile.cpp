
#include "Projectile.h"

#include <iostream>
#include <SDL2/SDL_image.h>

Projectile::Projectile(glm::vec2 direction, double speed, std::vector<std::string> sprites, int size, bool flip, ProjectileType t) : projectileDirection{direction}, projectileSpeed{speed}, projectileRect{0, 0, 0, 0}
{
    // std::cout << "Projectile Constructor" << std::endl;

    projectilePosition = glm::vec2(0.0, 0.0);
    projRectSize = size;
    spriteSheet = sprites;
    isFlipped = flip;
    type = t;
}

Projectile::~Projectile()
{
    // std::cout << "Projectile Destructor" << std::endl;
}

void Projectile::RenderProjectile(SDL_Renderer *gameRenderer)
{
    if (spriteSheet.size() == 1)
    {
        projectileSurface = IMG_Load(spriteSheet[0].c_str());
    }
    else
    {
        if (static_cast<int>(spriteSheetIndex) > spriteSheet.size() - 1)
        {
            spriteSheetIndex = 0.0;
        }
        projectileSurface = IMG_Load(spriteSheet[static_cast<int>(spriteSheetIndex)].c_str());
    }

    SDL_Texture *projectileTexture = SDL_CreateTextureFromSurface(gameRenderer, projectileSurface);
    SDL_FreeSurface(projectileSurface);
    projectileRect = {static_cast<int>(projectilePosition.x), static_cast<int>(projectilePosition.y), projRectSize, projRectSize};
    if (isFlipped)
    {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(gameRenderer, projectileTexture, NULL, &projectileRect, 0.0, NULL, flip);
    }
    else
    {
        SDL_RenderCopy(gameRenderer, projectileTexture, NULL, &projectileRect);
    }
    SDL_DestroyTexture(projectileTexture);
}

void Projectile::UpdateProjectile(double deltaTime)
{
    projectilePosition += (projectileDirection * static_cast<float>(projectileSpeed)) * static_cast<float>(deltaTime);

    spriteSheetIndex += deltaTime * 10.0;
}

void Projectile::Destroy()
{
    delete this;
}
