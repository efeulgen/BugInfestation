
#ifndef PPROJECTILE_H
#define PPROJECTILE_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Projectile
{
private:
    glm::vec2 projectilePosition;
    glm::vec2 projectileDirection;
    double projectileSpeed;

    SDL_Rect projectileRect;

public:
    Projectile(glm::vec2 direction, double speed);
    ~Projectile();
    void RenderProjectile(SDL_Renderer *gameRenderer); // render in Player
    void UpdateProjectile(double deltaTime);           // update in Player
    void Destroy();

    SDL_Rect GetProjectileRect() { return projectileRect; }
    glm::vec2 GetProjectilePosition() { return projectilePosition; }
    void SetProjectilePosition(glm::vec2 pos) { projectilePosition = pos; }
};

#endif
