#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1),hGround_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{

    //モデルデータのロード
    hModel_ = Model::Load("assets/Ball.fbx");
    hGround_ = Model::Load("assets/Ground.fbx");
    
    assert(hModel_ >= 0);
    assert(hGround_ >= 0);
    Camera::SetPosition(XMVECTOR{ 3, 5, -8, 0 });
    Camera::SetTarget(XMVECTOR{ 0, 0, 0, 0 });
    trBall.position_ = {2, 2, 0};
    trBall.rotate_ = { 0, 0, 0 };
    trBall.scale_ = {  1,1,1 };
    trGround.position_ = { 0, 0, 0 };
    trGround.rotate_ = { 0, 0, 0 };
    trGround.scale_ = { 10, 10, 10 };
}

//更新
void Stage::Update()
{
   //transform_.rotate_.y += 0.5f;
    trBall.rotate_.y += 0.5f;
}

//描画
void Stage::Draw()
{
    //q->Draw(transform_);
    Model::SetTransform(hModel_, trBall);
    Model::Draw(hModel_);
    Model::SetTransform(hGround_, trGround);
    Model::Draw(hGround_);
}

//開放
void Stage::Release()
{
}