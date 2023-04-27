
#include "Player.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "./Logger/Logger.h"

Player::Player() : health{MAX_HEALTH}, fireCounter{FIRE_RATE}, isDead{false}
{
    std::cout << "Player Constructor" << std::endl;

    playerPosition = glm::vec2(40.0, 40.0);
    playerSpeed = glm::vec2(0.0, 500.0);
}

Player::~Player()
{
    std::cout << "Player Destructor" << std::endl;
}

void Player::Update(double deltaTime)
{
    if (fireCounter < FIRE_RATE)
    {
        fireCounter += deltaTime;
    }
    if (fireCounter > FIRE_RATE)
    {
        fireCounter = FIRE_RATE;
        canFire = true;
    }

    if (!projArray.empty())
    {
        UpdateProjectiles(deltaTime);
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

void Player::MoveUp(double deltaTime)
{
    playerPosition.x -= playerSpeed.x * deltaTime;
    playerPosition.y -= playerSpeed.y * deltaTime;
}

void Player::MoveDown(double deltaTime)
{
    playerPosition.x += playerSpeed.x * deltaTime;
    playerPosition.y += playerSpeed.y * deltaTime;
}

void Player::Fire()
{
    PlayerProjectile *newProjectile = new PlayerProjectile();
    newProjectile->SetProjectilePosition(playerPosition + newProjectile->GetProjectileOffset());
    projArray.push_back(newProjectile);

    canFire = false;
    fireCounter = 0.0;
}

void Player::UpdateProjectiles(double deltaTime)
{
    if (projArray.empty())
        return;
    for (auto projectile : projArray)
    {
        projectile->UpdateProjectile(deltaTime);
        if (projectile->GetProjectilePosition().x - playerPosition.x > 1280.0)
        {
            projArray.erase(std::remove(projArray.begin(), projArray.end(), projectile), projArray.end());
            projectile->Destroy();
            projectile = nullptr;
        }
    }
}

void Player::EraseElementFromProjarray(PlayerProjectile *proj)
{
    projArray.erase(std::remove(projArray.begin(), projArray.end(), proj), projArray.end());
}

void Player::ClearProjArray()
{
    for (auto proj : projArray)
    {
        proj->Destroy();
        proj = nullptr;
    }
    projArray.clear();
}

void Player::GetDamage(double amount)
{
    health -= amount;
    Logger::Err("Player gets damage.");
    if (health <= 0.0)
    {
        Logger::Err("Player is dead.");
        isDead = true;
    }
}
