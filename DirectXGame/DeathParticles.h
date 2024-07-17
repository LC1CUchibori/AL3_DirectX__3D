#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <array>

/// <summary>
/// デス演出用パーティクル
/// </summary>
class DeathParticles {
public:
	void Initialize(Model* model,ViewProjection* viewProjection,const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	// モデルのポインタ
	Model* model_ = nullptr;

	// ビュープロジェクションのポインタ
	ViewProjection* viewProjection_ = nullptr;

	WorldTransform* worldTransforms_ = nullptr;

	// パーティクルの個数
	static inline const uint32_t kNumParticles = 8;

	std::array<WorldTransform, kNumParticles>worldTransform_;
};