#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Engine/Transform.h"
#include <vector>
#include <filesystem>
#include "Mesh.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

using std::vector;
//class Texture;

class FbxData
{
	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	vector<MATERIAL *> MaterialList_;
	vector<MESH *> mesh_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitMaterial(fbxsdk::FbxNode* pNode);
public:

	FbxData();
	HRESULT Load(std::string fileName);
	void    Release();
};

