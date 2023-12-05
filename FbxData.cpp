#include "FbxData.h"
#include <filesystem>

using namespace std::filesystem;

FbxData::FbxData()
	:vertexCount_(0), polygonCount_(0), materialCount_(0)
{
}

HRESULT FbxData::Load(std::string fileName)
{
	
	//マネージャを生成
	FbxManager* pFbxManager = FbxManager::Create();

	//インポーターを生成
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//シーンオブジェクトにFBXファイルの情報を流し込む
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();

	//メッシュ情報を取得
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//各情報の個数を取得
	vertexCount_ = mesh->GetControlPointsCount();	//頂点の数
	polygonCount_ = mesh->GetPolygonCount();	//ポリゴンの数
	materialCount_ = pNode->GetMaterialCount();

	//現在のカレントディレクトリを取得
	std::filesystem::path crrPath = std::filesystem::current_path();
	////引数のfileNameからディレクトリ部分を取得
	std::filesystem::path absPath = std::filesystem::absolute(fileName);
	//カレントディレクトリ変更
	std::filesystem::current_path(absPath.remove_filename());

	//InitVertex(mesh);		//頂点バッファ準備
	//InitIndex(mesh);		//インデックスバッファ準備
	//IntConstantBuffer();	//コンスタントバッファ準備
	//InitMaterial(pNode);

	////カレントディレクトリを元に戻す
	std::filesystem::current_path(crrPath);


	////マネージャ解放
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
