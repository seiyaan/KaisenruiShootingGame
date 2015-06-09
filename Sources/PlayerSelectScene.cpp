//
//  PlayerSelectScene.cpp
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/04.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "PlayerSelectScene.h"
#include "PlayScene.h"


PlayerSelectScene::PlayerSelectScene()
{
    // Do nothing
}

PlayerSelectScene::~PlayerSelectScene()
{
    // Do nothing
}


void PlayerSelectScene::willAppear(GMGraphics* g)
{
    // 基本のシェーダ、2D描画用バッチ
    mBasicEffect = new GMBasicEffect();
    mSpriteBatch = new GMSpriteBatch();

    GMVector2D screenSize = g->getScreenSize();
    mBasicEffect->setProjectionMatrix(GMMatrix::CreateOrthographicOffCenter(0.0, screenSize.x, 0.0, screenSize.y, -1.0, 1.0));
    mBasicEffect->setViewMatrix(GMMatrix::Identity);
    
    mTexBack = new GMTexture2D("player_select_back2.png");
    mTexSelector = new GMTexture2D("player_selector.png");
    mTexSpec1 = new GMTexture2D("player_spec1.png");
    mTexSpec2 = new GMTexture2D("player_spec2.png");
	
	
	
	
	mTexKaitenRight =		new GMTexture2D("kaitendai_right.png");
	mTexKaitenLeft =		new GMTexture2D("kaitendai_left.png");
	mTexCharaTako =			new GMTexture2D("player_tako_mini.png");
	mTexCharaIka =			new GMTexture2D("player_ika_mini.png");
	mTexCharaUni =			new GMTexture2D("player_uni_mini.png");
	mTexCharaInfo =			new GMTexture2D("chara_info.png");
	mTexSelectYajirushi =	new GMTexture2D("select_yajirushi.png");
	
	
	mShowBgmName = new GMLabel("HelveticaNeue-Bold",13.0);
	mShowBgmName->setText("BGM:雪名残(煉獄庭園)");
	
    mStatus = 0;    // フェードイン
    mFadeCount = 80;
    
    mSelectorX = 0;
	mSelectorY = 163;
    mTimeCount = 0;
    
	mKaitenRightX = 0;
	mKaitenLeftX = 0;
	
	mStatusBlinkWait=0;
	
   
    mSESelect = new GMSound("select_se2.wav");
	mSESelect->setVolume(gGameInst->getSoundVolume());
	
	mBGM = new GMMusic("yukinagori.mp3");
	mBGM->setVolume(gGameInst->getBgmVolume());
    mBGM->play();
}

void PlayerSelectScene::didDisappear()
{
    delete mBGM;
    mBGM = NULL;
    
    delete mSESelect;
    mSESelect = NULL;
    
    delete mBasicEffect;
    mBasicEffect = NULL;
    
    delete mSpriteBatch;
    mSpriteBatch = NULL;

    delete mTexBack;
    mTexBack = NULL;

    delete mTexSpec1;
    mTexSpec1 = NULL;

    delete mTexSpec2;
    mTexSpec2 = NULL;
    
    delete mTexSelector;
    mTexSelector = NULL;
	
	delete mShowBgmName;
	mShowBgmName = NULL;
}

void PlayerSelectScene::drawView(GMGraphics* g)
{
    // 画面のクリア（全画面をテクスチャで描画する場合は不要。重くなるので省略する）
    //g->clear(GMColor::White);

    mBasicEffect->begin();
    {
        mSpriteBatch->begin();
        mSpriteBatch->draw(mTexBack, GMVector2D::Zero);
        
        const int blinkInterval = 65;
        double blinkAlpha = (mTimeCount % blinkInterval) * (2.0 / blinkInterval);
        if (blinkAlpha > 1.0) {
            blinkAlpha = 2.0 - blinkAlpha;
        }
        blinkAlpha = blinkAlpha * 0.75 + 0.25;
		
		/*
		if (mStatus != 0 && mStatus != 1 && mStatus !=  6 && mStatus != 4){
			mStatusBlinkWait=blinkInterval - mTimeCount % blinkInterval * 2;
		}
		if(mStatusBlinkWait>0){
			mStatusBlinkWait--;
			blinkAlpha = 1.0;
		}
		*/
		
		//回転台を表示する
		mSpriteBatch->draw(mTexKaitenRight, GMVector2D(mKaitenRightX,231));
		mSpriteBatch->draw(mTexKaitenRight, GMVector2D(-640+mKaitenRightX,231));
		mSpriteBatch->draw(mTexKaitenLeft, GMVector2D(320+mSelectorX,163));
		mSpriteBatch->draw(mTexKaitenLeft, GMVector2D(-320+mSelectorX,163));
		//タコイカウニを表示する
		mSpriteBatch->draw(mTexCharaIka, GMVector2D(mSelectorX-150,mSelectorY), GMColor(1, 1, 1, mStatus==6 ? blinkAlpha : 1.0));
		mSpriteBatch->draw(mTexCharaTako, GMVector2D(mSelectorX+320-150,mSelectorY), GMColor(1, 1, 1, mStatus==0||mStatus==1 ? blinkAlpha : 1.0));
		mSpriteBatch->draw(mTexCharaUni, GMVector2D(mSelectorX+640-150,mSelectorY), GMColor(1, 1, 1, mStatus==4 ? blinkAlpha :1.0));
		//キャラクタ情報
		mSpriteBatch->draw(mTexCharaInfo, GMVector2D(0,0),GMRect2D(0,(mStatus==4?0:mStatus==0||mStatus==1?1:mStatus==6?2:3)*160,640,160));
		//select用の矢印
		if(mStatus==1||mStatus==0){
			mSpriteBatch->draw(mTexSelectYajirushi, GMVector2D(0,mSelectorY),GMRect2D(0,0,100,150), GMColor(1, 1, 1, blinkAlpha));
			mSpriteBatch->draw(mTexSelectYajirushi, GMVector2D(540,mSelectorY),GMRect2D(540,0,100,150), GMColor(1, 1, 1, blinkAlpha));
		}
		else if(mStatus==4){
			mSpriteBatch->draw(mTexSelectYajirushi, GMVector2D(0,mSelectorY),GMRect2D(0,0,100,150), GMColor(1, 1, 1, blinkAlpha));
		}else if(mStatus==6){
			mSpriteBatch->draw(mTexSelectYajirushi, GMVector2D(540,mSelectorY),GMRect2D(540,0,100,150), GMColor(1, 1, 1, blinkAlpha));
        }
        
		//BGMタイトル
		mSpriteBatch->draw(mShowBgmName->getTexture(), GMVector2D(500,463), GMColor(GMVector3D(0.0,0.0,0.0)));

		
        mSpriteBatch->end();
        
        // フェードイン
        if (mStatus == 0) {
            double alpha = mFadeCount / 80.0;
            
            mBasicEffect->enableTexture(false);
            GMDrawSys::SetBlendMode(GMBlendModeAlpha);
            GMDraw::Begin();
            GMDraw::FillQuad(GMVector2D(0, 0), GMVector2D(640, 0), GMVector2D(640, 480), GMVector2D(0, 480), GMColor(0, 0, 0, alpha));
            GMDraw::End();
        }
        // フェードアウト
        else if (mStatus == 10) {
            double alpha = (80 - mFadeCount) / 80.0;
            
            mBasicEffect->enableTexture(false);
            GMDrawSys::SetBlendMode(GMBlendModeAlpha);
            GMDraw::Begin();
            GMDraw::FillQuad(GMVector2D(0, 0), GMVector2D(640, 0), GMVector2D(640, 480), GMVector2D(0, 480), GMColor(1, 1, 1, alpha));
            GMDraw::End();
        }
    }
	
	

	
	
    mBasicEffect->end();
}

void PlayerSelectScene::updateModel(GMInput* input)
{
    mTimeCount++;
	mKaitenRightX = mTimeCount % 640;
	
	
    // フェードイン
    if (mStatus == 0) {
        mFadeCount--;
        if (mFadeCount == 0) {
            mStatus = 1;
        }
    }
    // 真ん中のプレーヤ選択中
    else if (mStatus == 1) {
        if (input->isKeyDownTriggered(GMKeyMaskLeft)) {
            mStatus = 2;
        }else if (input->isKeyDownTriggered(GMKeyMaskRight)) {
            mStatus = 3;
        } 
		
		else if (input->isKeyDownTriggered(GMKeyMaskZ)) {
            gPlaySceneInst->setPlayerType(1);
            gGameInst->mGlobal->setSelectCharacterFlag(1);
			mFadeCount = 80;
            mStatus = 10;
            mSESelect->play();
			
        }
    }
    // 右へずらす
    else if (mStatus == 2) {
        mSelectorX += 20;
        if (mSelectorX >= 320) {
            mSelectorX = 320;
            mStatus = 6;
        }
		
    }
	// 左へずらす
	else if (mStatus == 3) {
        mSelectorX -= 20;
        if (mSelectorX <= -320) {
            mSelectorX = -320;
            mStatus = 4;
        }
    }
    // 左側のプレーヤ選択中
    else if (mStatus == 4) {
        if (input->isKeyDownTriggered(GMKeyMaskLeft)) {
            mStatus = 5;
        }else if (input->isKeyDownTriggered(GMKeyMaskZ)) {
            gPlaySceneInst->setPlayerType(2);
			gGameInst->mGlobal->setSelectCharacterFlag(2);
            mFadeCount = 80;
            mStatus = 10;
            mSESelect->play();
        }
    }
    // 左へずす
    else if (mStatus == 5) {
        mSelectorX += 20;
        if (mSelectorX >= 0) {
            mSelectorX = 0;
            mStatus = 1;
        }
    }
    // 右側のプレーヤ選択中
    else if (mStatus == 6) {
        if (input->isKeyDownTriggered(GMKeyMaskRight)) {
            mStatus = 7;
        }else if (input->isKeyDownTriggered(GMKeyMaskZ)) {
            gPlaySceneInst->setPlayerType(3);
			gGameInst->mGlobal->setSelectCharacterFlag(3);
            mFadeCount = 80;
            mStatus = 10;
            mSESelect->play();
        }
    }
	// 右へずらす
	else if (mStatus == 7) {
        mSelectorX -= 20;
        if (mSelectorX <= 0) {
            mSelectorX = 0;
            mStatus = 1;
        }
    }
	
    // フェードアウト
    else if (mStatus == 10) {

        mFadeCount--;
        if (mFadeCount == 0) {
            GMGame::ChangeScene("play");
            return;
        }
    }
}

