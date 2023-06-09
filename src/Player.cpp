
#include "Player.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "./Logger/Logger.h"

Player::Player() : health{MAX_HEALTH}, fireCounter{FIRE_RATE}, isDead{false}, gravityFactor{GRAVITY}, isUsingJetPack{false}, isFlipped{false}
{
    std::cout << "Player Constructor" << std::endl;

    playerPosition = glm::vec2(40.0, 40.0);
    playerSpeed = glm::vec2(300.0, 350.0);
    firePos = glm::vec2(105.0, 64.0);

    extraLives = 0;
    rocketAmount = 0;
}

Player::~Player()
{
    std::cout << "Player Destructor" << std::endl;
}

void Player::Update(double deltaTime)
{
    if (fireCounter < (FIRE_RATE - fireBoost))
    {
        fireCounter += deltaTime;
    }
    if (fireCounter > (FIRE_RATE - fireBoost))
    {
        fireCounter = (FIRE_RATE - fireBoost);
        canFire = true;
    }

    if (!projArray.empty())
    {
        UpdateProjectiles(deltaTime);
    }

    // *************** bound checking *********************************************
    if (playerPosition.y <= 0.0)
    {
        playerPosition.y = 0.0;
    }
    if (playerPosition.y >= 720.0)
    {
        playerPosition.y = 720.0;
    }
    if (playerPosition.x <= 0.0)
    {
        playerPosition.x = 0.0;
    }
    if (playerPosition.x >= 1152.0)
    {
        playerPosition.x = 1152.0;
    }

    // *************** apply gravity *********************************************
    if (!isUsingJetPack)
    {
        gravityFactor += (gravityIncrement * deltaTime);
        playerPosition.y += (gravityFactor * deltaTime);
    }

    // *************** boost *********************************************
    if (isSpeedBoostActive)
    {
        speedBoostDuration += deltaTime;
        if (speedBoostDuration >= 10.0)
        {
            DeactivateSpeedBoost();
            speedBoostDuration = 0.0;
        }
    }

    if (isFireRateBoostActive)
    {
        fireRateBoostDuration += deltaTime;
        if (fireRateBoostDuration >= 15.0)
        {
            DeactivateFireRateBoost();
            fireRateBoostDuration = 0.0;
        }
    }

    // update anima counters
    jetPackAnimCounter += deltaTime * JETPACK_ANIM_SPEED;
}

void Player::RenderPlayer(SDL_Renderer *gameRenderer)
{

    SDL_Surface *playerSurface = IMG_Load("./assets/sprites/astro-K-47.png");
    SDL_Texture *playertexture = SDL_CreateTextureFromSurface(gameRenderer, playerSurface);
    SDL_FreeSurface(playerSurface);
    playerRect = {static_cast<int>(playerPosition.x), static_cast<int>(playerPosition.y), 128, 128};

    if (isFlipped)
    {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(gameRenderer, playertexture, NULL, &playerRect, 0.0, NULL, flip);
    }
    else
    {
        SDL_RenderCopy(gameRenderer, playertexture, NULL, &playerRect);
    }
    SDL_DestroyTexture(playertexture);

    for (auto projectile : projArray)
    {
        projectile->RenderProjectile(gameRenderer, playerProjectileSpriteSheet, PLAYER_PROJECTILE_SPRITESHEET_SIZE);
    }

    if (isUsingJetPack)
    {
        RenderJetPackFire(gameRenderer);
    }
}

void Player::MoveRight(double deltaTime)
{
    playerPosition.x += playerSpeed.x * deltaTime;
    SetIsFlipped(false);
}
void Player::MoveLeft(double deltaTime)
{
    playerPosition.x -= playerSpeed.x * deltaTime;
    SetIsFlipped(true);
}

void Player::Fire()
{
    double projSpeed = isFlipped ? -1000.0 : 1000.0;
    firePos = isFlipped ? glm::vec2(-40.0, 64.0) : glm::vec2(105.0, 64.0);
    Projectile *newProjectile = new Projectile(glm::vec2(1, 0), projSpeed);
    newProjectile->SetProjectilePosition(playerPosition + firePos);
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

void Player::EraseElementFromProjarray(Projectile *proj)
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
    if (health <= 0.0)
    {
        if (extraLives > 0)
        {
            extraLives--;
            health = MAX_HEALTH;
        }
        else
        {
            isDead = true;
        }
    }
}

void Player::UseJetPack(double deltaTime)
{
    isUsingJetPack = true;
    gravityFactor = GRAVITY;
    playerPosition.y -= playerSpeed.y * deltaTime;
}

bool Player::CheckCollision(SDL_Rect other) const
{
    if (SDL_HasIntersection(&playerRect, &other))
    {
        return true;
    }
    return false;
}

void Player::HealPlayer()
{
    health = health + 10.0 > 100.0 ? 100.0 : health + 10.0;
}

void Player::GainExtraLife()
{
    extraLives = extraLives + 1 > 5 ? 5 : extraLives + 1;
}

void Player::GainRokcet()
{
    rocketAmount++;
}

void Player::ActivateSpeedBoost()
{
    playerSpeed.x *= 2.0;
    isSpeedBoostActive = true;
}

void Player::DeactivateSpeedBoost()
{
    playerSpeed.x /= 2.0;
    isSpeedBoostActive = false;
}

void Player::ActivateFireRateBoost()
{
    fireBoost = 0.2;
    isFireRateBoostActive = true;
}

void Player::DeactivateFireRateBoost()
{
    fireBoost = 0.0;
    isFireRateBoostActive = false;
}

void Player::RenderJetPackFire(SDL_Renderer *renderer)
{
    SDL_Surface *surf = IMG_Load(playerJetPackSpriteSheet[jetPackSpriteSheetIndex]);
    if (static_cast<int>(jetPackAnimCounter) % PLAYER_JETPACK_SPRITESHEET_SIZE == jetPackModCounter)
    {
        jetPackSpriteSheetIndex = jetPackSpriteSheetIndex >= (PLAYER_JETPACK_SPRITESHEET_SIZE - 1) ? 0 : jetPackSpriteSheetIndex + 1;
        jetPackModCounter = jetPackModCounter >= (PLAYER_JETPACK_SPRITESHEET_SIZE - 1) ? 0 : jetPackModCounter + 1;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    SDL_Rect jetPackFireRect = {static_cast<int>(playerPosition.x), static_cast<int>(playerPosition.y), 128, 128};

    if (!isFlipped)
    {
        SDL_RenderCopy(renderer, tex, NULL, &jetPackFireRect);
    }
    else
    {
        SDL_RendererFlip jpFlip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer, tex, NULL, &jetPackFireRect, 0.0, NULL, jpFlip);
    }

    SDL_DestroyTexture(tex);
}
