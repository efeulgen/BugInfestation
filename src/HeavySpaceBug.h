
#ifndef HEAVYSPACEBUG_H
#define HEAVYSPACEBUG_H

#include "SpaceBug.h"
#include "Projectile.h"
#include <vector>

const double BUG_FIRE_RATE = 1.0;
const int BUG_PROJECTILE_SPRITESHEET_SIZE = 4;

class HeavySpaceBug : public SpaceBug
{
private:
      int health = 3;
      std::vector<Projectile *> projArray;
      double fireCounter = 0.0;

      const char *bugProjectileSpritesheet[BUG_PROJECTILE_SPRITESHEET_SIZE] = {"./assets/heavyBug_projectile_1.png", "./assets/heavyBug_projectile_2.png", "./assets/heavyBug_projectile_3.png", "./assets/heavyBug_projectile_4.png"};

public:
      HeavySpaceBug();
      HeavySpaceBug(glm::vec2 pos, glm::vec2 dir);

      void GetDamage();
      void ShootProjectile(glm::vec2 playerPos);
      void UpdateSpaceBug(double deltaTime, glm::vec2 playerPos);
      void RenderSpaceBug(SDL_Renderer *gameRenderer) override;
};

#endif
