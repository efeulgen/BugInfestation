
#ifndef HEAVYSPACEBUG_H
#define HEAVYSPACEBUG_H

#include "SpaceBug.h"
#include "Projectile.h"
#include <vector>

const double BUG_FIRE_RATE = 1.0;

class HeavySpaceBug : public SpaceBug
{
private:
      int health = 3;
      std::vector<Projectile *> projArray;
      double fireCounter = 0.0;

public:
      HeavySpaceBug();
      HeavySpaceBug(glm::vec2 pos, glm::vec2 dir);

      void GetDamage();
      void ShootProjectile(glm::vec2 playerPos);
      void UpdateSpaceBug(double deltaTime, glm::vec2 playerPos);
      void RenderSpaceBug(SDL_Renderer *gameRenderer) override;
};

#endif
