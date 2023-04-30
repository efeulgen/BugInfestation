
#include "Projectile.h"

#include <iostream>
#include <SDL2/SDL_image.h>

Projectile::Projectile(glm::vec2 direction, double speed) : projectileDirection{direction}, projectileSpeed{speed}
{
    std::cout << "Projectile Constructor" << std::endl;

    projectilePosition = glm::vec2(0.0, 0.0);
}

Projectile::~Projectile()
{
    std::cout << "Projectile Destructor" << std::endl;
}

void Projectile::RenderProjectile(SDL_Renderer *gameRenderer, const char *spriteSheet[], const int spriteSheetSize)
{
    if (spriteSheetSize == 1)
    {
        projectileSurface = IMG_Load(spriteSheet[0]);
    }
    else
    {
        projectileSurface = IMG_Load(spriteSheet[spriteSheetIndex]);
        if (static_cast<int>(animCounter) % spriteSheetSize == modCounter)
        {
            spriteSheetIndex = spriteSheetIndex >= (spriteSheetSize - 1) ? 0 : spriteSheetIndex + 1;
            modCounter = modCounter >= (spriteSheetSize - 1) ? 0 : modCounter + 1;
        }
    }

    SDL_Texture *projectileTexture = SDL_CreateTextureFromSurface(gameRenderer, projectileSurface);
    SDL_FreeSurface(projectileSurface);
    projectileRect = {static_cast<int>(projectilePosition.x), static_cast<int>(projectilePosition.y), 20, 20};
    SDL_RenderCopy(gameRenderer, projectileTexture, NULL, &projectileRect);
    SDL_DestroyTexture(projectileTexture);
}

void Projectile::UpdateProjectile(double deltaTime)
{
    projectilePosition += (projectileDirection * static_cast<float>(projectileSpeed)) * static_cast<float>(deltaTime);

    animCounter += deltaTime * 10.0;
    if (animCounter >= 1000.0)
    {
        animCounter = 0.0;
    }
}

void Projectile::Destroy()
{
    delete this;
}
