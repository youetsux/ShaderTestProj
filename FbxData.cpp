#include "FbxData.h"


FbxData::FbxData()
	:vertexCount_(0), polygonCount_(0), materialCount_(0)
{
}

HRESULT FbxData::Load(std::string fileName)
{
    return E_NOTIMPL;
}


void FbxData::InitVertex(fbxsdk::FbxMesh* mesh)
{
}

void FbxData::InitIndex(fbxsdk::FbxMesh* mesh)
{
}

void FbxData::InitMaterial(fbxsdk::FbxNode* pNode)
{
}


void FbxData::Release()
{
}
