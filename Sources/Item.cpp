//
//  PlayerBullet.cpp
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/04.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "Item.h"



Item::Item(const GMVector2D& pos,int type)
    : mPos(pos),mType(type)
{	
    mV = GMVector2D::Zero;
    mA = GMVector2D::Zero;
	mAngle = 0.0;
    mAngleSpeed = -0.5;
	
	mState = 0; 
	mCount = 0;
	
	collect = false;
	
	if(mType == 1 || mType == 2 || mType == 3){
		mSize = GMVector2D(16,16);
	}else {
		mSize = GMVector2D::Zero;
	}
}

Item::~Item()
{
	// Nothing
}

//当たり判定の範囲
GMRect2D Item::getAttackBounds() const
{
    return GMRect2D(mPos.x, mPos.y, mSize.x, mSize.y);
}

//接近の範囲
GMRect2D Item::getApproachBounds() const
{
	return GMRect2D(mPos.x - 25, mPos.y - 25 , mSize.x+50, mSize.y+50);
}


void Item::draw(GMSpriteBatch* batch,GMTexture2D* tex)
{
	batch->draw(tex, mPos, GMRect2D::Empty, GMColor::White, mAngle ,GMVector2D(mSize.x/2, mSize.y/2), GMVector2D::One, GMSpriteFlipNone, 0.0);
}

bool Item::move()
{
	if (mState == 0 ){
		mV.y = 3;
		
		if(mCount > 15 || collect == true){
			mState = 1;
		}
	} else if (mState == 1){
		mV.y -= 0.05;
		
		
		if(mV.y < -2.5){
			mV.y = -2.5;
			mState = 2;
		}		
	}
	
	if (mPos.y < -16) {
		return false;
	}
	
	mAngleSpeed += 0.01;
	if(mAngleSpeed > 0){
		mAngleSpeed = 0;
		
		if((int)mAngle % 360 != 0){
			mAngle = 0;
		}
	}
	
	
	mV += mA;
    mPos += mV;
    mAngle += mAngleSpeed;
	
	
	mCount++;
    return true;
}

void Item::setPos(GMVector2D pos)
{
	mPos = pos;
}

void Item::setCollect(bool flag){
	mV.x = 0.0;
	mV.y = 0.0;
	mA.x = 0.0;
	mA.y = 0.0;
	mAngleSpeed = -1.0;
	
	collect = flag;
}

int Item::getType() const
{
	return mType;
}

GMVector2D Item::getPos() const
{
    return mPos;
}

int Item::getState() const
{
	return mState;
}

bool Item::getCollect() const{
	return collect;
}
