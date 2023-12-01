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
	float4		diffuseColor;		//�}�e���A���̐F���g�U���ˌW��
	float4		lightDirection;
	float4		eyePosition;
	int			isTextured;			//�e�N�X�`���[���\���Ă��邩�ǂ���
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
	//float4 eyev		:TEXCOORD1;

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
	outData.pos_ = float4(inData.pos, 1.0);
	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(outData.pos_, matWVP);
	//outData.pos = pos;
	outData.uv = inData.uv;
	outData.color = diffuseColor;
	//outData.color = (1.0, 1.0, 1.0, 1.0);
	float4 normal;
	normal.w= 0;
	normal = mul(inData.normal, matW);
	normal = normalize(normal);
	outData.normal = normal;

	//float4 light = float4(0, 10, -2, 0);
	////float light = lightDirection;
	//light = normalize(light);
	//outData.color = clamp(dot(normal, light), 0, 1);
	//float4 posw = mul(pos, matW);
	//outData.eyev = eyePosition - posw;

	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(PS_IN inData) : SV_Target
{
	float4 light = float4(0.0, 2, 0, 1); // �_�����̈ʒu
	light = mul(light, matW);

	float3 LD = inData.pos_ - light; // ���̕����x�N�g��
	float len = length(LD); // ���̕����x�N�g���𐳋K��(�傫���� 1 �ɂ�
	//float4 outColor = inData.color;
	float4 outColor = { 1,1,1,1 };
	float lightMagnitude = saturate(dot(inData.normal, -normalize(LD)));
	float k = saturate(1.0f / (1.0f + 1.0 * len * len));

	return outColor * (0.8 * k * lightMagnitude + 0.2f);



	//return g_texture.Sample(g_sampler, inData.uv);
}
