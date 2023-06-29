
#include "Pickup.h"

Pickup::Pickup(glm::vec2 initPos, glm::vec2 initSpeed, int seed) : pos{initPos}, speed{initSpeed}
{
      std::cout << "Pickup Constructor" << std::endl;

      srand(seed);
      int typeIndex = rand() % 5;
      switch (typeIndex)
      {
      case 1:
            type = PickupType::ExtraLifePickup;
            imgPath = "./assets/sprites/pickups/extra_life.png";
            break;
      case 2:
            type = PickupType::HealthPickup;
            imgPath = "./assets/sprites/pickups/extra_life.png";
            break;
      case 3:
            type = PickupType::RocketPickup;
            imgPath = "./assets/sprites/pickups/extra_rocket.png";
            break;
      case 4:
            type = PickupType::SpeedBoostPickup;
            imgPath = "./assets/sprites/pickups/speed_boost.png";
            break;

      default:
            break;
      }

      speed.x *= 200.0;
      speed.y *= 200.0;
}

Pickup::~Pickup()
{
      std::cout << "Pickup Destructor" << std::endl;
}

void Pickup::Update(double deltaTime)
{
      pos.x += speed.x * deltaTime;
      pos.y += speed.y * deltaTime;
}

void Pickup::Render(SDL_Renderer *gameRenderer)
{
      SDL_Surface *pickupSurface = IMG_Load(imgPath);
      SDL_Texture *pickupTexture = SDL_CreateTextureFromSurface(gameRenderer, pickupSurface);
      SDL_FreeSurface(pickupSurface);
      rect = {static_cast<int>(pos.x), static_cast<int>(pos.y), 64, 64};
      SDL_RenderCopy(gameRenderer, pickupTexture, NULL, &rect);
      SDL_DestroyTexture(pickupTexture);
}

void Pickup::DestroyPickup()
{
      delete this;
}

bool Pickup::CheckCollisionWithPlayer(SDL_Rect playerRect, Player *mainPlayer)
{
      if (SDL_HasIntersection(&rect, &playerRect))
      {
            if (type == PickupType::HealthPickup)
            {
                  mainPlayer->HealPlayer();
            }
            else if (type == PickupType::ExtraLifePickup)
            {
                  mainPlayer->GainExtraLife();
            }
            else if (type == PickupType::RocketPickup)
            {
                  mainPlayer->GainRokcet();
            }
            else if (type == PickupType::SpeedBoostPickup)
            {
                  mainPlayer->ActivateSpeedBoost();
            }

            return true;
      }
      return false;
}