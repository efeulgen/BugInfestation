
#include "PlayerProjectile.h"

#include <iostream>
#include <SDL2/SDL_image.h>

PlayerProjectile::PlayerProjectile()
{
    std::cout << "PlayerProjectile Constructor" << std::endl;

    projectilePosition = glm::vec2(0.0, 0.0);
    projectileSpeed = glm::vec2(20.0, 0.0);
    projectileOffset = glm::vec2(105.0, 64.0);
}

PlayerProjectile::~PlayerProjectile()
{
    std::cout << "PlayerProjectile Destructor" << std::endl;
}

void PlayerProjectile::RenderPlayerProjectile(SDL_Renderer *gameRenderer)
{
    SDL_Surface *projectileSurface = IMG_Load("./assets/PlayerProjectile.png");
    SDL_Texture *projectileTexture = SDL_CreateTextureFromSurface(gameRenderer, projectileSurface);
    SDL_FreeSurface(projectileSurface);
    projectileRect = {static_cast<int>(projectilePosition.x), static_cast<int>(projectilePosition.y), 20, 20};
    SDL_RenderCopy(gameRenderer, projectileTexture, NULL, &projectileRect);
    SDL_DestroyTexture(projectileTexture);
}

void PlayerProjectile::UpdateProjectile()
{
    projectilePosition += projectileSpeed;
}

void PlayerProjectile::Destroy()
{
    delete this;
}
