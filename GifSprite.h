#pragma once
#include "Engine\\Direct3D.h"
#include "GifTexture.h"
#include <vector>
#include <string>
#include "Engine\\Transform.h"

using std::string;

#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] p; p = nullptr;}


namespace
{
	const int MAX_F_COUNT{ 10 };
}

class GifSprite
{
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;		//���[���h�s��
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;	//�ʒu
		XMVECTOR uv;		//UV
	};

protected:
	uint64_t vertexNum_;		//���_��
	std::vector<VERTEX> vertices_;		//���_���
	ID3D11Buffer* pVertexBuffer_;		//���_�o�b�t�@

	uint64_t indexNum;			//�C���f�b�N�X��
	std::vector<int> index_;			//�C���f�b�N�X���
	ID3D11Buffer* pIndexBuffer_;		//�C���f�b�N�X�o�b�t�@

	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	GifTexture* pTexture_;		//�e�N�X�`��
	string spriteFileName_;

public:
	GifSprite(string _fileName);
	~GifSprite();
	
	//�������i�|���S����\�����邽�߂̊e����������j
	//�ߒl�F�����^���s
	HRESULT Initialize();

	//�`��
	//�����Ftransform	�g�����X�t�H�[���N���X�I�u�W�F�N�g
	void Draw(Transform& transform);

	//���
	void Release();

private:
	//---------Initialize����Ă΂��֐�---------
	virtual void InitVertexData();		//���_���̏���
	HRESULT CreateVertexBuffer();		//���_�o�b�t�@���쐬

	virtual void InitIndexData();		//�C���f�b�N�X��������
	HRESULT CreateIndexBuffer();		//�C���f�b�N�X�o�b�t�@���쐬

	HRESULT CreateConstantBuffer();		//�R���X�^���g�o�b�t�@�쐬

	HRESULT LoadTexture(string _fileName);	//�e�N�X�`�������[�h


	//---------Draw�֐�����Ă΂��֐�---------
	void PassDataToCB(XMMATRIX worldMatrix);	//�R���X�^���g�o�b�t�@�Ɋe�����n��
	void SetBufferToPipeline();							//�e�o�b�t�@���p�C�v���C���ɃZ�b�g
public:
	int imageCount_;
	int crrImageNum_;
	int fCounter_;
	void UpdateCounter();
	bool GetCounter();
	void ResetCounter();

};

