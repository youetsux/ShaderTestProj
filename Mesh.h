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

//�}�e���A��
struct MATERIAL
{
	TEXTURE_INFO textureInfo;
	XMFLOAT4 diffuse_;
	int indexCount_;
	bool isTextured;
};

struct VERTEX
{
	XMFLOAT4 position;//�ʒu
	XMFLOAT2 uv; //�e�N�X�`�����W
	XMFLOAT4 normal; //�@���x�N�g��
	//XMFLOAT3 Tangent; // �ڋ��
	//XMFLOAT4 Color; // ���_�F
};


class MESH
{
public:
	std::vector<VERTEX> Vertices; // ���_�f�[�^�̔z��
	std::vector<tuple<int, int, int>> Indices; // �C���f�b�N�X�̔z��
	std::filesystem::path path; // �e�N�X�`���̃t�@�C���p�X
};

