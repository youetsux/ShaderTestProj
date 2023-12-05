#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <DirectXMath.h>
#include <map>
#pragma comment(lib,"assimp-vc143-mtd.lib")

using std::string;
using std::wstring;
using std::vector;
using std::tuple;
using namespace DirectX;


struct TEXTURE_INFO
{
	unsigned int id;
	string type;
	std::filesystem::path path;
};

//マテリアル
struct MATERIAL
{
	TEXTURE_INFO textureInfo;
	XMFLOAT4 diffuse_;
	int indexCount_;
	bool isTextured;
};

struct VERTEX
{
	XMFLOAT4 position;//位置
	XMFLOAT2 uv; //テクスチャ座標
	XMFLOAT4 normal; //法線ベクトル
	//XMFLOAT3 Tangent; // 接空間
	//XMFLOAT4 Color; // 頂点色
};


class MESH
{
public:
	std::vector<VERTEX> Vertices; // 頂点データの配列
	std::vector<tuple<int, int, int>> Indices; // インデックスの配列
	std::filesystem::path path; // テクスチャのファイルパス
};

