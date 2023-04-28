
#ifndef SPACEBUG_H
#define SPACEBUG_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

const double ANIM_SPEED = 10.0;
const int BUG_SPRITESHEET_SIZE = 4;

class SpaceBug
{
private:
    glm::vec2 spaceBugPos;
    glm::vec2 spaceBugDirection;
    SDL_Surface *spaceBugSurface = nullptr;
    const char *bugSpriteSheet[BUG_SPRITESHEET_SIZE] = {"./assets/space_bug_2.png", "./assets/space_bug.png", "./assets/space_bug_1.png", "./assets/space_bug.png"};
    SDL_Rect spaceBugRect;
    double animCounter = 0;

public:
    SpaceBug();
    SpaceBug(glm::vec2 initPos, glm::vec2 initDirection);
    ~SpaceBug();
    void UpdateSpaceBug(double deltaTime);
    void RenderSpaceBug(SDL_Renderer *gameRenderer);
    bool CheckCollision(SDL_Rect other);
    void Destroy();

    inline SDL_Rect GetSpaceBugRect() { return spaceBugRect; }
};

#endif
