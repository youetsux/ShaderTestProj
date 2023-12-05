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

	//InitVertex(mesh);		//���_�o�b�t�@����
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
