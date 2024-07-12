#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugText.h"

/// <summary>
/// 自キャラ
/// </summary>

class MapChipField;

class Enemy {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

private:
    // ワールドトランスフォーム
	WorldTransform worldTransform_;
	// モデルのポインタ
	Model* model_ = nullptr;
	// ビュープロジェクションのポインタ
	ViewProjection* viewProjection_ = nullptr;
	// マップチップフィールドのポインタ
	MapChipField* mapChipField_ = nullptr;

	// 歩行の速さ
	static inline const float kWalkSpeed = 0.01f;
	// 速度
	Vector3 velocity_ = {};

	// 最初の角度[度]
	static inline const float kWalkMotionAngleStart = -7.0f;
	// 最後の角度[度]
	static inline const float kWalkMotionAngleEnd = 8.0f;
	// アニメーションの周期となる時間[秒]
	static inline const float kWalkMotionTime = 5.0f;
	// 経過時間
	float walkTimer_ = 0.0f;
};
