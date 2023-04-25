
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "PlayerProjectile.h"

class Player
{
private:
    double health;
    // const double maxHealth = 100.0;
    double fireCounter = 5.0;
    double fireRate = 5.0;
    bool isDead;

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

    // *************** getters & setters ***************
    std::vector<PlayerProjectile *> GetProjectileArray() { return projArray; }
    SDL_Rect GetPlayerRect() { return playerRect; }

    bool GetIsDead() { return isDead; }

    double GetHealth() { return health; }
};

#endif
