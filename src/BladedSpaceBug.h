
#ifndef BLADEDSPACEBUG_H
#define BLADEDSPACEBUG_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "SpaceBug.h"
#include "Player.h"

enum BladedSpaceBugState
{
      Patroling,
      Attacking
};

const double ATTACK_DURATION = 1.5;
const double PATROL_DURATION = 5.0;

class BladedSpaceBug : public SpaceBug
{
private:
      double normalSpeed;
      double attackSpeed;
      double attackDuration;
      double patrolDuration;

      std::vector<glm::vec2> pointsToFollow;
      glm::vec2 currentTarget;
      int pointsToFollowIndex = 0;
      double fillCounter = 0.0;
      double canDamagePlayerCounter = 0.0;

      BladedSpaceBugState state = BladedSpaceBugState::Patroling;

      double bladedSpaceBugAnimIndex = 0.0;
      const char *bladedSpaceBugSpriteSheet[4] = {"./assets/sprites/BladedSpaceBug_2.png", "./assets/sprites/BladedSpaceBug_1.png", "./assets/sprites/BladedSpaceBug_3.png", "./assets/sprites/BladedSpaceBug_1.png"};

      double bladedSpaceBugDeathAnimIndex = 0.0;
      const char *bladedSpaceBugDeathSpriteSheet[6] = {"./assets/sprites/BladedSpaceBug_death_1.png", "./assets/sprites/BladedSpaceBug_death_2.png", "./assets/sprites/BladedSpaceBug_death_3.png", "./assets/sprites/BladedSpaceBug_death_4.png", "./assets/sprites/BladedSpaceBug_death_5.png", "./assets/sprites/BladedSpaceBug_death_6.png"};

public:
      BladedSpaceBug(glm::vec2 initPos, glm::vec2 initVelocity);
      ~BladedSpaceBug();
      void UpdateSpaceBug(double deltaTime, Player *player = nullptr) override;
      void RenderSpaceBug(SDL_Renderer *gameRenderer) override;

      void Attack(Player *player);
      void SetNewDirection();
      void FillPointsToFollow(double deltaTime, Player *player);
};

#endif
