
#include "SpaceBug.h"

SpaceBug::SpaceBug()
{
    std::cout << "SpaceBug Constructor" << std::endl;
}

SpaceBug::SpaceBug(glm::vec2 initPos, glm::vec2 initDirection) : spaceBugPos{initPos}, spaceBugDirection{initDirection}, spaceBugRect{0, 0, 0, 0}
{
    health = 1;
    type = BugType::Regular;
}

SpaceBug::~SpaceBug()
{
    std::cout << "SpaceBug Destructor" << std::endl;
}

void SpaceBug::UpdateSpaceBug(double deltaTime, Player *player)
{
    spaceBugPos.x += spaceBugDirection.x * deltaTime;
    spaceBugPos.y += spaceBugDirection.y * deltaTime;
    if (spaceBugPos.x <= 0 || spaceBugPos.x >= (1280 - 64))
    {
        spaceBugDirection.x *= -1;
        isFlipped = !isFlipped;
    }
    if (spaceBugPos.y <= 0 || spaceBugPos.y >= (720 - 64))
    {
        spaceBugDirection.y *= -1;
    }

    // update anim index
    spriteSheetIndex += deltaTime * ANIM_SPEED;
}

void SpaceBug::RenderSpaceBug(SDL_Renderer *gameRenderer)
{
    if (static_cast<int>(spriteSheetIndex) > 3)
    {
        spriteSheetIndex = 0.0;
    }

    spaceBugSurface = IMG_Load(bugSpriteSheet[static_cast<int>(spriteSheetIndex)]);
    SDL_Texture *spaceBugTexture = SDL_CreateTextureFromSurface(gameRenderer, spaceBugSurface);
    SDL_FreeSurface(spaceBugSurface);
    spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 64, 64};

    if (isFlipped)
    {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(gameRenderer, spaceBugTexture, NULL, &spaceBugRect, 0.0, NULL, flip);
    }
    else
    {
        SDL_RenderCopy(gameRenderer, spaceBugTexture, NULL, &spaceBugRect);
    }
    SDL_DestroyTexture(spaceBugTexture);
}

void SpaceBug::GetDamage()
{
    health--;
    if (health <= 0)
    {
        isDestructible = true;
        canDamagePlayer = false;
    }
}

bool SpaceBug::CheckCollision(SDL_Rect other) const
{
    if (SDL_HasIntersection(&spaceBugRect, &other) && canDamagePlayer)
    {
        return true;
    }
    return false;
}

void SpaceBug::Destroy()
{
    delete this;
}

void SpaceBug::EraseElementFromProjarray(Projectile *proj)
{
    projArray.erase(std::remove(projArray.begin(), projArray.end(), proj), projArray.end());
}
