#include "TitleScene.h"
#include <numbers>
#include <TextureManager.h>

void TitleScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	titlemodel_ = Model::CreateFromOBJ("title", true);
	pushSpaceModel_ = Model::CreateFromOBJ("PushSpace", true);
	titleWorldTransform_.Initialize();
	viewProjection_.Initialize();
	PushSpaceWorldTransform_.Initialize();
	pushSpaceViewProjection_.Initialize();
	Timer_ = 0.0f;

	// タイトルを近づける
	titleWorldTransform_.translation_ = { 0.0f, 0.0f, -40.0f };  // z値を調整して近づける
	PushSpaceWorldTransform_.translation_ = { 0.0f,0.0f,-20.0f };

	// 天球の生成
	skydome_ = new Skydome();
	// 天球3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	// 天球の初期化
	skydome_->Initialize(modelSkydome_,&viewProjection_);

	/*Rule_ = TextureManager::Load("setumei.png");

	sprite_ = Sprite::Create(Rule_, { 10,10 });*/
	
}

void TitleScene::Update()
{
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}

	Timer_ += 1.0f / 60.0f;
	float param = std::sin(2.0f * std::numbers::pi_v<float> * Timer_ / kWalklMotionTime);
	float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	titleWorldTransform_.rotation_.y = radian * (std::numbers::pi_v<float> / 90.0f);
	// 行列計算
	titleWorldTransform_.UpdateMatrix();

	// 天球の更新
	skydome_->Update();

}

void TitleScene::Draw()
{
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);

	titlemodel_->Draw(titleWorldTransform_, viewProjection_);
	pushSpaceModel_->Draw(PushSpaceWorldTransform_, pushSpaceViewProjection_);

	// 天球の描画
	skydome_->Draw();

	Model::PostDraw();

	//// 背景スプライト描画前処理
	//Sprite::PreDraw(commandList);
	//sprite_->Draw();
	//// スプライト描画後処理
	//Sprite::PostDraw();

}
