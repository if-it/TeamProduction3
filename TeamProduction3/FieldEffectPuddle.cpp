#include "FieldEffectPuddle.h"
Dx12_Mesh FieldEffectPuddle::mesh = Dx12_Mesh();

FieldEffectPuddle::FieldEffectPuddle() :FieldEffect()
{
}

FieldEffectPuddle::~FieldEffectPuddle()
{
	delete cb;
}

void FieldEffectPuddle::LoadAsset(ID3D12Device * device, Dx12_CBVSRVUAVHeap * heap)
{
	cb = new Dx12_CBuffer<CBData>(device, heap, 1);
}

void FieldEffectPuddle::Initialize()
{
	pos = Vector3();
	size = Vector3();
	reviveFlag = false;
	liveFlag = false;
	reviveT = 0;
	alpha = 0;
}

void FieldEffectPuddle::Update()
{
	const float REVIVE_TIME = 1;        //��������(�b)
	const float MAX_SIZE = 128;         //�}�b�N�X�T�C�Y
	const float DECREASE_ALPHA = 0.001f; //���R�ɂȂ��Ȃ�l
	if (reviveFlag)
	{
		if (reviveT < 1)
		{
			reviveT += (0.016f / REVIVE_TIME);
		}
		if (reviveT >= 1)
		{
			reviveT = 1;
			reviveFlag = false;
			liveFlag = true;
		}
		alpha = reviveT;
	}
	else
	{
		alpha -= DECREASE_ALPHA;
	}
	size = Vector3(MAX_SIZE, 1, MAX_SIZE) * alpha;
	cb->Map({ Matrix4::Scale(size)*Matrix4::Translate(pos),{0,0,1,alpha} });
	if (alpha <= 0)
	{
		Initialize();
	}
}

void FieldEffectPuddle::Draw(ID3D12GraphicsCommandList * cmdList)
{
	cb->Set(cmdList);
	mesh.Draw(cmdList);
}

void FieldEffectPuddle::StaticLoadAsset(ID3D12Device * device, LoadContents * loader)
{
	MeshData md;
	loader->LoadMeshData("Resources/Model/", "Player", md);
	mesh.Create(device, &md);
}