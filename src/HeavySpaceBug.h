
#ifndef HEAVYSPACEBUG_H
#define HEAVYSPACEBUG_H

#include "SpaceBug.h"
#include "Player.h"
#include <vector>

const double BUG_FIRE_RATE = 3.0;
const int BUG_PROJECTILE_SPRITESHEET_SIZE = 4;
const int HEAVY_BUG_SPRITESHEET_SIZE = 4;

class HeavySpaceBug : public SpaceBug
{
private:
      double fireCounter;
      bool isDead = false;

      const char *heavyBugSpriteSheet[HEAVY_BUG_SPRITESHEET_SIZE] = {"./assets/heavy_space_bug_2.png", "./assets/heavy_space_bug.png", "./assets/heavy_space_bug_1.png", "./assets/heavy_space_bug.png"};
      const char *bugProjectileSpritesheet[BUG_PROJECTILE_SPRITESHEET_SIZE] = {"./assets/heavyBug_projectile_1.png", "./assets/heavyBug_projectile_2.png", "./assets/heavyBug_projectile_3.png", "./assets/heavyBug_projectile_4.png"};

public:
      HeavySpaceBug();
      HeavySpaceBug(glm::vec2 pos, glm::vec2 dir);

      void GetDamage() override;
      void ShootProjectile(Player *player);
      void UpdateSpaceBug(double deltaTime, Player *player = nullptr) override;
      void RenderSpaceBug(SDL_Renderer *gameRenderer) override;
};

#endif
