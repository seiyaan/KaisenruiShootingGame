//
//  PlayerBullet.cpp
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/04.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "PlayerBullet.h"


PlayerBullet::PlayerBullet(const GMVector2D& pos,int type, GMInput* input)
    : mPos(pos) , mType(type)
{
	
	mAngle = 0.0;
    mAngleSpeed = 0.1;
	
	rot = 0;	// 円の角度(0 ～ 360)
	rot_speed = 50;	// 円の角度変化量(0 ～ 360)
	radius = 3 ;	// 円の半径
	
	
	
	if(mType == 0 ){
		//真ん中
		mSize = GMVector2D(16,64);
		mV = GMVector2D(0, 6);
		mA = GMVector2D(0, 0.2);
		
	}else if(mType == 100){
		//オプション
		mSize = GMVector2D(6,6);
		mV = GMVector2D(0, 5);
		mA = GMVector2D(0, 0.5);
	}
	
	
	
}

PlayerBullet::~PlayerBullet()
{
    // Do nothing
}

GMRect2D PlayerBullet::getAttackBounds() const
{
	return GMRect2D(mPos.x, mPos.y, mSize.x, mSize.y);
}

void PlayerBullet::draw(GMSpriteBatch* batch, GMTexture2D* tex)
{
	if(mType == 0 ){
		batch->draw(tex, mPos,GMRect2D::Empty, GMColor(GMVector4D(1.0,1.0,1.0,0.5)));
	}else {
		batch->draw(tex, mPos,GMRect2D::Empty, GMColor::White);
	}
}

bool PlayerBullet::move()
{
	
	rot += rot_speed;	// 角度を変化させる
	rad = rot * 3.14 / 180;	// 角度からラジアンに変換する
	
	if(mType == 0 ){
		//真ん中
		mV += mA;
		mPos += mV;
	}else if(mType == 100){
		//オプション
		mV += mA;
		mPos += mV;
	}
	
    if (mPos.y > 480) {
        return false;
    }
    
	mAngle += mAngleSpeed;
    return true;
}

int PlayerBullet::getType() const
{
	return mType;
}

GMVector2D PlayerBullet::getSize() const
{
	return mSize;
}





