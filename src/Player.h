
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Projectile.h"

const double FIRE_RATE = 0.25;
const double MAX_HEALTH = 100.0;
const double GRAVITY = 200.0;
const int PLAYER_PROJECTILE_SPRITESHEET_SIZE = 1;

class Player
{
private:
    double health;
    double fireCounter;
    bool isDead;
    bool canFire = true;
    double gravityFactor;
    double gravityIncrement = 100.0;
    bool isUsingJetPack;
    bool isFlipped;

    int extraLives;
    int rocketAmount;
    bool isSpeedBoostActive = false;
    double speedBoostDuration = 0.0;

    glm::vec2 playerPosition;
    glm::vec2 playerSpeed;
    glm::vec2 firePos;

    const char *playerProjectileSpriteSheet[PLAYER_PROJECTILE_SPRITESHEET_SIZE] = {"./assets/sprites/PlayerProjectile.png"};

    SDL_Rect playerRect;

    std::vector<Projectile *> projArray;

public:
    Player();
    ~Player();

    void Update(double deltaTime);
    void RenderPlayer(SDL_Renderer *gameRenderer);
    void MoveRight(double deltaTime);
    void MoveLeft(double deltaTime);
    void Fire();
    void UpdateProjectiles(double deltaTime);
    void EraseElementFromProjarray(Projectile *proj);
    void ClearProjArray();
    void GetDamage(double amount);
    void UseJetPack(double deltaTime);
    bool CheckCollision(SDL_Rect other) const;
    void HealPlayer();
    void GainExtraLife();
    void GainRokcet();
    void ActivateSpeedBoost();
    void DeactivateSpeedBoost();

private:
    void RenderJetPackFire(SDL_Renderer *renderer);

    // **********************************************************************************************
    // *************** getters & setters ************************************************************

public:
    std::vector<Projectile *> GetProjectileArray() { return projArray; }
    SDL_Rect GetPlayerRect() { return playerRect; }
    glm::vec2 GetPlayerPos() { return playerPosition; }

    bool GetCanFire() { return canFire; }
    bool GetIsDead() { return isDead; }
    double GetHealth() { return health; }

    bool GetIsUsingJetPack() const { return isUsingJetPack; }
    void SetIsUsingJetPack(bool value) { isUsingJetPack = value; }

    bool GetIsFlipped() const { return isFlipped; }
    void SetIsFlipped(bool val) { isFlipped = val; }

    int GetExtraLives() const { return extraLives; }
    int GetRocketAmount() const { return rocketAmount; }
};

#endif
