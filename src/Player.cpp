
#include "Player.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

Player::Player() : health{100.0}, isDead{false}
{
    std::cout << "Player Constructor" << std::endl;

    playerPosition = glm::vec2(40.0, 40.0);
    playerSpeed = glm::vec2(0, 5.0);
}

Player::~Player()
{
    std::cout << "Player Destructor" << std::endl;
}

void Player::Update()
{
    if (fireCounter < fireRate)
    {
        fireCounter++;
    }
    if (fireCounter > fireRate)
    {
        fireCounter = fireRate;
    }

    if (!projArray.empty())
    {
        UpdateProjectiles();
    }
}

void Player::RenderPlayer(SDL_Renderer *gameRenderer)
{
    SDL_Surface *playerSurface = IMG_Load("./assets/astro-K-47.png");
    SDL_Texture *playertexture = SDL_CreateTextureFromSurface(gameRenderer, playerSurface);
    SDL_FreeSurface(playerSurface);
    playerRect = {static_cast<int>(playerPosition.x), static_cast<int>(playerPosition.y), 128, 128};
    SDL_RenderCopy(gameRenderer, playertexture, NULL, &playerRect);
    SDL_DestroyTexture(playertexture);

    for (auto projectile : projArray)
    {
        projectile->RenderPlayerProjectile(gameRenderer);
    }
}

void Player::MoveUp()
{
    playerPosition -= playerSpeed;
}

void Player::MoveDown()
{
    playerPosition += playerSpeed;
}

void Player::Fire()
{
    PlayerProjectile *newProjectile = new PlayerProjectile();
    newProjectile->SetProjectilePosition(playerPosition + newProjectile->GetProjectileOffset());
    projArray.push_back(newProjectile);

    fireCounter = 0.0;
}

void Player::UpdateProjectiles()
{
    if (projArray.empty())
        return;
    for (auto projectile : projArray)
    {
        projectile->UpdateProjectile();
        if (projectile->GetProjectilePosition().x - playerPosition.x > 2500.0)
        {
            projArray.erase(std::remove(projArray.begin(), projArray.end(), projectile), projArray.end());
            projectile->Destroy();
        }
    }
}

void Player::EraseElementFromProjarray(PlayerProjectile *proj)
{
    projArray.erase(std::remove(projArray.begin(), projArray.end(), proj), projArray.end());
}

void Player::GetDamage(double amount)
{
    health -= amount;
    if (health <= 0.0)
    {
        std::cout << "Player is dead." << std::endl;
        isDead = true;
    }
}
