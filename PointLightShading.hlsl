//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

cbuffer gmodel:register(b0)
{
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matW;           // ���[���h�s��
	float4x4	matNormal;           // ���[���h�s��
	float4		diffuseColor;		//�}�e���A���̐F���g�U���ˌW��
	bool		isTextured;			//�e�N�X�`���[���\���Ă��邩�ǂ���

};

cbuffer gmodel:register(b1)
{
	float4		lightPosition;
	float4		eyePosition;
};



struct PS_IN
{
	float4 pos  : SV_POSITION;	//�ʒu
	float2 uv	: TEXCOORD;		//UV���W
	float4 eyev		:POSITION1;
	float4 normal	:POSITION2;
	float4 light	:POSITION3;
};


//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
PS_IN VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	PS_IN outData = (PS_IN)0;

	outData.pos = mul(pos, matWVP);
	//outData.pos = pos;
	outData.uv = uv;
	float4 normalout;
	normalout = mul(normal, matNormal);
	normalout.w = 0;
	normalout = normalize(normalout);
	outData.normal = normalout;

	float4 posw = mul(pos, matW);
	outData.light = normalize(lightPosition - posw);
	outData.eyev = normalize(eyePosition - posw);
	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(PS_IN inData) : SV_Target
{

	float len = length(inData.light); // ���̕����x�N�g���𐳋K��(�傫���� 1 �ɂ�
					
	float NL = saturate(dot(inData.normal, inData.light));
	float k = 1.0f / (1.0 * len * len);

	float3 reflect = normalize(2 * NL * inData.normal - inData.light);
	float4 specular = pow(saturate(dot(reflect, inData.eyev)), 8);
	

	float4 lightSource = { 1,1,1,1 };//���̐F
	float4 ambientSource = { 1,1,1,1 };//�����̐F
	float4 ambTerm = 0.5;

	float4 diffuse;
	float4 ambient;
	if (isTextured.x == false)
	{
		diffuse = k*NL*lightSource * diffuseColor;
		ambient = ambTerm * ambientSource * diffuseColor;
	}
	else
	{
		diffuse = k*NL*lightSource * g_texture.Sample(g_sampler, inData.uv);
		ambient = ambTerm * ambientSource * g_texture.Sample(g_sampler, inData.uv);
	}

	return  diffuse + ambient + specular;
}
