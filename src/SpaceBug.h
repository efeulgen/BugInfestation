
#ifndef SPACEBUG_H
#define SPACEBUG_H

#include <iostream>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Logger/Logger.h"

const double ANIM_SPEED = 10.0;

enum BugType
{
    Regular,
    Heavy,
    Bladed
};

class SpaceBug
{
private:
    SDL_Surface *spaceBugSurface = nullptr;
    const char *bugSpriteSheet[4] = {"./assets/sprites/space_bug_2.png", "./assets/sprites/space_bug.png", "./assets/sprites/space_bug_1.png", "./assets/sprites/space_bug.png"};

protected:
    glm::vec2 spaceBugPos;
    glm::vec2 spaceBugDirection;
    SDL_Rect spaceBugRect;
    std::vector<Projectile *> projArray;

    BugType type;

    int health;
    bool isFlipped = true;
    bool isDestructible = false;
    bool canDamagePlayer = true;
    double spriteSheetIndex = 0.0;

public:
    SpaceBug();
    SpaceBug(glm::vec2 initPos, glm::vec2 initDirection);
    virtual ~SpaceBug();
    virtual void UpdateSpaceBug(double deltaTime, Player *player = nullptr);
    virtual void RenderSpaceBug(SDL_Renderer *gameRenderer);
    virtual void GetDamage();
    bool CheckCollision(SDL_Rect other) const;
    void Destroy();
    void EraseElementFromProjarray(Projectile *proj);

    // getters & setters
    SDL_Rect GetSpaceBugRect() const { return spaceBugRect; }
    bool GetIsDestructible() const { return isDestructible; }

    bool GetCanDamagePlayer() const { return canDamagePlayer; }
    void SetCanDamagePlayer(bool value) { canDamagePlayer = value; }

    std::vector<Projectile *> GetBugProjArraj() const { return projArray; }
    BugType GetBugType() { return type; }
};

#endif
