/*
 *  EnemyBullet1.cpp
 *  Karakuri2 Mac for Xcode 4
 *
 *  Created by KAI Seiya on 11/12/18.
 *  Copyright 2011 Satoshi Numata. All rights reserved.
 *
 */

#include "EnemyBullet1.h"
#include "Player.h"
#include "PlayScene.h"


/* ============================================================== */
// Enemy1
/* ============================================================== */
// 上から降りてくる,停まる,そのまま降りる

EnemyBullet1::EnemyBullet1(const GMVector2D& pos, int life, int number ,int deadScore ,int item)
: EnemyBullet(pos, life)
{
	
	mState = 0; 
	mCount = 0;
	mItem = item;
	mNumber = number;
	mDeadScore = (deadScore != -1)? deadScore : life;
	
    mTex = new GMTexture2D("enemy_tamago.png");
    
	mAngle = 0.0;
    mAngleSpeed = 0.1;
	
	if(mPos.x <= 200){
		mPos.x = 50;
		mState = 0;
		mAngleSpeed *= -1;
	}else if(mPos.x > 200){
		mPos.x = 350;
		mState = 10;
	}
	
	mPos.y = pos.y;
}

EnemyBullet1::~EnemyBullet1()
{
	
	delete mTex;
    mTex = NULL;
}

GMRect2D EnemyBullet1::getDefenceBounds() const
{
    return GMRect2D(mPos.x+5, mPos.y+5, 22, 22);
}

void EnemyBullet1::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos+GMVector2D(16, 16), GMRect2D::Empty, GMColor::White, mAngle, GMVector2D(16, 16), GMVector2D::One, GMSpriteFlipNone, 0.0);
}

bool EnemyBullet1::moveImpl(Player *player)
{
	if(mState == 0){
		
	}else if(mState == 9999){
		return false;
	}
	
	mAngle += mAngleSpeed;
	mCount++;
    return true;
}
