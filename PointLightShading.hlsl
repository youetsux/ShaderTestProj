//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global:register(b0)
{
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matW;           // ���[���h�s��
	float4x4	matNormal;           // ���[���h�s��
	float4		diffuseColor;		//�}�e���A���̐F���g�U���ˌW��
	float4		lightPosition;
	float4		eyePosition;
	int4		isTextured;			//�e�N�X�`���[���\���Ă��邩�ǂ���
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_IN
{
	float3 pos  : POSITION;	//�ʒu
	float2 uv	: TEXCOORD;		//UV���W
	float3 normal	:NORMAL;
	//float4 color	: COLOR;	//�F�i���邳�j
	//float4 eyev	:TEXCOORD1;
};


struct PS_IN
{
	float4 pos  : SV_POSITION;	//�ʒu
	float4 pos_ : POSITION;
	float2 uv	: TEXCOORD;		//UV���W
	float4 color	: COLOR;	//�F�i���邳�j
	float4 eyev		:POSITION1;
	float4 normal	:POSITION2;
};


//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
PS_IN VS(VS_IN inData)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	PS_IN outData = (PS_IN)0;
	float4 posTmp = float4(inData.pos, 1.0);
	outData.pos_ = mul(posTmp, matW);
	outData.pos = mul(posTmp, matWVP);
	//outData.pos = pos;
	outData.uv = inData.uv;
	outData.color = diffuseColor;
	//outData.color = float4(1.0, 1.0, 1.0, 1.0);
	float4 normal;

	normal = mul(inData.normal, matNormal);
	normal.w = 0;
	normal = normalize(normal);
	outData.normal = normal;


	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(PS_IN inData) : SV_Target
{
	//float4 light = float4(0, 2, -2, 1); // �_�����̈ʒu
	float4 light = lightPosition; // �_�����̈ʒu

	float3 LD = inData.pos_ - light; // ���̕����x�N�g��
	float len = length(LD); // ���̕����x�N�g���𐳋K��(�傫���� 1 �ɂ�

	float lightMagnitude = saturate(dot(inData.normal, -normalize(LD)));
	float k = 1.0f / (1.0 * len * len);

	float4 NL = saturate(dot(inData.normal, normalize(lightPosition)));
	float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));
	float4 specular = 2 * pow(saturate(dot(reflect, normalize(inData.eyev))),8);
	
	float  n = clamp((0.8 * k * lightMagnitude),0,1);
	float4 lightSource = { 1,1,1,1 };//���̐F
	float4 ambientSource = { 1,1,1,1 };//�����̐F
	float4 ambTerm = 0.5;

	float4 diffuse;
	float4 ambient;
	if (isTextured.x == false)
	{
		diffuse = n * lightSource * inData.color ;
		ambient = ambTerm * ambientSource * inData.color ;
	}
	else
	{
		diffuse = n * lightSource * g_texture.Sample(g_sampler, inData.uv);
		ambient = ambTerm * ambientSource * g_texture.Sample(g_sampler, inData.uv);
	}
	//return g_texture.Sample(g_sampler, inData.uv);// (diffuse + ambient);]
	//float4 diffuse = lightSource * inData.color;
	//float4 ambient = lightSource * ambentSource;
	return diffuse + ambient + specular;
	
	//return g_texture.Sample(g_sampler, inData.uv);
}
