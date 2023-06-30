
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

      BladedSpaceBugState state = BladedSpaceBugState::Patroling;

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
