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
	for (auto& worldTransform : worldTransform_) {
		// スケール、回転、平行移動を反映してワールド行列を計算
		worldTransform.UpdateMatrix();
	}

	for (uint32_t i = 0; i < 8; ++i) {
		// 基本となるベクトル
		Vector3 velocity = { kSpeed,0.0f,0.0f };
		// 回転角を計算する
		float angle = kAngleUint * i;
		// Z軸まわり回転行列
		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);
		// 基本ベクトルを回転させて速度ベクトルを得る
		velocity = Transform(velocity, matrixRotation);
		// 移動処理
		worldTransforms_[i].translation_ += velocity;
	}

	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;
	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}

	// 終了ならなにもしない
	if (isFinished_) {
		return;
	}
}

void DeathParticles::Draw(const ViewProjection& viewProjection)
{
	// モデルの描画
	for (const auto& worldTransform : worldTransform_) {
		model_->Draw(worldTransform, viewProjection);
	}

	// 終了ならなにもしない
	if (isFinished_) {
		return;
	}
}
