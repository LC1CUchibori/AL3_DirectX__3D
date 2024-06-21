#include <algorithm>
#include "CameraController.h"
#include "Player.h"

// 線形補間関数
template <typename T>
T Lerp(const T& a, const T& b, float t) {
	return a * (1 - t) + b * t;
}

void CameraController::Initialize()
{
	viewProjection_.Initialize();
}

void CameraController::Update()
{
    // 追従対象のワールドトランスフォームを参照
    const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
    // 追従対象とオフセットからのカメラの目標座標を計算
    cameraOffset_.x = targetWorldTransform.translation_.x + targetOffset_.x;
    cameraOffset_.y = targetWorldTransform.translation_.y + targetOffset_.y;
    cameraOffset_.z = targetWorldTransform.translation_.z + targetOffset_.z;

    // 座標補間によりゆったり追従
    viewProjection_.translation_.x = Lerp(viewProjection_.translation_.x, cameraOffset_.x, kInterpolationRate);
    viewProjection_.translation_.y = Lerp(viewProjection_.translation_.y, cameraOffset_.y, kInterpolationRate);
    viewProjection_.translation_.z = Lerp(viewProjection_.translation_.z, cameraOffset_.z, kInterpolationRate);

    // 移動範囲制限
    viewProjection_.translation_.x = min(viewProjection_.translation_.x, movableArea_.left);
    viewProjection_.translation_.x = max(viewProjection_.translation_.x, movableArea_.right);
    viewProjection_.translation_.y = max(viewProjection_.translation_.y, movableArea_.bottom);
    viewProjection_.translation_.y = min(viewProjection_.translation_.y, movableArea_.top);

    viewProjection_.UpdateMatrix();
}

void CameraController::Reset()
{
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	viewProjection_.translation_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	viewProjection_.translation_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	viewProjection_.translation_.z = targetWorldTransform.translation_.z + targetOffset_.z;
}

ViewProjection CameraController::GetViewPosition()
{
    return ViewProjection();
}
