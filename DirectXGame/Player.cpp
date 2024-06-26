#define NOMINMAX
#include "Player.h"
#include "Input.h"
#include <cassert>
#include<numbers>
#include<algorithm>
#include "mapChipField.h"

void Player::Initialize(Model* model, ViewProjection* viewProjection,const Vector3& position){

	// NULLチェック
	assert(model);

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	// 引数の内容をメンバ変数に記録
	model_ = model;
	//textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
}

void Player::Update(){

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// 1,移動入力

	// 衝突情報を初期化
	CollisionMapInfo collisionMapInfo;
	// 移動量に速度の値をコピー
	collisionMapInfo.movement_ = velocity_;

	// マップ衝突チェック
	MapCollision(collisionMapInfo);



	// 行列計算
	worldTransform_.UpdateMatrix();

	// 旋回制御
	if(turnTimer_>0.0f)
	{
		turnTimer_ -= 1.0f / 60.0f;
		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {
			std::numbers::pi_v<float> / 2.0f,
			std::numbers::pi_v<float>*3.0f / 2.0f
		};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = destinationRotationY;

	}

	// 着地フラグ
	bool landing = false;

	// 地面とのあたり判定
	if (velocity_.y < 0) {
		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;
		}
	}

	// 接地判定
	if (onGround_) {
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			// 空中状態の移行
			onGround_ = false;
		}
	}else {
		// 着地
		if (landing) {
			// めり込み排斥
			worldTransform_.translation_.y = 1.5f;
			// 摩擦で横方向速度が減衰する
			velocity_.x *= (1.0f - kAttenuation);
			// 下方向速度でリセット
			velocity_.y = 0.0f;
			// 接地状態に移行
			onGround_ = true;
		}
	}
}

void Player::Draw(){

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}

void Player::MoveInput()
{
	// 移動入力
	// 接地状態
	if (onGround_) {
		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {

			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {

				// 左移動中の右入力
				if (velocity_.x < 0.0f) {

					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = 0.5f;
				}
			}
			else if (Input::GetInstance()->PushKey(DIK_LEFT)) {

				// 右移動中の左入力
				if (velocity_.x > 0.0f) {

					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = 0.5f;
				}
			}
			// 加速/減速
			velocity_.x += acceleration.x;
			velocity_.y += acceleration.y;
			velocity_.z += acceleration.z;

			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		}
		if (Input::GetInstance()->PushKey(DIK_UP)) {
			// ジャンプ初速
			velocity_.y += kJumpAcceleration;
		}
		// 空中
	}
	else {
		// 落下速度
		velocity_.y -= kGravityAcceleration;
		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	// 移動
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

}

void Player::MapCollision(CollisionMapInfo& info)
{
	MapCollisionUp(info);
	MapCollisionDown(info);
	MapCollisionLeft(info);
	MapCollisionRight(info);
}

void Player::MapCollisionUp(CollisionMapInfo& info)
{

	// 上昇あり？
	if (info.movement_.y <= 0) {
		return;
	}
	
	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner>positonsNew;

	for (uint32_t i = 0; i < positonsNew.size(); ++i) {
		positonsNew[i] = CornerPosition(worldTransform_.translation_ + info.movement_, static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	// 真上のあたり判定を行う
	bool hit = false;
	// 左上点の判定
	MapChipField::IndexSet indexSet
}

void Player::MapCollisionDown(CollisionMapInfo& info)
{
	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner>positonsNew;

	for (uint32_t i = 0; i < positonsNew.size(); ++i) {
		positonsNew[i] = CornerPosition(worldTransform_.translation_ + info.movement_, static_cast<Corner>(i));
	}
}

void Player::MapCollisionLeft(CollisionMapInfo& info)
{
	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner>positonsNew;

	for (uint32_t i = 0; i < positonsNew.size(); ++i) {
		positonsNew[i] = CornerPosition(worldTransform_.translation_ + info.movement_, static_cast<Corner>(i));
	}
}

void Player::MapCollisionRight(CollisionMapInfo& info)
{
	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner>positonsNew;

	for (uint32_t i = 0; i < positonsNew.size(); ++i) {
		positonsNew[i] = CornerPosition(worldTransform_.translation_ + info.movement_, static_cast<Corner>(i));
	}
}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner)
{
	/*if (corner == kRightBottom) {
		return center + {+kWidth / 2.0f, -kHeight / 2.0f, 0};
	}
	else if (corner == kLeftBottom) {
		return center + {-kWidth / 2.0f, -kHeight / 2.0f, 0};
	}
	else if (corner == kRightTop) {
		return center + {+kWidth / 2.0f, +kHeight / 2.0f, 0};
	}
	else{
		return center + {-kWidth / 2.0f, +kHeight / 2.0f, 0};
	}*/

	Vector3 offsetTable[kNumCorner] = {
		{+kWidth / 2.0f,-kHeight / 2.0f,0}, // kRightBottom
		{-kWidth / 2.0f,-kHeight / 2.0f,0}, // kLeftBottom
		{+kWidth / 2.0f,+kHeight / 2.0f,0}, // kRightTop
		{-kWidth / 2.0f,+kHeight / 2.0f,0}  // kleftTop
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];
}

