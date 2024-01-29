#include "Sprite.h"

#include "Sprite.h"
#include "Camera.h"


//�R���X�g���N�^
Sprite::Sprite() :
	vertexNum_(0), pVertexBuffer_(nullptr),
	indexNum(0), pIndexBuffer_(nullptr),
	pConstantBuffer_(nullptr),
	pTexture_(nullptr)
{
}

//�f�X�g���N�^
Sprite::~Sprite()
{
	Release();
}

//������
HRESULT Sprite::Initialize()
{
	//���_���
	InitVertexData();					//�f�[�^��p�ӂ���

	//�C���f�b�N�X���
	InitIndexData();					//�f�[�^��p�ӂ���


	//�R���X�^���g�o�b�t�@�쐬
	if (FAILED(CreateConstantBuffer()))
	{
		return E_FAIL;
	}

	////�e�N�X�`���̃��[�h
	//if (FAILED(LoadTexture()))
	//{
	//	return E_FAIL;
	//}

	return S_OK;
}


//�`��
void Sprite::Draw(Transform& transform)
{
	Direct3D::SetShader(SHADER_2D);


	transform.Calclation();//�g�����X�t�H�[�����v�Z

	//�R���X�^���g�o�b�t�@�ɏ���n��
	PassDataToCB(transform.GetWorldMatrix());

	//���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�R���X�^���g�o�b�t�@���p�C�v���C���ɃZ�b�g
	SetBufferToPipeline();

	//�`��
	Direct3D::pContext_->DrawIndexed((UINT)indexNum, (UINT)0, 0);
}

void Sprite::Draw(Transform& transform, RECT rect, float alpha)
{
	//���낢��ݒ�
	Direct3D::SetShader(SHADER_TYPE::SHADER_2D);
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::SetDepthBafferWriteEnable(false);
	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	// �p�����[�^�̎󂯓n��
	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;


	//�\������T�C�Y�ɍ��킹��
	XMMATRIX cut = XMMatrixScaling((float)rect.right, (float)rect.bottom, 1);

	//��ʂɍ��킹��
	XMMATRIX view = XMMatrixScaling(1.0f / Direct3D::screenSize.cx, 1.0f / Direct3D::screenSize.cy, 1.0f);

	//�ŏI�I�ȍs��
	XMMATRIX world = cut * transform.matScale_ * transform.matRotate_ * view * transform.matTranslate_;
	cb.world = XMMatrixTranspose(world);

	// �e�N�X�`�����W�ϊ��s���n��
	XMMATRIX mTexTrans = XMMatrixTranslation((float)rect.left / (float)pTexture_->GetTextureSize().x,
		(float)rect.top / (float)pTexture_->GetTextureSize().y, 0.0f);
	XMMATRIX mTexScale = XMMatrixScaling((float)rect.right / (float)pTexture_->GetTextureSize().x,
		(float)rect.bottom / (float)pTexture_->GetTextureSize().y, 1.0f);
	XMMATRIX mTexel = mTexScale * mTexTrans;
	cb.uvTrans = XMMatrixTranspose(mTexel);


	// �e�N�X�`�������F����n��
	cb.color = XMFLOAT4(1, 1, 1, alpha);

	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃��\�[�X�A�N�Z�X���ꎞ�~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		// ���\�[�X�֒l�𑗂�


	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	// GPU����̃��\�[�X�A�N�Z�X���ĊJ

	//�|���S�����b�V����`�悷��
	Direct3D::pContext_->DrawIndexed(6, 0, 0);

	Direct3D::SetShader(SHADER_TYPE::SHADER_3D);

	Direct3D::SetDepthBafferWriteEnable(true);
}

//���
void Sprite::Release()
{
	SAFE_DELETE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}


///////////////���������private�֐�///////////////

HRESULT Sprite::Load(std::string fileName)
{
	if (FAILED(LoadTexture(fileName)))
	{
		return E_FAIL;
	}
	//���_���
	InitVertexData();					//�f�[�^��p�ӂ���

	//�C���f�b�N�X���
	InitIndexData();					//�f�[�^��p�ӂ���

	//�R���X�^���g�o�b�t�@�쐬
	if (FAILED(CreateConstantBuffer()))
	{
		return E_FAIL;
	}
	return S_OK;
}

//���_���̏���
void Sprite::InitVertexData()
{
	// ���_���
	vertices_ =
	{
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },// �l�p�`�̒��_�i����j
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�E��j
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },// �l�p�`�̒��_�i�E���j
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�����j		
	};

	//���_�̐�
	vertexNum_ = vertices_.size();	//�S�f�[�^�̃T�C�Y�@���@1���_���̃T�C�Y�@���@���_��

	//���łɒ��_�o�b�t�@���
	HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = (unsigned int)(sizeof(VERTEX) * vertexNum_);
	bd_vertex.Usage = D3D11_USAGE_DYNAMIC;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_.data();
	Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
}


//�C���f�b�N�X��������
void Sprite::InitIndexData()
{
	index_ = { 0,2,3, 0,1,2 };

	//�C���f�b�N�X��
	indexNum = index_.size();

	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = (unsigned int)(sizeof(int) * indexNum);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index_.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HRESULT hr;
	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
	}
}


//�R���X�^���g�o�b�t�@�쐬
HRESULT Sprite::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DEFAULT;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	HRESULT hr;
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

//�e�N�X�`�������[�h
HRESULT Sprite::LoadTexture(std::string fileName)
{
	pTexture_ = new Texture;

	HRESULT hr;
	string fname = "Assets\\" + fileName;
	hr = pTexture_->Load(fname);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�e�N�X�`���̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

//�R���X�^���g�o�b�t�@�Ɋe�����n��
void Sprite::PassDataToCB(XMMATRIX worldMatrix)
{
	CONSTANT_BUFFER cb;
	cb.world = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�


	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ
}

//�e�o�b�t�@���p�C�v���C���ɃZ�b�g
void Sprite::SetBufferToPipeline()
{
	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p
}

