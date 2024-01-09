#pragma once
#include "Engine/GameObject.h"
#include "GifSprite.h"

class ImageScene :
    public GameObject
{
    GifSprite *sImage;
public:
    ImageScene(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

