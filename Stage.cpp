#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //q = new Quad();
    //q->Initialize();
    //モデルデータのロード
    hModel_ = Model::Load("assets/Ball.fbx");
    assert(hModel_ >= 0);
    Camera::SetPosition(XMVECTOR{ 0, 0, -5, 0 });
    Camera::SetTarget(XMVECTOR{ 0, 0, 0, 0 });
}

//更新
void Stage::Update()
{
   //transform_.rotate_.y += 0.5f;
}

//描画
void Stage::Draw()
{
    //q->Draw(transform_);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Stage::Release()
{
}