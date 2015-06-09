//
//  TitleScene.h
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "Karakuri.h"
#include "Globals.h"


class TitleScene : public GMScene {

    GMBasicEffect*  mBasicEffect;
    GMSpriteBatch*  mSpriteBatch;
    
    GMMatrix        mProjection2D;
    GMMatrix        mProjection3D;
    GMMatrix        mView3D;
    
    GMTexture2D*    mTexBack;
    GMTexture2D*    mTexKey;
    GMTexture2D*    mTexMark5;
    
    int             mPushKeyState;
    int             mPushKeyX;
    int             mPushKeyCount;
    
    int             mTimeCount;
    
    int             mStatus;
    
    int             mFadeOutCount;
    
    GMMusic*        mBGM;
    GMSound*        mSound;
	GMLabel*		mShowBgmName;
	
public:
    TitleScene();
    virtual ~TitleScene();

public:
    virtual void    willAppear(GMGraphics* g);
    virtual void    didDisappear();
    
public:
    virtual void    drawView(GMGraphics* g);
    virtual void    updateModel(GMInput* input);
    
};


#endif  //#ifndef __TITLE_SCENE_H__


