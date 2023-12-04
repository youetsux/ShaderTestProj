#include "FbxData.h"
#include <filesystem>

using namespace std::filesystem;

FbxData::FbxData()
	:vertexCount_(0), polygonCount_(0), materialCount_(0)
{
}

HRESULT FbxData::Load(std::string fileName)
{
	

    return E_NOTIMPL;
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
