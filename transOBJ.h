#pragma once
#include "Engine/GameObject.h"


class transOBJ :
    public GameObject
{
    int hModel_;
public:
    //�R���X�g���N�^
    transOBJ(GameObject* parent);

    //�f�X�g���N�^
    ~transOBJ();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

