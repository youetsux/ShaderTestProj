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
	//���_��������z��
	VERTEX* vertices = new VERTEX[vertexCount_];

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
			vertices[index].position = XMVectorSet((float)(-pos[0]), (float)pos[1], (float)pos[2], 0.0f);

			//���_��UV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			vertices[index].uv = XMVectorSet((float)(uv.mData[0]), (float)(1.0 - uv.mData[1]), 0.0f, 0.0f);

			//���_�̖@��
			FbxVector4 Normal;
			mesh->GetPolygonVertexNormal(poly, vertex, Normal);	//���Ԗڂ̃|���S���́A���Ԗڂ̒��_�̖@�����Q�b�g
			vertices[index].normal = XMVectorSet((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
		}

}

void FbxData::LoadIndex(fbxsdk::FbxMesh* mesh)
{
}

void FbxData::LoadMaterial(fbxsdk::FbxNode* pNode)
{
}


void FbxData::Release()
{
}
