//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

Texture2D		g_toon_texture : register(t1);

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer gmodel:register(b0)
{
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matW;           // ���[���h�s��
	float4x4	matNormal;           // ���[���h�s��
	float4		diffuseColor;		//�}�e���A���̐F���g�U���ˌW��
	float4		ambientColor;		//����
	float4		specularColor;		//���ʔ��ˁ��n�C���C�g
	float		shininess;
	bool		isTextured;			//�e�N�X�`���[���\���Ă��邩�ǂ���

};

cbuffer gmodel:register(b1)
{
	float4		lightPosition;
	float4		eyePosition;
};



//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos  : SV_POSITION;	//�ʒu
	float2 uv	: TEXCOORD;		//UV���W
	float4 color	: COLOR;	//�F�i���邳�j
	float4 eyev		:POSITION;
	float4 normal	:NORMAL;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
float4 VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL):SV_POSITION
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	//VS_OUT outData = (VS_OUT)0;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	normal.w = 0;
	pos = pos + normal * 0.05;
	
	pos = mul(pos, matWVP);

	return pos;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	return float4(0,0,0,1);
	//return g_texture.Sample(g_sampler, inData.uv);
}
