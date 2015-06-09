/*
 *  GameOverScene.cpp
 *  Karakuri2 Mac for Xcode 4
 *
 *  Created by KAI Seiya on 12/01/23.
 *  Copyright 2012 Satoshi Numata. All rights reserved.
 *
 */

#include "GameOverScene.h"
#include "GameMain.h"



GameOverScene::GameOverScene()
{
	// Do nothing
}

GameOverScene::~GameOverScene()
{
    // Do nothing
}


void GameOverScene::willAppear(GMGraphics* g)
{
	// 基本のシェーダ、2D描画用バッチ
    mBasicEffect = new GMBasicEffect();
    mSpriteBatch = new GMSpriteBatch();
	
	GMVector2D screenSize = g->getScreenSize();
    mBasicEffect->setProjectionMatrix(GMMatrix::CreateOrthographicOffCenter(0.0, screenSize.x, 0.0, screenSize.y, -1.0, 1.0));
    mBasicEffect->setViewMatrix(GMMatrix::Identity);
	
	mStatus = 0;    // フェードイン
    mFadeCount = 80;
	
	if(gGameInst->mGlobal->getSelectCharacterFlag() == 1){
		mTex = new GMTexture2D("gameover_back_tako.png");
	}else if(gGameInst->mGlobal->getSelectCharacterFlag() == 2){
		mTex = new GMTexture2D("gameover_back_uni.png");
	}else if(gGameInst->mGlobal->getSelectCharacterFlag() == 3){
		mTex = new GMTexture2D("gameover_back_ika.png");
	}else {
		mTex = new GMTexture2D("gameover_back_tako.png");
	}
	
	mBGM = new GMMusic("gameover.mp3");
	mBGM->setVolume(gGameInst->getBgmVolume());
    mBGM->play();
}

void GameOverScene::didDisappear()
{
	delete mTex;
    mTex = NULL;
	
	mBGM->stop();
	delete mBGM;
    mBGM = NULL;
    
}

void GameOverScene::drawView(GMGraphics* g)
{
	//g->clear(GMColor(0.1, 0.1, 0.1, 1.0));
    
    mBasicEffect->begin();
    {
		
        //GMDrawSys::SetBlendMode(GMBlendModeAdd);
        mSpriteBatch->begin();
		
		
		mSpriteBatch->draw(mTex, GMVector2D(0,0), GMColor::White);
        
		
		mSpriteBatch->end();
		
		
        // フェードイン
        if (mStatus == 0 || mStatus == 10) {
            double alpha = mFadeCount / 80.0;
            
            mBasicEffect->enableTexture(false);
            GMDrawSys::SetBlendMode(GMBlendModeAlpha);
            GMDraw::Begin();
            GMDraw::FillQuad(GMVector2D(0, 0), GMVector2D(640, 0), GMVector2D(640, 480), GMVector2D(0, 480), GMColor(1, 1, 1, alpha));
            GMDraw::End();
        }
    }
    mBasicEffect->end();
}

void GameOverScene::updateModel(GMInput* input)
{
	
    if (mStatus == 0) {
		// フェードイン
        mFadeCount--;
        if (mFadeCount == 0) {
            mStatus = 1;
        }
    }else if (mStatus == 1) {
        if (input->isKeyDownTriggered(GMKeyMaskZ)) {
            mStatus = 10;
        }
	}else if (mStatus == 10) {
		// フェードアウト
        mFadeCount++;
        if (mFadeCount == 80) {
            GMGame::ChangeScene("title");
            return;
        }
    }
}

