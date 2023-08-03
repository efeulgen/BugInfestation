
#include "Player.h"

Player::Player() : health{MAX_HEALTH}, fireCounter{FIRE_RATE}, isDead{false}, gravityFactor{GRAVITY}, isUsingJetPack{false}, isFlipped{false}
{
    std::cout << "Player Constructor" << std::endl;

    playerPosition = glm::vec2(40.0, 40.0);
    playerSpeed = glm::vec2(300.0, 350.0);
    firePos = glm::vec2(105.0, 64.0);

    extraLives = 0;
    rocketAmount = 0;

    laserSound = Mix_LoadWAV("./audio/player_laser.wav");
    rocketSound = Mix_LoadWAV("./audio/rocketLauncher_sound.wav");
    if (laserSound == NULL || rocketSound == NULL)
    {
        Logger::Err("SFX isn't loaded.");
    }

    collisionRect = new SDL_Rect();
    weaponState = PlayerWeaponState::PWS_Normal;
    spriteToRender = normalWeaponStateSprtie;
}

Player::~Player()
{
    std::cout << "Player Destructor" << std::endl;

    delete collisionRect;
    collisionRect = nullptr;

    Mix_FreeChunk(laserSound);
    Mix_FreeChunk(rocketSound);
}

void Player::Update(double deltaTime)
{
    if (fireCounter < (FIRE_RATE - fireBoost))
    {
        fireCounter += deltaTime;
    }
    if (fireCounter > (FIRE_RATE - fireBoost))
    {
        fireCounter = (FIRE_RATE - fireBoost);
        canFire = true;
    }

    if (!projArray.empty())
    {
        UpdateProjectiles(deltaTime);
    }

    // *************** bound checking *********************************************
    if (playerPosition.y <= 0.0)
    {
        playerPosition.y = 0.0;
    }
    if (playerPosition.y >= 720.0)
    {
        playerPosition.y = 720.0;
    }
    if (playerPosition.x <= 0.0)
    {
        playerPosition.x = 0.0;
    }
    if (playerPosition.x >= 1152.0)
    {
        playerPosition.x = 1152.0;
    }

    // *************** apply gravity *********************************************
    if (!isUsingJetPack)
    {
        gravityFactor += (gravityIncrement * deltaTime);
        playerPosition.y += (gravityFactor * deltaTime);
    }

    // *************** boost *********************************************
    if (isSpeedBoostActive)
    {
        speedBoostDuration += deltaTime;
        if (speedBoostDuration >= 10.0)
        {
            DeactivateSpeedBoost();
            speedBoostDuration = 0.0;
        }
    }

    if (isFireRateBoostActive)
    {
        fireRateBoostDuration += deltaTime;
        if (fireRateBoostDuration >= 15.0)
        {
            DeactivateFireRateBoost();
            fireRateBoostDuration = 0.0;
        }
    }

    // update sprite sheet index
    if (isUsingJetPack)
    {
        jetPackSpriteSheetIndex += deltaTime * JETPACK_ANIM_SPEED;
    }
    if (isRenderingBloodSplash)
    {
        bloodSplashSpriteSheetIndex += deltaTime * 10.0;
    }
}

void Player::RenderPlayer(SDL_Renderer *gameRenderer)
{

    SDL_Surface *playerSurface = IMG_Load(spriteToRender);
    SDL_Texture *playertexture = SDL_CreateTextureFromSurface(gameRenderer, playerSurface);
    SDL_FreeSurface(playerSurface);
    playerRect = {static_cast<int>(playerPosition.x), static_cast<int>(playerPosition.y), 128, 128};

    if (isFlipped)
    {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(gameRenderer, playertexture, NULL, &playerRect, 0.0, NULL, flip);
    }
    else
    {
        SDL_RenderCopy(gameRenderer, playertexture, NULL, &playerRect);
    }
    SDL_DestroyTexture(playertexture);

    for (auto projectile : projArray) // render projectiles
    {
        projectile->RenderProjectile(gameRenderer);
    }

    if (isUsingJetPack) // render jet pack fire
    {
        RenderJetPackFire(gameRenderer);
    }

    if (isRenderingBloodSplash) // render blood splash
    {
        RenderBloodSplash(gameRenderer);
    }
}

void Player::MoveRight(double deltaTime)
{
    playerPosition.x += playerSpeed.x * deltaTime;
    SetIsFlipped(false);
}
void Player::MoveLeft(double deltaTime)
{
    playerPosition.x -= playerSpeed.x * deltaTime;
    SetIsFlipped(true);
}

void Player::Fire()
{
    Mix_PlayChannel(-1, laserSound, 0);
    double projSpeed = isFlipped ? -1000.0 : 1000.0;
    firePos = isFlipped ? glm::vec2(-40.0, 64.0) : glm::vec2(105.0, 64.0);
    Projectile *newProjectile = new Projectile(glm::vec2(1, 0), projSpeed, playerProjectileSpriteSheet);
    newProjectile->SetProjectilePosition(playerPosition + firePos);
    projArray.push_back(newProjectile);

    canFire = false;
    fireCounter = 0.0;
}

void Player::FireRocket()
{
    if (rocketAmount > 0)
    {
        Mix_PlayChannel(-1, rocketSound, 0);
        double projSpeed = isFlipped ? -700.0 : 700.0;
        firePos = isFlipped ? glm::vec2(-40.0, 64.0) : glm::vec2(105.0, 64.0);
        Projectile *newProjectile = new Projectile(glm::vec2(1, 0), projSpeed, playerRocketLauncgerSprtieSheet, 60, isFlipped, ProjectileType::PT_Heavy);
        newProjectile->SetProjectilePosition(playerPosition + firePos);
        projArray.push_back(newProjectile);

        rocketAmount--;
    }
}

void Player::UpdateProjectiles(double deltaTime)
{
    if (projArray.empty())
        return;
    for (auto projectile : projArray)
    {
        projectile->UpdateProjectile(deltaTime);
        if (std::abs(projectile->GetProjectilePosition().x - playerPosition.x) > 1400.0)
        {
            projArray.erase(std::remove(projArray.begin(), projArray.end(), projectile), projArray.end());
            projectile->Destroy();
            projectile = nullptr;
        }
    }
}

void Player::EraseElementFromProjarray(Projectile *proj)
{
    projArray.erase(std::remove(projArray.begin(), projArray.end(), proj), projArray.end());
}

void Player::ClearProjArray()
{
    for (auto proj : projArray)
    {
        proj->Destroy();
        proj = nullptr;
    }
    projArray.clear();
}

void Player::GetDamage(double amount)
{
    health -= amount;
    isRenderingBloodSplash = true;
    if (health <= 0.0)
    {
        if (extraLives > 0)
        {
            extraLives--;
            health = MAX_HEALTH;
        }
        else
        {
            isDead = true;
        }
    }
}

void Player::UseJetPack(double deltaTime)
{
    isUsingJetPack = true;
    gravityFactor = GRAVITY;
    playerPosition.y -= playerSpeed.y * deltaTime;
}

bool Player::CheckCollision(SDL_Rect other)
{
    if (SDL_HasIntersection(&playerRect, &other))
    {
        SDL_IntersectRect(&playerRect, &other, collisionRect);
        return true;
    }
    return false;
}

void Player::HealPlayer()
{
    health = health + 10.0 > 100.0 ? 100.0 : health + 10.0;
}

void Player::GainExtraLife()
{
    extraLives = extraLives + 1 > 5 ? 5 : extraLives + 1;
}

void Player::GainRokcet()
{
    rocketAmount++;
}

void Player::ActivateSpeedBoost()
{
    playerSpeed.x *= 2.0;
    isSpeedBoostActive = true;
}

void Player::DeactivateSpeedBoost()
{
    playerSpeed.x /= 2.0;
    isSpeedBoostActive = false;
}

void Player::ActivateFireRateBoost()
{
    fireBoost = 0.2;
    isFireRateBoostActive = true;
}

void Player::DeactivateFireRateBoost()
{
    fireBoost = 0.0;
    isFireRateBoostActive = false;
}

void Player::RenderJetPackFire(SDL_Renderer *renderer)
{
    if (static_cast<int>(jetPackSpriteSheetIndex) > 2)
    {
        jetPackSpriteSheetIndex = 0.0;
    }

    SDL_Surface *surf = IMG_Load(playerJetPackSpriteSheet[static_cast<int>(jetPackSpriteSheetIndex)]);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    SDL_Rect jetPackFireRect = {static_cast<int>(playerPosition.x), static_cast<int>(playerPosition.y), 128, 128};

    if (!isFlipped)
    {
        SDL_RenderCopy(renderer, tex, NULL, &jetPackFireRect);
    }
    else
    {
        SDL_RendererFlip jpFlip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer, tex, NULL, &jetPackFireRect, 0.0, NULL, jpFlip);
    }

    SDL_DestroyTexture(tex);
}

void Player::RenderBloodSplash(SDL_Renderer *renderer)
{
    SDL_Surface *surf = IMG_Load(playerBloodSplashSpriteSheet[static_cast<int>(bloodSplashSpriteSheetIndex)]);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    SDL_Rect bloodSplashRect = {static_cast<int>(collisionRect->x), static_cast<int>(collisionRect->y), 64, 64};
    SDL_RenderCopy(renderer, tex, NULL, &bloodSplashRect);
    SDL_DestroyTexture(tex);

    if (static_cast<int>(bloodSplashSpriteSheetIndex) >= 3)
    {
        isRenderingBloodSplash = false;
        bloodSplashSpriteSheetIndex = 0.0;
    }
}

void Player::ToggleWeaponState()
{
    if (weaponState == PlayerWeaponState::PWS_Normal)
    {
        weaponState = PlayerWeaponState::PWS_RocketLauncher;
        spriteToRender = rocketLauncherWeaponStateSprite;
    }
    else if (weaponState == PlayerWeaponState::PWS_RocketLauncher)
    {
        weaponState = PlayerWeaponState::PWS_Normal;
        spriteToRender = normalWeaponStateSprtie;
    }
}
