
#include "BladedSpaceBug.h"

BladedSpaceBug::BladedSpaceBug(glm::vec2 initPos, glm::vec2 initVelocity)
{
      std::cout << "BladedSpaceBug Constructor" << std::endl;

      spaceBugPos = initPos;
      health = 40;
      type = BugType::Bladed;

      normalSpeed = 100.0;
      attackSpeed = 800.0;
      attackDuration = 1.0;
      patrolDuration = 7.5; // TODO : randomize

      pointsToFollow.push_back(glm::vec2(640, 360));
      currentTarget = pointsToFollow[pointsToFollowIndex];

      spaceBugDirection = glm::normalize(currentTarget - spaceBugPos);
      spaceBugDirection.x *= normalSpeed;
      spaceBugDirection.y *= normalSpeed;
}

BladedSpaceBug::~BladedSpaceBug()
{
      std::cout << "BladedSpaceBug Destructor" << std::endl;
}

void BladedSpaceBug::UpdateSpaceBug(double deltaTime, Player *player)
{
      spaceBugPos.x += spaceBugDirection.x * deltaTime;
      spaceBugPos.y += spaceBugDirection.y * deltaTime;

      if (state == BladedSpaceBugState::Patroling)
      {
            FillPointsToFollow(deltaTime, player);

            if (glm::distance(currentTarget, spaceBugPos) < 1.0f)
            {
                  SetNewDirection();
            }
            patrolDuration -= deltaTime;
            if (patrolDuration <= 0.0)
            {
                  patrolDuration = 7.5;
                  Attack(player);
            }
      }
      else if (state == BladedSpaceBugState::Attacking)
      {
            attackDuration -= deltaTime;
            if (attackDuration <= 0.0)
            {
                  attackDuration = 3.5;
                  state = BladedSpaceBugState::Patroling;

                  pointsToFollow.push_back(glm::vec2(640, 360));
                  currentTarget = pointsToFollow[pointsToFollowIndex];

                  spaceBugDirection = glm::normalize(currentTarget - spaceBugPos);
                  spaceBugDirection.x *= normalSpeed;
                  spaceBugDirection.y *= normalSpeed;
            }
      }
}

void BladedSpaceBug::RenderSpaceBug(SDL_Renderer *gameRenderer)
{
      SDL_Surface *surf = IMG_Load("./assets/sprites/BladedSpaceBug.png");
      SDL_Texture *tex = SDL_CreateTextureFromSurface(gameRenderer, surf);
      SDL_FreeSurface(surf);
      spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 100, 100};
      SDL_RenderCopy(gameRenderer, tex, NULL, &spaceBugRect);
      SDL_DestroyTexture(tex);
}

// *******************************************************************************************************************************************************************************
// *************** methods *******************************************************************************************************************************************************

void BladedSpaceBug::Attack(Player *player)
{
      state = BladedSpaceBugState::Attacking;

      // reset points to follow
      pointsToFollow.clear();
      pointsToFollowIndex = 0;
      fillCounter = 0.0;

      // set attack direction
      spaceBugDirection = glm::normalize(player->GetPlayerPos() - spaceBugPos);
      spaceBugDirection.x *= attackSpeed;
      spaceBugDirection.y *= attackSpeed;
}

void BladedSpaceBug::SetNewDirection()
{
      pointsToFollowIndex++;
      currentTarget = pointsToFollow[pointsToFollowIndex];

      spaceBugDirection = glm::normalize(currentTarget - spaceBugPos);
      spaceBugDirection.x *= normalSpeed;
      spaceBugDirection.y *= normalSpeed;
}

void BladedSpaceBug::FillPointsToFollow(double deltaTime, Player *player)
{
      fillCounter += deltaTime;
      if (fillCounter >= 2.0)
      {
            pointsToFollow.push_back(player->GetPlayerPos());
            fillCounter = 0.0;
      }
}
