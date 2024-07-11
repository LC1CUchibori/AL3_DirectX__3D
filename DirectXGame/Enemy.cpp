#include "Enemy.h"

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	// モデル変数に記録
	model_ = model;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
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
}
