#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
//#include "Stage.h"
#include "ImageScene.h"
#include "Engine/Camera.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{
	//Instantiate<Stage>(this);
	Instantiate<ImageScene>(this);
}

void TestScene::Update()
{

}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
