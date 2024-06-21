#include "Viewprojection.h"
#include "Player.h"
#include "Vector3.h"
#include "MathUtilityForText.h"


class Player;

class CameraController {

public:

	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	void SetMovableArea(const Vector4& area)
	{
		movableArea_ .left= area.x; 
		movableArea_.right = area.y;
		movableArea_.bottom = area.z;
		movableArea_.top = area.w;
	}

	ViewProjection GetViewPosition();

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;

	Player* target_ = nullptr;

	Vector3 targetOffset_{ 0,0,-15.0f };

	Vector3 cameraOffset_{ 0,0,-15.0f };

	static inline const float kInterpolationRate = 0.5f;

	const ViewProjection& GetViewProjection()const { return viewProjection_; }

	// 矩形
	struct Rect {
		float left = 0.0f;// 左端
		float right = 1.0f;// 右端
		float bottom = 0.0f;// 下端
		float top = 1.0f;// 上端
	};

	Rect movableArea_ = { 0,100,0,100 };

};
