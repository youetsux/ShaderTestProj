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

	//三角ポリゴン化
	FbxGeometryConverter geometryConverter(pFbxManager);
	geometryConverter.Triangulate(pFbxScene, true);

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

	LoadVertex(mesh);		//頂点バッファ準備
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

	//vector<MATERIAL*> MaterialList_;
	//vector<MESH*> mesh_;
	//頂点情報を入れる配列
	//ERTEX* vertices = new VERTEX[vertexCount_];
	MESH* tMesh = new MESH;
	tMesh->Vertices.resize(vertexCount_);

	//全ポリゴン
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3頂点分
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//調べる頂点の番号
			int index = mesh->GetPolygonVertex(poly, vertex);

			//頂点の位置
			FbxVector4 pos = mesh->GetControlPointAt(index);
			tMesh->Vertices[index].position = XMFLOAT4((float)(-pos[0]), (float)pos[1], (float)pos[2], 0.0f);

			//頂点のUV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			tMesh->Vertices[index].uv = XMFLOAT2((float)(uv.mData[0]), (float)(1.0 - uv.mData[1]));

			//頂点の法線
			FbxVector4 Normal;
			mesh->GetPolygonVertexNormal(poly, vertex, Normal);	//ｉ番目のポリゴンの、ｊ番目の頂点の法線をゲット
			tMesh->Vertices[index].normal = XMFLOAT4((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
		}
	}
	mesh_.push_back(tMesh);
}

void FbxData::LoadIndex(fbxsdk::FbxMesh* mesh)
{
	//mesh_. = vector<int>(materialCount_);
	//indexCount_  = new int[materialCount_
	
	//vector<int> index(polygonCount_ * 3);//ポリゴン数*3＝全頂点分用意
	////int* index = new int[polygonCount_ * 3];

	//for (int i = 0; i < materialCount_; i++)
	//{
	//	int count = 0;
	//	//全ポリゴン
	//	for (DWORD poly = 0; poly < polygonCount_; poly++)
	//	{
	//		//あるマテリアルを持ったポリゴンのリストをとってきて、頂点をリストアップ
	//		FbxLayerElementMaterial* mtl = mesh->GetLayer(0)->GetMaterials();
	//		int mtlId = mtl->GetIndexArray().GetAt(poly);

	//		if (mtlId == i)
	//		{
	//			//3頂点分
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
	//		MessageBox(NULL, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);
	//	}
	//}
}

void FbxData::LoadMaterial(fbxsdk::FbxNode* pNode)
{
}


void FbxData::Release()
{
}
