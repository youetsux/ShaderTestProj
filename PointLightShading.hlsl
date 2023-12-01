//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global:register(b0)
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;           // ワールド行列
	float4x4	matNormal;           // ワールド行列
	float4		diffuseColor;		//マテリアルの色＝拡散反射係数
	float4		lightPosition;
	float4		eyePosition;
	int4		isTextured;			//テクスチャーが貼られているかどうか
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_IN
{
	float3 pos  : POSITION;	//位置
	float2 uv	: TEXCOORD;		//UV座標
	float3 normal	:NORMAL;
	//float4 color	: COLOR;	//色（明るさ）
	//float4 eyev	:TEXCOORD1;
};


struct PS_IN
{
	float4 pos  : SV_POSITION;	//位置
	float4 pos_ : POSITION;
	float2 uv	: TEXCOORD;		//UV座標
	float4 color	: COLOR;	//色（明るさ）
	float4 eyev		:POSITION1;
	float4 normal	:POSITION2;
};


//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
PS_IN VS(VS_IN inData)
{
	//ピクセルシェーダーへ渡す情報
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


	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(PS_IN inData) : SV_Target
{
	//float4 light = float4(0, 2, -2, 1); // 点光源の位置
	float4 light = lightPosition; // 点光源の位置

	float3 LD = inData.pos_ - light; // 光の方向ベクトル
	float len = length(LD); // 光の方向ベクトルを正規化(大きさを 1 にし

	float lightMagnitude = saturate(dot(inData.normal, -normalize(LD)));
	float k = 1.0f / (1.0 * len * len);

	float4 NL = saturate(dot(inData.normal, normalize(lightPosition)));
	float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));
	float4 specular = 2 * pow(saturate(dot(reflect, normalize(inData.eyev))),8);
	
	float  n = clamp((0.8 * k * lightMagnitude),0,1);
	float4 lightSource = { 1,1,1,1 };//光の色
	float4 ambientSource = { 1,1,1,1 };//環境光の色
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
