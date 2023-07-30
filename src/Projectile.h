
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

    double spriteSheetIndex = 0.0;
    SDL_Surface *projectileSurface = nullptr;

    int projRectSize;

    SDL_Rect projectileRect;

public:
    Projectile(glm::vec2 direction, double speed, int size = 20);
    ~Projectile();
    void RenderProjectile(SDL_Renderer *gameRenderer, const char *spriteSheet[], const int spriteSheetSize);
    void UpdateProjectile(double deltaTime);
    void Destroy();

    // getters & setters
    SDL_Rect GetProjectileRect() { return projectileRect; }
    glm::vec2 GetProjectilePosition() { return projectilePosition; }
    void SetProjectilePosition(glm::vec2 pos) { projectilePosition = pos; }
};

#endif
