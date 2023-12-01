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
	float4		diffuseColor;		//マテリアルの色＝拡散反射係数
	float4		lightDirection;
	float4		eyePosition;
	int			isTextured;			//テクスチャーが貼られているかどうか
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
	//float4 eyev		:TEXCOORD1;

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
	outData.pos_ = float4(inData.pos, 1.0);
	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
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

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(PS_IN inData) : SV_Target
{
	float4 light = float4(0.0, 2, 0, 1); // 点光源の位置
	light = mul(light, matW);

	float3 LD = inData.pos_ - light; // 光の方向ベクトル
	float len = length(LD); // 光の方向ベクトルを正規化(大きさを 1 にし
	//float4 outColor = inData.color;
	float4 outColor = { 1,1,1,1 };
	float lightMagnitude = saturate(dot(inData.normal, -normalize(LD)));
	float k = saturate(1.0f / (1.0f + 1.0 * len * len));

	return outColor * (0.8 * k * lightMagnitude + 0.2f);



	//return g_texture.Sample(g_sampler, inData.uv);
}
