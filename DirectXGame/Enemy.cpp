#include "Enemy.h"
#include <numbers>

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	// モデル変数に記録
	model_ = model;
	viewProjection_ = viewProjection;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = -3.14f / 2.0f;
}

void Enemy::Updata()
{
	// 行列計算
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw()
{
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}

