#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// 自キャラ
/// </summary>

class MapChipField;

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model,ViewProjection* viewProjection,const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	float x, y, z;

	// += 演算子のオーバーロード
	Vector3& operator+=(const Vector3& other) {
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
	}

	WorldTransform& GetWorldTransform() { return worldTransform_; }

	Vector3& GetVelocity() {return velocity_; }

	void SetMapChipField(MapChipField* mapChipField) { MapChipField* mapChipField_; }

private:

	// 左右
	enum class LRDirection {
		kRight,
		kLeft,
	};

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	Vector3 velocity_ = {};

	LRDirection lrDirection_ = LRDirection::kRight;

	MapChipField* mapChipField_ = nullptr;


	static inline const float kAcceleration = 0.03f;
	static inline const float kLimitRunSpeed = 0.6f;
	static inline const float kAttenuation = 0.03f;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.0f;

	// 接地状態フラグ
	bool onGround_ = true;

	// 重力加速度
	static inline const float kGravityAcceleration = 0.1f;
	// 最大落下速度
	static inline const float kLimitFallSpeed = 0.3f;
	// ジャンプ初速
	static inline const float kJumpAcceleration = 0.6f;

	const WorldTransform& GetWorldTransform()const { return worldTransform_; }
};

