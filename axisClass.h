#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"


class axisClass :
    public GameObject
{
    Fbx* pFbx;
    int hModel_;//���f���ԍ�
public:
    //�R���X�g���N�^
    axisClass(GameObject* parent);

    //�f�X�g���N�^
    ~axisClass();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

