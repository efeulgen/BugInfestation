
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
    double fireCounter = 100.0;
    double fireRate = 100.0;
    bool isDead;
    int score;

    glm::vec2 playerPosition;
    glm::vec2 playerSpeed;

    SDL_Rect playerRect;

    std::vector<PlayerProjectile *> projArray;

public:
    Player();
    ~Player();

    void Update();
    void RenderPlayer(SDL_Renderer *gameRenderer);
    void MoveUp();
    void MoveDown();
    void Fire();
    void UpdateProjectiles();
    void EraseElementFromProjarray(PlayerProjectile *proj);
    void GetDamage(double amount);

    // *************** getters & setters ***************
    std::vector<PlayerProjectile *> GetProjectileArray() { return projArray; }
    SDL_Rect GetPlayerRect() { return playerRect; }
    bool GetIsDead() { return isDead; }

    int GetScore() { return score; }
    void IncrementScore() { score++; }
};

#endif
