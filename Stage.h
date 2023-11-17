#pragma once
#include "Engine/GameObject.h"
#include "Engine/Quad.h"

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_;    //���f���ԍ�
    Quad* q;
public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};