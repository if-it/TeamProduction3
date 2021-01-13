#include "Player.h"

Keyboard* Player::keyboard = nullptr;
Xinput* Player::ctrler = nullptr;

Player::Player()
	:cb(nullptr), pos(Vector3())
{
}

Player::~Player()
{
	delete cb;
}

void Player::LoadAsset(ID3D12Device * pDevice, Dx12_CBVSRVUAVHeap * heap, LoadContents * loader)
{
	cb = new Dx12_CBuffer<CBData>(pDevice, heap, 1);
	loader->LoadMeshData("Resources/Model/", "Player", md);
	mesh.Create(pDevice, &md);
}

void Player::Initialize()
{
	pos = Vector3(0,0,512);
	vel = Vector3();
	forward = Vector3();
	jumpFlag = false;
	fireValue = 0;
}

void Player::Update()
{
	const float MOVE_SPEED = 1.f;
	const float G = 0.98f;
	const float INCREASE_FIRE_VALUE = 1.f / 60.f;
	Vector3 moveVector = Vector3();
	if (pos.y <= 0)
	{
		pos.y = 0;
		vel.y = 0;
		if (jumpFlag)
		{
			jumpFlag = false;
		}
	}
	//�ړ�����
	if (keyboard->CheakHitKey(Key::W) || ctrler->CheckHitKey(XinputPadKey::XINPUT_UP) || ctrler->GetLStickY() < 0.0f)
	{
		moveVector += forward;
	}
	if (keyboard->CheakHitKey(Key::A) || ctrler->CheckHitKey(XinputPadKey::XINPUT_LEFT) || ctrler->GetLStickX() < 0.0f)
	{
		moveVector -= Vector3::Normalize(Vector3::Cross(Vector3(0, 1, 0), forward));;
	}
	if (keyboard->CheakHitKey(Key::S) || ctrler->CheckHitKey(XinputPadKey::XINPUT_DOWN) || ctrler->GetLStickY() > 0.0f)
	{
		moveVector -= forward;
	}
	if (keyboard->CheakHitKey(Key::D) || ctrler->CheckHitKey(XinputPadKey::XINPUT_RIGHT) || ctrler->GetLStickX() > 0.0f)
	{
		moveVector += Vector3::Normalize(Vector3::Cross(Vector3(0, 1, 0), forward));;
	}
	if (!jumpFlag && (keyboard->KeyPressTrigger(Key::SPACE) || ctrler->CheckHitKeyTrigger(XinputPadKey::XINPUT_A)))
	{
		jumpFlag = true;
		vel.y = 16;
	}

	if (moveVector.Length() > 0)
	{
		fireValue += INCREASE_FIRE_VALUE;
	}
	else
	{
		fireValue -= INCREASE_FIRE_VALUE;
	}

	if (fireValue < 0)
	{
		fireValue = 0;
	}
	else if (fireValue > 1)
	{
		fireValue = 1;
		moveVector *= 5;
	}

	vel.y -= G;
	pos += moveVector * MOVE_SPEED + vel;
	cb->Map({ Matrix4::Scale(Vector3(32,32,32)) *Matrix4::RotationY(atan2f(forward.x,forward.z))* Matrix4::Translate(pos),{fireValue,0,0,1} });
}

void Player::Draw(ID3D12GraphicsCommandList * pCmdList, Dx12_CBVSRVUAVHeap* heap)
{
	cb->Set(pCmdList);
	//pCmdList->SetGraphicsRootDescriptorTable(2, heap->GetSRVHandleForGPU(md.materialData.texture->GetSRVNumber()));
	mesh.Draw(pCmdList);
}

void Player::SetInputDevice(Keyboard * pKeyboard, Xinput * pCtrler)
{
	keyboard = pKeyboard;
	ctrler = pCtrler;
}

void Player::SetPosition(const Vector3 & p)
{
	pos = p;
}

Vector3 Player::GetPosition()
{
	return pos;
}

void Player::SetForward(const Vector3 & f)
{
	forward = f;
}

float Player::GetFireValue()
{
	return fireValue;
}

void Player::SetFireValue(float fv)
{
	fireValue = fv;
}