
#ifndef SPACEBUG_H
#define SPACEBUG_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class SpaceBug
{
private:
    glm::vec2 spaceBugPos;
    glm::vec2 spaceBugDirection;
    SDL_Rect spaceBugRect;

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
