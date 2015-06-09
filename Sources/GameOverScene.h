/*
 *  GameOverScene.h
 *  Karakuri2 Mac for Xcode 4
 *
 *  Created by KAI Seiya on 12/01/23.
 *  Copyright 2012 Satoshi Numata. All rights reserved.
 *
 */

#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "Karakuri.h"
#include "Globals.h"


class GameOverScene : public GMScene {
	
private:
    GMBasicEffect*  mBasicEffect;
    GMSpriteBatch*  mSpriteBatch;
	
	int     mStatus;
    int     mFadeCount;
	
	
    GMTexture2D*    mTex;
    GMMusic*        mBGM;
	
public:
    GameOverScene();
    virtual ~GameOverScene();
	
public:
    virtual void    willAppear(GMGraphics* g);
    virtual void    didDisappear();
    
public:
    virtual void    drawView(GMGraphics* g);
    virtual void    updateModel(GMInput* input);
    
};


#endif  //#ifndef __GAME_OVER_SCENE_H__