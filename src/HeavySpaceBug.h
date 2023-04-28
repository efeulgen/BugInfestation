
#ifndef HEAVYSPACEBUG_H
#define HEAVYSPACEBUG_H

#include "SpaceBug.h"

class HeavySpaceBug : public SpaceBug
{
private:
      int health = 3;

public:
      HeavySpaceBug();
      HeavySpaceBug(glm::vec2 pos, glm::vec2 dir);

      void GetDamage();
      void ShootProjectile();
      void RenderSpaceBug(SDL_Renderer *gameRenderer) override;
};

#endif
