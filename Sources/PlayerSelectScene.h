//
//  PlayerSelectScene.h
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/04.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __PLAYER_SELECT_SCENE
#define __PLAYER_SELECT_SCENE

#include "Karakuri.h"
#include "Globals.h"


class PlayerSelectScene : public GMScene {
    
    GMBasicEffect*  mBasicEffect;
    GMSpriteBatch*  mSpriteBatch;
    
    GMTexture2D*    mTexBack;
    GMTexture2D*    mTexSelector;
    GMTexture2D*    mTexSpec1;
    GMTexture2D*    mTexSpec2;
	GMTexture2D*    mTexKaitenRight;
	GMTexture2D*    mTexKaitenLeft;
	
	GMTexture2D*    mTexCharaTako;
	GMTexture2D*    mTexCharaIka;
	GMTexture2D*    mTexCharaUni;
	GMTexture2D*    mTexCharaInfo;
	GMTexture2D*    mTexSelectYajirushi;

	
	GMLabel*		mShowBgmName;
	
	
    int     mTimeCount;
    int		mKaitenRightX;
	int		mKaitenLeftX;
	
    int     mStatus;
    int     mFadeCount;
    
    double  mSelectorX;
    double	mSelectorY;
	
	int		mStatusBlinkWait;
	
	
    GMMusic*        mBGM;
    GMSound*        mSESelect;
    
public:
    PlayerSelectScene();
    virtual ~PlayerSelectScene();
    
public:
    virtual void    willAppear(GMGraphics* g);
    virtual void    didDisappear();
    
public:
    virtual void    drawView(GMGraphics* g);
    virtual void    updateModel(GMInput* input);
    
};


#endif  //#ifndef __PLAYER_SELECT_SCENE

