
#ifndef PPROJECTILE_H
#define PPROJECTILE_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

enum ProjectileType
{
    PT_Regular,
    PT_Heavy
};

class Projectile
{
private:
    glm::vec2 projectilePosition;
    glm::vec2 projectileDirection;
    double projectileSpeed;

    double spriteSheetIndex = 0.0;
    SDL_Surface *projectileSurface = nullptr;

    std::vector<std::string> spriteSheet;
    int projRectSize;
    bool isFlipped;

    SDL_Rect projectileRect;
    ProjectileType type;

public:
    Projectile(glm::vec2 direction, double speed, std::vector<std::string> sprites, int size = 20, bool flip = false, ProjectileType t = ProjectileType::PT_Regular);
    ~Projectile();
    void RenderProjectile(SDL_Renderer *gameRenderer);
    void UpdateProjectile(double deltaTime);
    void Destroy();

    // getters & setters
    SDL_Rect GetProjectileRect() { return projectileRect; }
    glm::vec2 GetProjectilePosition() { return projectilePosition; }
    void SetProjectilePosition(glm::vec2 pos) { projectilePosition = pos; }
    ProjectileType GetProjectileType() const { return type; }
};

#endif
