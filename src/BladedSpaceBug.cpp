
#include "BladedSpaceBug.h"

BladedSpaceBug::BladedSpaceBug(glm::vec2 initPos, glm::vec2 initVelocity)
{
      Logger::Log("BladedSpaceBug Constructor");

      spaceBugPos = initPos;
      health = 15;
      type = BugType::Bladed;

      normalSpeed = 200.0;
      attackSpeed = 1200.0;
      attackDuration = ATTACK_DURATION;
      patrolDuration = PATROL_DURATION;

      pointsToFollow.push_back(glm::vec2(640, 360)); // update these values
      currentTarget = pointsToFollow[pointsToFollowIndex];

      spaceBugDirection = glm::normalize(currentTarget - spaceBugPos);
      spaceBugDirection.x *= normalSpeed;
      spaceBugDirection.y *= normalSpeed;
}

BladedSpaceBug::~BladedSpaceBug()
{
      Logger::Log("BladedSpaceBug Destructor");
}

void BladedSpaceBug::UpdateSpaceBug(double deltaTime, Player *player)
{
      // animations
      if (isDead)
      {
            bladedSpaceBugDeathAnimIndex += deltaTime * 8;
            return;
      }
      bladedSpaceBugAnimIndex += deltaTime * 5;

      // update position
      spaceBugPos.x += spaceBugDirection.x * deltaTime;
      spaceBugPos.y += spaceBugDirection.y * deltaTime;

      if (!player)
      {
            return;
      }

      if (state == BladedSpaceBugState::Patroling)
      {
            FillPointsToFollow(deltaTime, player);

            if (glm::distance(currentTarget, spaceBugPos) < 10.0f)
            {
                  SetNewDirection();
            }
            patrolDuration -= deltaTime;
            if (patrolDuration <= 0.0)
            {
                  patrolDuration = PATROL_DURATION;
                  Attack(player);
            }
      }
      else if (state == BladedSpaceBugState::Attacking)
      {
            attackDuration -= deltaTime;
            if (attackDuration <= 0.0)
            {
                  attackDuration = ATTACK_DURATION;
                  state = BladedSpaceBugState::Patroling;

                  pointsToFollow.push_back(player->GetPlayerPos());
                  currentTarget = pointsToFollow[pointsToFollowIndex];

                  spaceBugDirection = glm::normalize(currentTarget - spaceBugPos);
                  spaceBugDirection.x *= normalSpeed;
                  spaceBugDirection.y *= normalSpeed;
            }
      }

      if (!canDamagePlayer)
      {
            canDamagePlayerCounter += deltaTime;
            if (canDamagePlayerCounter >= 2.0)
            {
                  canDamagePlayer = true;
                  canDamagePlayerCounter = 0.0;
            }
      }

      // flip
      isFlipped = spaceBugDirection.x > 0 ? true : false;

      // bound checking
      if (spaceBugPos.x < -100.0 || spaceBugPos.x > 1400.0 || spaceBugPos.y < -100.0 || spaceBugPos.y > 900.0)
      {
            pointsToFollow.clear();
            pointsToFollowIndex = 0;
            fillCounter = 0.0;

            attackDuration = ATTACK_DURATION;
            state = BladedSpaceBugState::Patroling;

            pointsToFollow.push_back(player->GetPlayerPos());
            currentTarget = pointsToFollow[pointsToFollowIndex];

            spaceBugDirection = glm::normalize(currentTarget - spaceBugPos);
            spaceBugDirection.x *= normalSpeed;
            spaceBugDirection.y *= normalSpeed;
      }
}

void BladedSpaceBug::RenderSpaceBug(SDL_Renderer *gameRenderer)
{
      // render bladedSpaceBugDeathSpriteSheet
      if (isDead)
      {
            if (!donePlayingExplodeAnim)
            {
                  SDL_Surface *surf = IMG_Load(bladedSpaceBugDeathSpriteSheet[static_cast<int>(bladedSpaceBugDeathAnimIndex)]);
                  SDL_Texture *tex = SDL_CreateTextureFromSurface(gameRenderer, surf);
                  SDL_FreeSurface(surf);
                  spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 120, 120};
                  SDL_RenderCopy(gameRenderer, tex, NULL, &spaceBugRect);
                  SDL_DestroyTexture(tex);

                  if (static_cast<int>(bladedSpaceBugDeathAnimIndex) >= 5)
                  {
                        donePlayingExplodeAnim = true;
                        isDestructible = true;
                  }
            }
            return;
      }

      // render bladedSpaceBugSpriteSheet
      if (static_cast<int>(bladedSpaceBugAnimIndex) > 3)
      {
            bladedSpaceBugAnimIndex = 0.0;
      }
      SDL_Surface *surf = IMG_Load(bladedSpaceBugSpriteSheet[static_cast<int>(bladedSpaceBugAnimIndex)]);
      SDL_Texture *tex = SDL_CreateTextureFromSurface(gameRenderer, surf);
      SDL_FreeSurface(surf);
      spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 120, 120};
      if (isFlipped)
      {
            SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
            SDL_RenderCopyEx(gameRenderer, tex, NULL, &spaceBugRect, 0.0, NULL, flip);
      }
      else
      {
            SDL_RenderCopy(gameRenderer, tex, NULL, &spaceBugRect);
      }
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
