#include "Viewprojection.h"
#include "Player.h"
#include "Vector3.h"


class Player;

class CameraController {

public:

	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	void SetMovableArea(Vector4 area) { movableArea_ = area; }

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;

	Player* target_ = nullptr;

	Vector3 targetOffset_{ 0,0,-15.0f };

	// 矩形
	struct Rect {
		float left = 0.0f;// 左端
		float right = 1.0f;// 右端
		float bottom = 0.0f;// 下端
		float top = 1.0f;// 上端
	};

	Rect movableArea_ = { 0,100,0,100 };
};
