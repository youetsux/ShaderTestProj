#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //q = new Quad();
    //q->Initialize();
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("assets/Ball.fbx");
    assert(hModel_ >= 0);
    Camera::SetPosition(XMVECTOR{ 0, 0, -5, 0 });
    Camera::SetTarget(XMVECTOR{ 0, 0, 0, 0 });
}

//�X�V
void Stage::Update()
{
   //transform_.rotate_.y += 0.5f;
}

//�`��
void Stage::Draw()
{
    //q->Draw(transform_);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Stage::Release()
{
}