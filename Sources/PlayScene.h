//
//  PlayScene.h
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/04.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__


#include "Karakuri.h"
#include "GameMain.h"
#include "Globals.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "EnemyDamageEffect.h"
#include "Item.h"
#include "EnemyBullet.h"


class BackStar {
    
    GMVector2D  mPos;
    GMVector2D  mV;
    
public:
    BackStar();
    
public:
    void    draw(GMSpriteBatch* batch, GMTexture2D* tex);
    bool    move();
    
};






class PlayScene : public GMScene {
    
    GMBasicEffect*  mBasicEffect;
    GMSpriteBatch*  mSpriteBatch;
    
    GMTexture2D*    mTexBack1;
    GMTexture2D*    mTexBack2;
    GMTexture2D*    mTexStar;
	GMTexture2D*    mTexItem1;
	GMTexture2D*    mTexItem2;
	GMTexture2D*    mTexItem3;
	
    GMTexture2D*    mTexTitle;
    
	GMTexture2D*	mCounter;
	GMTexture2D*	mGaugeLife;
	GMTexture2D*	mGaugeBoms;
	
	GMTexture2D*    mTexPlayerBullet1;
	GMTexture2D*    mTexOptionBullet1;
	GMTexture2D*    mTexPlayerBullet2;
	GMTexture2D*    mTexOptionBullet2;
	GMTexture2D*    mTexPlayerBullet3;
	GMTexture2D*    mTexOptionBullet3;
	
	GMLabel*		mShowScore;
	GMLabel*		mShowPower;
	GMLabel*		mShowPowerDecimal;

	
    EnemyDamageEffect*  mEnemyDamageEffect;
    
    EnemyManager*   mEnemyManager;
    EnemyBulletManager*   mEnemyBulletManager;
	
    int     mStatus;
    int     mFadeCount;
    
    int     mTitleCount;
    int		mFrameCount;
	int		mCountKeyDownX;
	int		mWaitClearScene;
	
    std::list<BackStar*>        mStars;
    std::list<PlayerBullet*>    mPlayerBullets;
	std::list<Item*>			mItems;
	std::list<Option*>			mOptions;
	
	
	
	Own*		mOwn;
    Player*     mPlayer;
    int         mPlayerType;
    
	int			mPlayerBulletState;
	
	
    GMMusic*    mBGM;
    GMMusic*    mBGMBoss1;
    GMSound*    mSEShot;
    GMSound*    mSEEnemyBreak;
	GMSound*	mSEExplosion;
	GMSound*	mSEExplosion2;
	
    bool        mIsPausing;
    
public:
    PlayScene();
    virtual ~PlayScene();
    
public:
    virtual void    willAppear(GMGraphics* g);
    virtual void    didDisappear();
    
public:
    virtual void    drawView(GMGraphics* g);
    virtual void    updateModel(GMInput* input);
    
public:
    void    setPlayerType(int type);
    int		getPlayerType() const;
	
private:
    void    drawBackground();
	
};


extern PlayScene*   gPlaySceneInst;


#endif  //#ifndef __PLAY_SCENE_H__

