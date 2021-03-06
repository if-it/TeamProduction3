#pragma once
#include "Scene.h"
#include "Dx12_CBuffer.h"
#include "Dx12_Pipeline.h"
class ResultScene : public Scene
{
private:
	Dx12_CBuffer<DirectX::XMMATRIX>* orthograph;
	Dx12_Pipeline* animetionShader;
public:
	ResultScene();
	~ResultScene();
	void LoadAsset();
	void Initialize();
	void Update();
	void DrawSprite();
	void Draw();
	SceneName GetNextSceneName();
};