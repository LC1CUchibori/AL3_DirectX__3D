#include"GameScene.h"

// アフィン変換行列の作成
Matrix4x4 MakeAffineMatrix(const Vector3& scale_, const Vector3& rotation_, const Vector3& translation_);

// 行列の掛け算
Matrix4x4 MatrixMultiply(Matrix4x4& m1, Matrix4x4& m2);