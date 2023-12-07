#include "FbxData.h"
#include <filesystem>

using namespace std::filesystem;

FbxData::FbxData()
	:vertexCount_(0), polygonCount_(0), materialCount_(0)
{
}

HRESULT FbxData::Load(std::string fileName)
{
	
	//�}�l�[�W���𐶐�
	FbxManager* pFbxManager = FbxManager::Create();

	//�C���|�[�^�[�𐶐�
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//�V�[���I�u�W�F�N�g��FBX�t�@�C���̏��𗬂�����
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();

	//�O�p�|���S����
	FbxGeometryConverter geometryConverter(pFbxManager);
	geometryConverter.Triangulate(pFbxScene, true);

	//���b�V�������擾
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//�e���̌����擾
	vertexCount_ = mesh->GetControlPointsCount();	//���_�̐�
	polygonCount_ = mesh->GetPolygonCount();	//�|���S���̐�
	materialCount_ = pNode->GetMaterialCount();

	//���݂̃J�����g�f�B���N�g�����擾
	std::filesystem::path crrPath = std::filesystem::current_path();
	////������fileName����f�B���N�g���������擾
	std::filesystem::path absPath = std::filesystem::absolute(fileName);
	//�J�����g�f�B���N�g���ύX
	std::filesystem::current_path(absPath.remove_filename());

	LoadVertex(mesh);		//���_�o�b�t�@����
	//InitIndex(mesh);		//�C���f�b�N�X�o�b�t�@����
	//IntConstantBuffer();	//�R���X�^���g�o�b�t�@����
	//InitMaterial(pNode);

	////�J�����g�f�B���N�g�������ɖ߂�
	std::filesystem::current_path(crrPath);


	////�}�l�[�W�����
	pFbxManager->Destroy();
	return S_OK;
}


void FbxData::LoadVertex(fbxsdk::FbxMesh* mesh)
{

	//vector<MATERIAL*> MaterialList_;
	//vector<MESH*> mesh_;
	//���_��������z��
	//ERTEX* vertices = new VERTEX[vertexCount_];
	MESH* tMesh = new MESH;
	tMesh->Vertices.resize(vertexCount_);

	//�S�|���S��
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3���_��
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//���ׂ钸�_�̔ԍ�
			int index = mesh->GetPolygonVertex(poly, vertex);

			//���_�̈ʒu
			FbxVector4 pos = mesh->GetControlPointAt(index);
			tMesh->Vertices[index].position = XMFLOAT4((float)(-pos[0]), (float)pos[1], (float)pos[2], 0.0f);

			//���_��UV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			tMesh->Vertices[index].uv = XMFLOAT2((float)(uv.mData[0]), (float)(1.0 - uv.mData[1]));

			//���_�̖@��
			FbxVector4 Normal;
			mesh->GetPolygonVertexNormal(poly, vertex, Normal);	//���Ԗڂ̃|���S���́A���Ԗڂ̒��_�̖@�����Q�b�g
			tMesh->Vertices[index].normal = XMFLOAT4((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
		}
	}
	mesh_.push_back(tMesh);
}

void FbxData::LoadIndex(fbxsdk::FbxMesh* mesh)
{
	//mesh_. = vector<int>(materialCount_);
	//indexCount_  = new int[materialCount_
	
	//vector<int> index(polygonCount_ * 3);//�|���S����*3���S���_���p��
	////int* index = new int[polygonCount_ * 3];

	//for (int i = 0; i < materialCount_; i++)
	//{
	//	int count = 0;
	//	//�S�|���S��
	//	for (DWORD poly = 0; poly < polygonCount_; poly++)
	//	{
	//		//����}�e���A�����������|���S���̃��X�g���Ƃ��Ă��āA���_�����X�g�A�b�v
	//		FbxLayerElementMaterial* mtl = mesh->GetLayer(0)->GetMaterials();
	//		int mtlId = mtl->GetIndexArray().GetAt(poly);

	//		if (mtlId == i)
	//		{
	//			//3���_��
	//			for (DWORD vertex = 0; vertex < 3; vertex++)
	//			{
	//				index[count] = mesh->GetPolygonVertex(poly, vertex);
	//				count++;
	//			}
	//		}
	//	}
	//	indexCount_[i] = count;

	//	D3D11_BUFFER_DESC   bd;
	//	bd.Usage = D3D11_USAGE_DEFAULT;
	//	bd.ByteWidth = sizeof(int) * polygonCount_ * 3;
	//	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//	bd.CPUAccessFlags = 0;
	//	bd.MiscFlags = 0;

	//	D3D11_SUBRESOURCE_DATA InitData;
	//	InitData.pSysMem = index.data();
	//	InitData.SysMemPitch = 0;
	//	InitData.SysMemSlicePitch = 0;

	//	HRESULT hr;
	//	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_[i]);
	//	if (FAILED(hr))
	//	{
	//		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
	//	}
	//}
}

void FbxData::LoadMaterial(fbxsdk::FbxNode* pNode)
{
}


void FbxData::Release()
{
}
