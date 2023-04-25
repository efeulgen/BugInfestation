
#ifndef PPROJECTILE_H
#define PPROJECTILE_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class PlayerProjectile
{
private:
    glm::vec2 projectilePosition;
    glm::vec2 projectileSpeed;
    glm::vec2 projectileOffset;

    SDL_Rect projectileRect;

public:
    PlayerProjectile();
    ~PlayerProjectile();
    void RenderPlayerProjectile(SDL_Renderer *gameRenderer);
    void UpdateProjectile(double deltaTime); // update in Player
    void Destroy();

    inline glm::vec2 GetProjectileOffset() { return projectileOffset; }
    inline glm::vec2 GetProjectilePosition() { return projectilePosition; }
    inline SDL_Rect GetProjectileRect() { return projectileRect; }
    inline void SetProjectilePosition(glm::vec2 pos) { projectilePosition = pos; }
};

#endif
