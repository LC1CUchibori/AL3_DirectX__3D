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

	void Updata();

	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

private:
    // ワールドトランスフォーム
	WorldTransform worldTransform_;
	// モデルのポインタ
	Model* model_ = nullptr;
	// ビュープロジェクションのポインタ
	ViewProjection* viewProjection_ = nullptr;

	MapChipField* mapChipField_ = nullptr;
};