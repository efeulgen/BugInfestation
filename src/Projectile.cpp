
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

void Projectile::RenderProjectile(SDL_Renderer *gameRenderer)
{
    SDL_Surface *projectileSurface = IMG_Load("./assets/PlayerProjectile.png");
    SDL_Texture *projectileTexture = SDL_CreateTextureFromSurface(gameRenderer, projectileSurface);
    SDL_FreeSurface(projectileSurface);
    projectileRect = {static_cast<int>(projectilePosition.x), static_cast<int>(projectilePosition.y), 20, 20};
    SDL_RenderCopy(gameRenderer, projectileTexture, NULL, &projectileRect);
    SDL_DestroyTexture(projectileTexture);
}

void Projectile::UpdateProjectile(double deltaTime)
{
    projectilePosition += (projectileDirection * static_cast<float>(projectileSpeed)) * static_cast<float>(deltaTime);
}

void Projectile::Destroy()
{
    delete this;
}
