#include "axisClass.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"

axisClass::axisClass(GameObject* parent)
	:GameObject(parent, "AXIS"), hModel_(-1)
{

}

axisClass::~axisClass()
{
}

void axisClass::Initialize()
{
    hModel_ = Model::Load("Assets/Arrow.fbx");
    assert(hModel_ >= 0);//���f���ԍ���-1�̂܂܂������炠���[�ƂɈ���������

    //transform_.scale_.x = 0.1f;
    //transform_.scale_.y = 0.1f;
    //transform_.scale_.z = 0.1f;
    //transform_.position_.x = 2.0f;
    //transform_.position_.y = 1.0f;
}

void axisClass::Update()
{
}

void axisClass::Draw()
{
    Transform xt, yt, zt;
    xt.rotate_.y = 0;
    xt.scale_ = { 0.5,0.5,0.5 };
    yt.rotate_.z = 90;
    yt.scale_ = { 0.5,0.5,0.5 };
    zt.rotate_.y = -90;
    zt.scale_ = { 0.5,0.5,0.5 };
    Model::SetTransform(hModel_, xt);
    Model::Draw(hModel_);
    Model::SetTransform(hModel_, yt);
    Model::Draw(hModel_);
    Model::SetTransform(hModel_, zt);
    Model::Draw(hModel_);
}

void axisClass::Release()
{
}
