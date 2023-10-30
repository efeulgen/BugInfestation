
#include "SeekAndDestroyDrone.h"

SeekAndDestroyDrone::SeekAndDestroyDrone(glm::vec2 pos, glm::vec2 dir, Player *player) : Drone(pos, dir)
{
      Logger::Log("SeekAndDestroyDrone Constructor");

      imgPath = "./assets/sprites/TrippleLaserDrone.png"; // for debugging change later
      droneRectSize = 64;
      droneType = DroneType::DT_SeekAndDestroyDrone;
      refToPlayer = player;
      droneSpeed = 150.0;
      UpdatePositionsToFollow();
}

SeekAndDestroyDrone::~SeekAndDestroyDrone()
{
      Logger::Log("SeekAndDestroyDrone Destructor");
}

void SeekAndDestroyDrone::UpdateDrone(double deltaTime)
{
      updatepositionsToFollowCounter += deltaTime;
      if (updatepositionsToFollowCounter >= UPDATE_POSITIONS_TO_FOLLOW_RATE)
      {
            UpdatePositionsToFollow();
      }

      if (isDead)
      {
            majorExplosionAnimCounter += deltaTime * 8.0;
            if (donePlayingMajorExplosion)
            {
                  isDestructible = true;
            }
      }

      Drone::UpdateDrone(deltaTime);
}

void SeekAndDestroyDrone::RenderDrone(SDL_Renderer *renderer)
{
      if (isDead)
      {
            if (!donePlayingMajorExplosion)
            {
                  SDL_Surface *surf = IMG_Load(majorExplosionSpriteSheet[static_cast<int>(majorExplosionAnimCounter)]);
                  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
                  SDL_FreeSurface(surf);
                  SDL_Rect rect = {static_cast<int>(position.x), static_cast<int>(position.y), droneRectSize * 2, droneRectSize * 2};
                  SDL_RenderCopy(renderer, tex, NULL, &rect);
                  SDL_DestroyTexture(tex);

                  if (static_cast<int>(majorExplosionAnimCounter) >= 3)
                  {
                        donePlayingMajorExplosion = true;
                  }
            }

            return;
      }

      Drone::RenderDrone(renderer);
}

void SeekAndDestroyDrone::UpdatePositionsToFollow()
{
      positionToFollow = refToPlayer->GetPlayerPos();
      direction = glm::normalize(positionToFollow - position);
}
