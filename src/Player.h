
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "PlayerProjectile.h"

const double FIRE_RATE = 0.25;
const double MAX_HEALTH = 100.0;

class Player
{
private:
    double health;
    double fireCounter;
    bool isDead;
    bool canFire = true;

    glm::vec2 playerPosition;
    glm::vec2 playerSpeed;

    SDL_Rect playerRect;

    std::vector<PlayerProjectile *> projArray;

public:
    Player();
    ~Player();

    void Update(double deltaTime);
    void RenderPlayer(SDL_Renderer *gameRenderer);
    void MoveUp(double deltaTime);
    void MoveDown(double deltaTime);
    void Fire();
    void UpdateProjectiles(double deltaTime);
    void EraseElementFromProjarray(PlayerProjectile *proj);
    void ClearProjArray();
    void GetDamage(double amount);
    void UseJetPack();

    // **********************************************************************************************
    // *************** getters & setters ************************************************************
    std::vector<PlayerProjectile *> GetProjectileArray() { return projArray; }
    SDL_Rect GetPlayerRect() { return playerRect; }

    bool GetCanFire() { return canFire; }
    bool GetIsDead() { return isDead; }
    double GetHealth() { return health; }
};

#endif
