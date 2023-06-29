
#include "Pickup.h"

Pickup::Pickup(PickupType pickupType, glm::vec2 initPos, glm::vec2 initSpeed, int seed) : type{pickupType}, pos{initPos}, speed{initSpeed}
{
      std::cout << "Pickup Constructor" << std::endl;

      srand(seed);
      int typeIndex = rand() % 5;
      switch (typeIndex)
      {
      case 1:
            pickupType = PickupType::ExtraLifePickup;
            imgPath = "./assets/sprites/extra_life.png";
            break;
      case 2:
            pickupType = PickupType::HealthPickup;
            imgPath = "./assets/sprites/extra_life.png";
            break;
      case 3:
            pickupType = PickupType::RocketPickup;
            imgPath = "./assets/sprites/extra_life.png";
            break;
      case 4:
            pickupType = PickupType::SpeedBoostPickup;
            imgPath = "./assets/sprites/extra_life.png";
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