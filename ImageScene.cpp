#include "ImageScene.h"

ImageScene::ImageScene(GameObject* parent)
	:GameObject(parent, "ImageScene")
{
}

void ImageScene::Initialize()
{
	sImage = new GifSprite("Assets\\ani.gif");
	sImage->Initialize();
}

void ImageScene::Update()
{
}

void ImageScene::Draw()
{
	sImage->Draw(transform_);
}

void ImageScene::Release()
{
}