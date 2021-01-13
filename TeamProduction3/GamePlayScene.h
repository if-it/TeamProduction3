#pragma once
#include "Scene.h"
#include "Dx12_CBuffer.h"
#include "Dx12_Pipeline.h"
#include "Camera.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Ground.h"
#include "FieldEffectPuddle.h"
#include "FieldEffectManager.h"
#include "Matrix4.h"

class GamePlayScene : public Scene
{
private:
	Camera mainCamera;
	Dx12_CBuffer<DirectX::XMMATRIX>* orthograph;
	Dx12_CBuffer<Perspective>* perspective;
	Dx12_Pipeline* simpleShader;
private:
	Player player;
	Ground ground;
	EnemyManager enemyManager;
	FieldEffectManager feManager;
public:
	GamePlayScene();
	~GamePlayScene();
	void LoadAsset();
	void Initialize();
	void Update();
	void DrawSprite();
	void Draw();
	SceneName GetNextSceneName();
};