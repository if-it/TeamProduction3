#include "EnemyBullet.h"

MeshData EnemyBullet::md = MeshData();
Dx12_Mesh EnemyBullet::mesh = Dx12_Mesh();

EnemyBullet::EnemyBullet():cb(nullptr),pos(Vector3()),vel(Vector3()),target(Vector3()),isUse(false),isOldUse(false)
{
}

EnemyBullet::~EnemyBullet()
{
	delete cb;
}

void EnemyBullet::LoadAsset(ID3D12Device * device, Dx12_CBVSRVUAVHeap * heap)
{
	cb = new Dx12_CBuffer<CBData>(device, heap, 1);
}

void EnemyBullet::StaticLoadAsset(ID3D12Device * device, LoadContents * loader)
{
	loader->LoadMeshData("Resources/Model/", "Player", md);
	mesh.Create(device, &md);
}

void EnemyBullet::Initialize()
{
	pos = Vector3();
	vel = Vector3();
	target = Vector3();
	isUse = false;
	isOldUse = false;
}

void EnemyBullet::Update()
{
	isOldUse = isUse;
	if (isUse)
	{
		pos += vel;
		if (Vector3::Distance(pos, target) <= 16)
		{
			isUse = false;
		}
	}
	float a = (isUse) ? 1.0f : 0.0f;
	cb->Map({ Matrix4::Scale(Vector3(8,8,8)) * Matrix4::Translate(pos),{0,0,1,a} });
}

void EnemyBullet::Draw(ID3D12GraphicsCommandList * cmdList)
{
	cb->Set(cmdList);
	mesh.Draw(cmdList);
}

void EnemyBullet::SetTarget(const Vector3 & tp)
{
	target = tp;
	vel = Vector3::Normalize(target - pos) * 5;
}

void EnemyBullet::SetPosition(const Vector3 & p)
{
	pos = p;
}

Vector3 EnemyBullet::GetPosition()
{
	return pos;
}

void EnemyBullet::SetIsUse(bool b)
{
	isUse = b;
}

bool EnemyBullet::GetIsUse()
{
	return isUse;
}

bool EnemyBullet::GetIsOldUse()
{
	return isOldUse;
}

Vector3 EnemyBullet::GetLostPosition()
{
	return Vector3(target.x,1,target.z);
}