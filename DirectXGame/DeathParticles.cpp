#include "DeathParticles.h"

void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	// モデルを初期化
	model_ = model;
	// ビュープロジェクションを初期化
	viewProjection_ = viewProjection;
	// ワールド変換の初期化
	for (auto& worldTransform : worldTransform_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
}

void DeathParticles::Update()
{
	// ワールド変換の更新
	for (auto& worldTransform : worldTransforms_) {
		// アフィン変換行列を計算
		worldTransform.matWorld_ = 
			Matrix4::Scaling(worldTransform.scale_) *
			Matrix4::Rotation(worldTransform.rotation_) *
			Matrix4::Translation(worldTransform.translation_);
		// VRAMに転送 (仮の関数として TransferToVRAM を使用)
		TransferToVRAM(worldTransform.matWorld_);
	}
}

void DeathParticles::Draw(const ViewProjection& viewProjection)
{
	// モデルの描画
	for (auto& worldTransform : worldTransforms_) {
		// モデルの描画 (仮の関数として DrawModel を使用)
		DrawModel(model_, worldTransform.matWorld_, viewProjection_);
	}
}
