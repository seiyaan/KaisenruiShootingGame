//
//  TitleScene.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "TitleScene.h"
#include "GameMain.h"

TitleScene::TitleScene()
{
    // Do nothing
}

TitleScene::~TitleScene()
{
    // Do nothing
}

/*
    このシーンが表示されるときに呼ばれます。
 */
void TitleScene::willAppear(GMGraphics* g)
{
    // 基本のシェーダ、2D描画用バッチ
    mBasicEffect = new GMBasicEffect();
    mSpriteBatch = new GMSpriteBatch();

    // 2D用画面設定
    GMVector2D screenSize = g->getScreenSize();
    mProjection2D = GMMatrix::CreateOrthographicOffCenter(0.0, screenSize.x, 0.0, screenSize.y, -1.0, 1.0);
    mProjection3D = GMMatrix::CreatePerspectiveFieldOfView(M_PI/4, screenSize.x/screenSize.y, 1.0, 5000.0);
    mView3D = GMMatrix::CreateLookAt(GMVector3D(0, 0, 300),  // Camera Pos
                                     GMVector3D(0, 0, 0),  // Camera Target
                                     GMVector3D::Up);

    mBasicEffect->enableLighting(false);

    g->enableDepthTest(false);
    
    // タイトル画面のテクスチャ
    mTexBack = new GMTexture2D("title_back.png");
    mTexKey = new GMTexture2D("title_pushkey.png");
    mTexMark5 = new GMTexture2D("title_markUo.png");
    
	
	//BGMの名前
	mShowBgmName = new GMLabel("HelveticaNeue-Bold",13.0);
	mShowBgmName->setText("BGM:水･風･炎･地･空･冥･天(煉獄庭園)");
	
    mTimeCount = 0;
    mStatus = 0;    // キー入力待ち

    mPushKeyState = 0;
    mPushKeyX = (int)(-mTexKey->getSize().x);
    
    mSound = new GMSound("select_se2.wav");
    mSound->setVolume(gGameInst->getSoundVolume());
	
	//mBGM = new GMMusic("opening.m4a");
	mBGM = new GMMusic("suihu.mp3");
	mBGM->setVolume(gGameInst->getBgmVolume());
    mBGM->play();
	
}

/*
    他のシーンへの以降時またはアプリケーションの終了時に呼ばれます。
 */
void TitleScene::didDisappear()
{
    delete mBGM;
    mBGM = NULL;
    
    delete mSound;
    mSound = NULL;
    
    // 各種リソースのクリーンアップ
    delete mBasicEffect;
    mBasicEffect = NULL;
    
    delete mSpriteBatch;
    mSpriteBatch = NULL;
    
    delete mTexBack;
    mTexBack = NULL;
    
    delete mTexKey;
    mTexKey = NULL;

    delete mTexMark5;
    mTexMark5 = NULL;
	
	delete mShowBgmName;
	mShowBgmName = NULL;
}

/*
    ビューを描画します。
 */
void TitleScene::drawView(GMGraphics* g)
{
    // 画面のクリア（全画面をテクスチャで描画する場合は不要。重くなるので省略する）
    //g->clear(GMColor::CornflowerBlue);

    GMVector2D screenSize = g->getScreenSize();
    
    // 画面の描画
    mBasicEffect->setProjectionMatrix(mProjection2D);
    mBasicEffect->setViewMatrix(GMMatrix::Identity);
    mBasicEffect->setWorldMatrix(GMMatrix::Identity);
    mBasicEffect->begin();
    {
        GMDrawSys::SetBlendMode(GMBlendModeAlpha);
        mSpriteBatch->begin();
        mSpriteBatch->draw(mTexBack, GMVector2D(0, 0));
		mSpriteBatch->draw(mShowBgmName->getTexture(), GMVector2D(405,463), GMColor(GMVector3D(1.0,1.0,1.0)));
        mSpriteBatch->end();
    }
    mBasicEffect->end();
    
    mBasicEffect->setProjectionMatrix(mProjection3D);
    mBasicEffect->setViewMatrix(mView3D);
    mBasicEffect->begin();
    {
        const int rotationInterval = 200;
        double rotation = (mTimeCount % rotationInterval) * (1.0 / rotationInterval) * M_PI * 2;

        const int rotationInterval2 = 400;
        double rotation2 = (mTimeCount % rotationInterval2) * (1.0 / rotationInterval2) * M_PI * 2;

        mBasicEffect->setWorldMatrix(GMMatrix::CreateTranslation(-158/2, -241/2, 0) * GMMatrix::CreateRotationY(rotation2) * GMQuat::CreateFromAxisAngle(GMVector3D(196, 194, 0).normalize(), rotation));

        mBasicEffect->setTexture(mTexMark5);
        mBasicEffect->enableTexture(true);
        GMDrawSys::SetBlendMode(GMBlendModeAdd);
        GMDraw::Begin();
        GMDraw::FillQuad(GMVector2D(0, 0), GMVector2D(208, 0), GMVector2D(208, 221), GMVector2D(0, 221), GMColor(1, 1, 1, 0.75),
                         GMVector2D(0, 0), GMVector2D(1, 0), GMVector2D(1, 1), GMVector2D(0, 1));
        GMDraw::End();
    }
    mBasicEffect->end();
    
    mBasicEffect->setProjectionMatrix(mProjection2D);
    mBasicEffect->setViewMatrix(GMMatrix::Identity);
    mBasicEffect->setWorldMatrix(GMMatrix::Identity);
    mBasicEffect->begin();
    {
        GMDrawSys::SetBlendMode(GMBlendModeAlpha);
        mSpriteBatch->begin();
        const int keyInterval = 120;
        double keyAlpha = (mTimeCount % keyInterval) * (2.0 / keyInterval);
        if (keyAlpha > 1.0) {
            keyAlpha = 2.0 - keyAlpha;
        }
        keyAlpha = keyAlpha * 0.8 + 0.2;
        mSpriteBatch->draw(mTexKey, GMVector2D(mPushKeyX, 56), GMColor(1, 1, 1, keyAlpha));
        mSpriteBatch->end();
    }
    mBasicEffect->end();

    if (mStatus == 1) {
        mBasicEffect->setProjectionMatrix(mProjection2D);
        mBasicEffect->setViewMatrix(GMMatrix::Identity);
        mBasicEffect->begin();
        {
            mBasicEffect->enableTexture(false);
            GMDrawSys::SetBlendMode(GMBlendModeAlpha);
            GMDraw::Begin();
            double alpha = (80 - mFadeOutCount) / 80.0;
            GMDraw::FillQuad(GMVector2D(0, 0), GMVector2D(640, 0), GMVector2D(640, 480), GMVector2D(0, 480), GMColor(0, 0, 0, alpha));
            GMDraw::End();
        }
        mBasicEffect->end();
    }
	
}

/*
    モデルを1フレーム分更新します。
 */
void TitleScene::updateModel(GMInput* input)
{
    // キー入力待ち
    if (mStatus == 0) {
        if (input->isKeyDown(GMKeyMaskZ|GMKeyMaskX|GMKeyMaskC|GMKeyMaskSpace|GMKeyMaskReturn|GMKeyMaskShift)) {
            mFadeOutCount = 80;
            mStatus = 1;
            mSound->play();
        }
    }
    // フェードアウト
    else if (mStatus == 1) {
        mFadeOutCount--;
        if (mFadeOutCount == 0) {
            GMGame::ChangeScene("player_select");
            return;
        }
    }
    
    if (mPushKeyState == 0) {
        mPushKeyX += 15;
        if (mPushKeyX >= 49) {
            mPushKeyX = 49;
            //mPushKeyCount = 60*3;
			mPushKeyCount = 160;
            mPushKeyState = 1;
        }
    } else if (mPushKeyState == 1) {
        mPushKeyCount--;
        if (mPushKeyCount == 0) {
            mPushKeyState = 2;
        }
    } else if (mPushKeyState == 2) {
        mPushKeyX += 15;
        if (mPushKeyX >= 640) {
            mPushKeyX = (int)(-mTexKey->getSize().x);
            mPushKeyState = 0;
        }
    }
    
    mTimeCount++;
}

