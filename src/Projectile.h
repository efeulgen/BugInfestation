
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

    double animCounter = 0.0;
    int spriteSheetIndex = 0;
    int modCounter = 0;
    SDL_Surface *projectileSurface = nullptr;

    SDL_Rect projectileRect;

public:
    Projectile(glm::vec2 direction, double speed);
    ~Projectile();
    void RenderProjectile(SDL_Renderer *gameRenderer, const char *spriteSheet[], const int spriteSheetSize);
    void UpdateProjectile(double deltaTime);
    void Destroy();

    SDL_Rect GetProjectileRect() { return projectileRect; }
    glm::vec2 GetProjectilePosition() { return projectilePosition; }
    void SetProjectilePosition(glm::vec2 pos) { projectilePosition = pos; }
};

#endif
