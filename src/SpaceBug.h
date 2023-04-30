
#ifndef SPACEBUG_H
#define SPACEBUG_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Player.h"

const double ANIM_SPEED = 10.0;
const int BUG_SPRITESHEET_SIZE = 4;

class SpaceBug
{
private:
    SDL_Surface *spaceBugSurface = nullptr;
    const char *bugSpriteSheet[BUG_SPRITESHEET_SIZE] = {"./assets/space_bug_2.png", "./assets/space_bug.png", "./assets/space_bug_1.png", "./assets/space_bug.png"};
    double animCounter = 0;
    int spriteSheetIndex = 0;
    int modCounter = 0;

protected:
    glm::vec2 spaceBugPos;
    glm::vec2 spaceBugDirection;
    SDL_Rect spaceBugRect;

public:
    SpaceBug();
    SpaceBug(glm::vec2 initPos, glm::vec2 initDirection);
    virtual ~SpaceBug();
    virtual void UpdateSpaceBug(double deltaTime, Player *player = nullptr);
    virtual void RenderSpaceBug(SDL_Renderer *gameRenderer);
    bool CheckCollision(SDL_Rect other) const;
    void Destroy();

    SDL_Rect GetSpaceBugRect() const { return spaceBugRect; }
};

#endif
