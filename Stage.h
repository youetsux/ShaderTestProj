#pragma once
#include "Engine/GameObject.h"
#include "Engine/Quad.h"


struct CBUFF_STAGESCENE
{
    XMFLOAT4	lightPosition;
    XMFLOAT4	eyePos;
};

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_;    //モデル番号
    int hGround_;
    int hLightBall_;
    Transform trBall;
    Transform trGround;
    Transform trLightBall;
    ID3D11Buffer* pCBStageScene_;
    //Quad* q;
public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};