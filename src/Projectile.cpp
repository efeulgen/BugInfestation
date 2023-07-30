
#include "Projectile.h"

#include <iostream>
#include <SDL2/SDL_image.h>

Projectile::Projectile(glm::vec2 direction, double speed, int size) : projectileDirection{direction}, projectileSpeed{speed}
{
    // std::cout << "Projectile Constructor" << std::endl;

    projectilePosition = glm::vec2(0.0, 0.0);
    projRectSize = size;
}

Projectile::~Projectile()
{
    // std::cout << "Projectile Destructor" << std::endl;
}

void Projectile::RenderProjectile(SDL_Renderer *gameRenderer, const char *spriteSheet[], const int spriteSheetSize)
{
    if (spriteSheetSize == 1)
    {
        projectileSurface = IMG_Load(spriteSheet[0]);
    }
    else
    {
        if (static_cast<int>(spriteSheetIndex) > spriteSheetSize - 1)
        {
            spriteSheetIndex = 0.0;
        }
        projectileSurface = IMG_Load(spriteSheet[static_cast<int>(spriteSheetIndex)]);
    }

    SDL_Texture *projectileTexture = SDL_CreateTextureFromSurface(gameRenderer, projectileSurface);
    SDL_FreeSurface(projectileSurface);
    projectileRect = {static_cast<int>(projectilePosition.x), static_cast<int>(projectilePosition.y), projRectSize, projRectSize};
    SDL_RenderCopy(gameRenderer, projectileTexture, NULL, &projectileRect);
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
