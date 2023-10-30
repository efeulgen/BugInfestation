
#ifndef HEAVYSPACEBUG_H
#define HEAVYSPACEBUG_H

#include "SpaceBug.h"
#include "Player.h"
#include <vector>

const double BUG_FIRE_RATE = 3.0;

class HeavySpaceBug : public SpaceBug
{
private:
      double fireCounter;
      double heavyBugSpriteSheetIndex = 0.0;
      double explodeAnimIndex = 0.0;
      bool donePlayingExplodeAnim = false;

      const char *heavyBugSpriteSheet[4] = {"./assets/sprites/heavy_space_bug_2.png", "./assets/sprites/heavy_space_bug.png", "./assets/sprites/heavy_space_bug_1.png", "./assets/sprites/heavy_space_bug.png"};
      std::vector<std::string> bugProjectileSpritesheet = {"./assets/sprites/heavyBug_projectile_1.png", "./assets/sprites/heavyBug_projectile_2.png", "./assets/sprites/heavyBug_projectile_3.png", "./assets/sprites/heavyBug_projectile_4.png"};
      const char *bugExplodeSpriteSheet[7] = {"./assets/sprites/heavySpaceBug_explode_1.png", "./assets/sprites/heavySpaceBug_explode_2.png", "./assets/sprites/heavySpaceBug_explode_3.png", "./assets/sprites/heavySpaceBug_explode_4.png", "./assets/sprites/heavySpaceBug_explode_5.png", "./assets/sprites/heavySpaceBug_explode_6.png", "./assets/sprites/heavySpaceBug_explode_7.png"};

public:
      HeavySpaceBug();
      HeavySpaceBug(glm::vec2 pos, glm::vec2 dir);
      ~HeavySpaceBug();

      void GetDamage(int amount) override;
      void ShootProjectile(Player *player);
      void UpdateSpaceBug(double deltaTime, Player *player = nullptr) override;
      void RenderSpaceBug(SDL_Renderer *gameRenderer) override;
};

#endif
