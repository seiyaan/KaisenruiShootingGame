//
//  Enemy1.cpp
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/21.
//  Copyright 2011 Satoshi Numata. All rights reserved.
//

#include "Enemy1.h"
#include "Player.h"
#include "PlayScene.h"


/* ============================================================== */
// Enemy0 お茶
/* ============================================================== */
// 降りてくる　まっすぐ降りる
Enemy0::Enemy0(const GMVector2D& pos, int life, int number ,int deadScore, int item )
: Enemy(pos, life)
{
	mState = 0; 
	mItem = item;
	mNumber = number;
	mDeadScore = (deadScore != -1)? deadScore : life;
	
	mSize = GMVector2D(32,32);
    mTex = new GMTexture2D("enemy_tee_1.png");
    
	
	if(pos.x < 200){
		mType = 0;
		mCount = -1*number * 30;
		mPos.x = mNumber * 40 ;
	}else{
		mType = 1;
		mCount = -1*(8-number) * 30;
		mPos.x = mNumber * 40 + 80;
	}
	mPos.y = 600;
    mV = GMVector2D(0, 0);
}

Enemy0::~Enemy0()
{
	delete mTex;
    mTex = NULL;
}

GMRect2D Enemy0::getDefenceBounds() const
{
    return GMRect2D(mPos.x+5, mPos.y+5, mSize.x-10, mSize.y-10);
}

void Enemy0::draw(GMSpriteBatch* batch)
{
	if(mType == 0){
		batch->draw(mTex, mPos, GMRect2D(((mCount/4)%4)*32, 0, 32, 32));
	}else {
		batch->draw(mTex, mPos, GMRect2D((3-(mCount/4)%4)*32, 0, 32, 32));
	}
}

bool Enemy0::moveImpl(Player *player)
{	
	
	
	if(mState == 0){
		if(mCount > 0){
			mState = 1;
		}
	}else if(mState == 1){
		if(movePhysical( mNumber * 40 -mPos.x + 40, 350 - mPos.y , 40) == true){
			setBullet(1,1,12);
			mState = 2;
			if(mType == 0){
				mCount += mNumber*30;
			}else {
				mCount += (8-mNumber)*30;
			}
		}
	}else if(mState == 2){
		if(mCount > 350){
			mState = 3;
		}
	}else if(mState == 3){
		if(movePhysical( 0 , -50 - mPos.y , 100) == true){
			mState = 9999;
		}
	}else {
		return false;
	}
	
	mCount++;
    return true;
}


/* ============================================================== */
// Enemy1 マグロ
/* ============================================================== */
// くねっと曲がる
Enemy1::Enemy1(const GMVector2D& pos, int life, int number ,int deadScore ,int item )
    : Enemy(pos, life)
{
	mState = 0; 
	mItem = item;
	mNumber = number;
	mDeadScore = (deadScore != -1)? deadScore : life;
	mCount = -1*number * 30;
	
	mSize = GMVector2D(58,43);
    mTex = new GMTexture2D("enemy_maguro1-1.gif");
    
	if(pos.x < 200){
		mType = 0;
	}else {
		mType = 1;
	}
	
	mPos.x = pos.x;
	mPos.y = pos.y;
	mPosInX = mPos.x;
    mPosInY = mPos.y;
    mV = GMVector2D(0, 0);
	
	if(mType == 0){
		mRot = 90.0;	// 円の角度(0 ～ 360)
		mRot_speed = 2.0;	// 円の角度変化量(0 ～ 360)
	}else if(mType == 1){
		mRot = 270.0;
		mRot_speed = -2.0;
	}

	mRad = 0.0;	// ラジアン
	mRadius = 80 ; //半径
	
	mAngle = 0.0;
	mAngleSpeed = 0.1;
	
}

Enemy1::~Enemy1()
{
	delete mTex;
    mTex = NULL;
}

GMRect2D Enemy1::getDefenceBounds() const
{
    return GMRect2D(mPos.x+5, mPos.y+5, mSize.x-10, mSize.y-10);
}

void Enemy1::draw(GMSpriteBatch* batch)
{
	batch->draw(mTex, mPos, GMRect2D(0, 0, mSize.x, mSize.y));
}

bool Enemy1::moveImpl(Player *player)
{
	
	if (mState == 0){		
		if(mCount > -1){
			mState = 1;
			mV = GMVector2D(0, -2);
		}
	}else if (mState == 1){
		if(mPos.y < 350){
			mState = 2;
			mV = GMVector2D(0,0);
			mPosInY = mPos.y;
		}
	}else if(mState == 2){
		
		mRad = mRot * 3.14 / 180;	// 角度からラジアンに変換する
		mRot += mRot_speed;

		
		if(mType == 0){
			//反時計
			mPos.x = cos(mRad +(90*3.14/180)) * mRadius + mRadius + mPosInX;
			mPos.y = sin(mRad +(90*3.14/180)) * mRadius + mPosInY;
			if( mRot >= 180){
				mRot = 360;
				mState = 3;
				mV = GMVector2D(2, 0);
			}
		}else if(mType == 1){
			mPos.x = cos(mRad +(90*3.14/180)) * mRadius - mRadius + mPosInX;
			mPos.y = sin(mRad +(90*3.14/180)) * mRadius + mPosInY;
			if( mRot <= 180){
				mRot = 0;
				mState = 3;
				mV = GMVector2D(-2, 0);
			}
		}
		
	}else if(mState == 3){
		if(mPos.x > 400){
			mState = 9999;
		}
	}else{
		return false;
	}
	
	
	mAngle += mAngleSpeed;
	mCount++;
    return true;
}


/* ============================================================== */
// Enemy2 プリン
/* ============================================================== */
// 上から降りてくる,停まる,自機に向かって降りてくる

Enemy2::Enemy2(const GMVector2D& pos, int life, int number ,int deadScore ,int item )
: Enemy(pos, life)
{
	
	mState = 0; 
	mItem = item;
	mNumber = number;
	mDeadScore = (deadScore != -1)? deadScore : life;
	
	mSize = GMVector2D(64,64);
    mTex = new GMTexture2D("enemy_purin_1.png");
    
	
	if(pos.x < 200){
		mType = 0;
	}else {
		mType = 1;
	}
	
	mCount = -1*number * 30;
	
	mPos.x = pos.x;
	mPos.y = pos.y;
    mV = GMVector2D(0, 0);
}

Enemy2::~Enemy2()
{
	delete mTex;
    mTex = NULL;
}

GMRect2D Enemy2::getDefenceBounds() const
{
    return GMRect2D(mPos.x+5, mPos.y+5, mSize.x-10, mSize.y-10);
}

void Enemy2::draw(GMSpriteBatch* batch)
{
	batch->draw(mTex, mPos, GMRect2D(((mCount/4)%4)*64, 0, 64, 64));
}

bool Enemy2::moveImpl(Player *player)
{
	if (mState == 0){		
		if(mCount > -1){
			mState = 1;
			mCount = -1;
		}
	}else if(mState == 1){
		if(mType == 0){
			if(movePhysical( 0 , 350 - mPos.y , 60) == true){
				mState = 2;
			}
		}else if(mType == 1){
			if(movePhysical( 0 , 350 - mPos.y , 60) == true){
				mState = 2;
			}
		}
	}else if(mState == 2){
		if(mCount%60 == 5 || mCount%60 == 10 || mCount%60 == 15){
			setBullet(2,1,12);
		}
		
		if(mCount > 320){
			mState = 3;
		}
	}else if(mState == 3){
		if(movePhysical( player->getPosX() -mPos.x , -64 - mPos.y , 120) == true){
			mState = 9999;
		}
	}else {
		return false;
	}
	
	
	mCount++;
    return true;
}

/* ============================================================== */
// Enemy3 お茶
/* ============================================================== */
// 降りてくる 向かってくる
Enemy3::Enemy3(const GMVector2D& pos, int life, int number ,int deadScore,int item )
: Enemy(pos, life)
{
	mState = 0; 
	mItem = item;	mNumber = number;
	mDeadScore = (deadScore != -1)? deadScore : life;
	
	mSize = GMVector2D(32,32);
    mTex = new GMTexture2D("enemy_tee_1.png");
    
	
	if(pos.x < 200){
		mType = 0;
		mCount = -1*number * 30;
		mPos.x = mNumber * 40 ;
	}else{
		mType = 1;
		mCount = -1*(8-number) * 30;
		mPos.x = mNumber * 40 + 80;
	}
	
	mPos.y = 600;
    mV = GMVector2D(0, 0);
    
}

Enemy3::~Enemy3()
{
	delete mTex;
    mTex = NULL;
}

GMRect2D Enemy3::getDefenceBounds() const
{
    return GMRect2D(mPos.x+5, mPos.y+5, mSize.x-10, mSize.y-10);
}

void Enemy3::draw(GMSpriteBatch* batch)
{
	if(mType == 0){
		batch->draw(mTex, mPos, GMRect2D(((mCount/4)%4)*32, 0, 32, 32));
	}else {
		batch->draw(mTex, mPos, GMRect2D((3-(mCount/4)%4)*32, 0, 32, 32));
	}
}

bool Enemy3::moveImpl(Player *player)
{	
	
	if(mState == 0){
		if(mCount > 0){
			mState = 1;
		}
	}else if(mState == 1){
		if(movePhysical( mNumber * 40 -mPos.x + 40, 350 - mPos.y , 40) == true){
			mState = 2;
			if(mType == 0){
				mCount += mNumber*30;
			}else {
				mCount += (8-mNumber)*30;
			}
			
			setBullet(2,1,12);
		}
	}else if(mState == 2){
		if(mCount % 60 == 0 || mCount % 60 == 1 ||mCount % 60 == 2 ||mCount % 60 == 3 ||mCount % 60 == 4 )
		{
			setBullet(5,1,1);
		}
		
		if(mCount > 350){
			mState = 3;
			setBullet(2,1,12);
		}
	}else if(mState == 3){
		if(movePhysical( player->getPosX() -mPos.x , -50 - mPos.y , 100) == true){
			mState = 9999;
		}
	}else {
		return false;
	}
	
	mCount++;
    return true;
}


/* ============================================================== */
// Enemy4 マグロ
/* ============================================================== */
// 上から降りてくる，一時停止，斜めに降りる
Enemy4::Enemy4(const GMVector2D& pos, int life, int number ,int deadScore,int item )
: Enemy(pos, life)
{
	mState = 0; 
	mItem = item;
	mNumber = number;
	mDeadScore = (deadScore != -1)? deadScore : life;
	mCount = -1*number * 30;
	
	mSize = GMVector2D(58,43);
    mTex = new GMTexture2D("enemy_maguro1-1.gif");
    
	if(pos.x < 200){
		mType = 0;
	}else {
		mType = 1;
	}
	
	if(mType == 0){
		mPos.x = pos.x + (mNumber%2*-50);
		mPos.y = pos.y + (mType/2) * 50;
	}else {
		mPos.x = pos.x + (mNumber%2*50);
		mPos.y = pos.y + (mType/2) * 50;
	}
	mV = GMVector2D(0, 0);
	
	if(mType == 0){
		
	}else if(mType == 1){
		
	}
}

Enemy4::~Enemy4()
{
	delete mTex;
    mTex = NULL;
}

GMRect2D Enemy4::getDefenceBounds() const
{
    return GMRect2D(mPos.x+5, mPos.y+5, mSize.x-10, mSize.y-10);
}

void Enemy4::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos);
}

bool Enemy4::moveImpl(Player *player)
{
	if(mState == 0){
		if(mCount == 0){
			mState = 1;
		}
	}else if(mState == 1){
		if(movePhysical(0, 270 - mPos.y + (mNumber/2)*25, 120) == true){
			mState = 2;
		}
	}else if(mState == 2){
		if(mCount > 150){
			mState = 3;
			if(mType == 0){
				mV = GMVector2D(3,-2);
			}else {
				mV = GMVector2D(-3,-2);
			}
		}
	}else if(mState == 3){
		if(mPos.x+mSize.x < 0 || mPos.x > 400){
			mState = 9999;
		}
	}else {
		return false;
	}
	mCount++;
    return true;
}


/* ============================================================== */
// Enemy5 マグロ
/* ============================================================== */
// 上から降りてくる，一時停止(弾を打つ)，斜めに降りる
Enemy5::Enemy5(const GMVector2D& pos, int life, int number ,int deadScore,int item )
: Enemy(pos, life)
{
	mState = 0; 
	mItem = item;
	mNumber = number;
	mDeadScore = (deadScore != -1)? deadScore : life;
	mCount = -1*number * 30;
	
	mSize = GMVector2D(58,43);
    mTex = new GMTexture2D("enemy_maguro1-2.gif");
    
	if(pos.x < 200){
		mType = 0;
	}else {
		mType = 1;
	}
	
	if(mType == 0){
		mPos.x = pos.x + (mNumber%2*-50);
		mPos.y = pos.y + (mType/2) * 50;
	}else {
		mPos.x = pos.x + (mNumber%2*50);
		mPos.y = pos.y + (mType/2) * 50;
	}
	mV = GMVector2D(0, 0);
	
	if(mType == 0){
		
	}else if(mType == 1){
		
	}
}

Enemy5::~Enemy5()
{
	delete mTex;
    mTex = NULL;
}

GMRect2D Enemy5::getDefenceBounds() const
{
	return GMRect2D(mPos.x+5, mPos.y+5, mSize.x-10, mSize.y-10);
}

void Enemy5::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos);
}

bool Enemy5::moveImpl(Player *player)
{
	if(mState == 0){
		if(mCount == 0){
			mState = 1;
		}
	}else if(mState == 1){
		if(movePhysical(0, 270 - mPos.y + (mNumber/2)*25, 120) == true){
			mState = 2;
		}
	}else if(mState == 2){
		if(mCount > 125 && mCount <= 135){
			setBullet(5,0,1);
		}
		
		if(mCount > 150){
			mState = 3;
			if(mType == 0){
				mV = GMVector2D(3,-2);
			}else {
				mV = GMVector2D(-3,-2);
			}
		}
	}else if(mState == 3){
		if(mPos.x+mSize.x < 0 || mPos.x > 400){
			mState = 9999;
		}
	}else {
		return false;
	}
	mCount++;
    return true;
}



/* ============================================================== */
// Enemy6 卵
/* ============================================================== */
// 右もしくは左から敵が出てくる真っ直ぐ左もしくは右へ逃げる
Enemy6::Enemy6(const GMVector2D& pos, int life, int number ,int deadScore,int item )
: Enemy(pos, life)
{
	mState = 0; 
	mItem = item;
	mNumber = number;
	mDeadScore = (deadScore != -1)? deadScore : life;
	mCount = 0;
	
	mSize = GMVector2D(58,43);
    mTex = new GMTexture2D("enemy_tamago1-1.gif");
    
	if(pos.x < 200){
		mType = 0;
	}else {
		mType = 1;
	}
	
	if(mType == 0){
		mPos.x = pos.x + (mNumber/2*-60 + mNumber%2*-30);
		mPos.y = pos.y + (mNumber%2*60);
		mV = GMVector2D(4, -1);
	}else {
		mPos.x = pos.x + (mNumber/2*60 + mNumber%2*30);
		mPos.y = pos.y + (mNumber%2*60);
		mV = GMVector2D(-4, -1);
	}
}

Enemy6::~Enemy6()
{
	delete mTex;
    mTex = NULL;
}

GMRect2D Enemy6::getDefenceBounds() const
{
    return GMRect2D(mPos.x+5, mPos.y+5, mSize.x-10, mSize.y-10);
}

void Enemy6::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos);
}

bool Enemy6::moveImpl(Player *player)
{
	if(mState == 0){
		if(mPos.x > 100 && mPos.x < 300){
			mState = 1;
		}
	} else if(mState == 1){
		if(mPos.x+mSize.x < 0 || mPos.x > 400){
			mState = 9999;
		}
	}else {
		return false;
	}
	mCount++;
    return true;
}

/* ============================================================== */
// Enemy7 数の子
/* ============================================================== */
// 右もしくは左から敵が出てくる真っ直ぐ左もしくは右へ逃げる 弾を打つ
Enemy7::Enemy7(const GMVector2D& pos, int life, int number ,int deadScore,int item )
: Enemy(pos, life)
{
	mState = 0; 
	mItem = item;
	mNumber = number;
	mDeadScore = (deadScore != -1)? deadScore : life;
	mCount = 0;
	
	mSize = GMVector2D(60,30);
    mTex = new GMTexture2D("enemy_kazu1-1.gif");
    
	if(pos.x < 200){
		mType = 0;
	}else {
		mType = 1;
	}
	
	if(mType == 0){
		mPos.x = pos.x + (mNumber/2*-60 + mNumber%2*-30);
		mPos.y = pos.y + (mNumber%2*60);
		mV = GMVector2D(4, -1);
	}else {
		mPos.x = pos.x + (mNumber/2*60 + mNumber%2*30);
		mPos.y = pos.y + (mNumber%2*60);
		mV = GMVector2D(-4, -1);
	}
}

Enemy7::~Enemy7()
{
	delete mTex;
    mTex = NULL;
}

GMRect2D Enemy7::getDefenceBounds() const
{
	return GMRect2D(mPos.x+5, mPos.y+5, mSize.x-10, mSize.y-10);
}

void Enemy7::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos);
}

bool Enemy7::moveImpl(Player *player)
{
	
	if(mState == 0){
		if(mPos.x > 100 && mPos.x < 300){
			mState = 1;
		}
	} else if(mState == 1){
		if(mPos.x+mSize.x < 0 || mPos.x > 400){
			mState = 9999;
		}
	}else {
		return false;
	}
	
	if((mPos.x+mSize.x > 50 && mPos.x < 75)||(mPos.x+mSize.x > 175 && mPos.x < 225)||(mPos.x+mSize.x > 350 && mPos.x < 375)){
		if(mCount%10 == 0){
			setBullet(7, 0, 1);
		}
	}
	
	mCount++;
    return true;
}




/* ============================================================== */
// Enemy8 わさび
/* ============================================================== */
// 降りてくる　まっすぐ降りる
Enemy8::Enemy8(const GMVector2D& pos, int life, int number ,int deadScore, int item )
: Enemy(pos, life)
{
	mState = 0; 
	mItem = item;
	mNumber = number;
	mCount = 0;
	mDeadScore = (deadScore != -1)? deadScore : life;
	mPos = pos;
	
	if(pos.x < 200){
		mType = 0;
		mTex = new GMTexture2D("enemy_wasa1-1.gif");
	}else{
		mType = 1;
		mTex = new GMTexture2D("enemy_wasa1-2.gif");
	}
	
	mCount = -mNumber* 120;
	mSize = GMVector2D(97,21);
	
    mV = GMVector2D(0, 0);
	mA = GMVector2D(0, 0);
}

Enemy8::~Enemy8()
{
	delete mTex;
    mTex = NULL;
	
}

GMRect2D Enemy8::getDefenceBounds() const
{
    return GMRect2D(mPos.x+5, mPos.y+5, mSize.x-10, mSize.y-10);
}

void Enemy8::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos);
}

bool Enemy8::moveImpl(Player *player)
{	
	if(mState == 0){
		if(mCount >= 0){
			mState = 1;
			mV.y = -1;
		}
	}else if(mState == 1){
		if(mCount % 4 == 0){
			setBullet(8, 0, 1);
		}
		if(mPos.y+mSize.y < 0){
			mState = 9999;
		}
	}else {
		return false;
	}
	
	mCount++;
    return true;
}


/* ============================================================== */
// Enemy9 ほたて
/* ============================================================== */
// ゆっくりおりてくるだけ
Enemy9::Enemy9(const GMVector2D& pos, int life, int number ,int deadScore,int item )
: Enemy(pos, life)
{
	mState = 0; 
	mItem = item;
	mNumber = number;
	mDeadScore = (deadScore != -1)? deadScore : life;
	mCount = 0;
	
	mSize = GMVector2D(52,41);
    mTex = new GMTexture2D("enemy_hotate1-2.gif");
    
	if(pos.x < 200){
		mType = 0;
	}else {
		mType = 1;
	}
	
	mPos.x += mNumber*100;
	mV = GMVector2D(0, -1);
}

Enemy9::~Enemy9()
{
	delete mTex;
    mTex = NULL;
}

GMRect2D Enemy9::getDefenceBounds() const
{
	return GMRect2D(mPos.x+5, mPos.y+5, mSize.x-10, mSize.y-10);
}

void Enemy9::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos);
}

bool Enemy9::moveImpl(Player *player)
{
	if(mState == 0){
		if(mPos.x+mSize.x < 0 || mPos.x > 400){
			mState = 9999;
		}
	}else {
		return false;
	}
	mCount++;
    return true;
}

/*
Enemy4::Enemy4(const GMVector2D& pos, int life, int number ,int deadScore,int item )
: Enemy(pos, life)
{
	mState = 0; 
	mCount = 0;
	mItem = item;
	mDeadScore = (deadScore != -1)? deadScore : life;
	
	mSize = GMVector2D(32,32);
    mTex = new GMTexture2D("enemy_maguro1-1.gif");
    mPos.y += number * 32;
	
	mPosInX = mPos.x;
    mPosInY = mPos.y;
	
	mRot = 0.0;	// 円の角度(0 ～ 360)
	mRot_speed = 1.0;	// 円の角度変化量(0 ～ 360)
	mRad = 0.0;	// ラジアン
	mRadius = 80 ; //半径
	
	mV.y = -4;
	mAngle = 0.0;
	
	if(mPos.x < 200){
		startFlag = 0;
		mAngleSpeed = -0.1;
	}else if(200 <= mPos.x){
		startFlag = 1;
		mAngleSpeed = 0.1;
	}
	
	
	
    
}

Enemy4::~Enemy4()
{
	delete mTex;
    mTex = NULL;
}

GMRect2D Enemy4::getDefenceBounds() const
{
    return GMRect2D(mPos.x+5, mPos.y+5, 22, 22);
}

void Enemy4::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos+GMVector2D(16, 16), GMRect2D::Empty, GMColor::White, mAngle, GMVector2D(16, 16), GMVector2D::One, GMSpriteFlipNone, 0.0);
}

bool Enemy4::moveImpl(Player *player)
{
	
	
	if (mState == 0){		
		if(mPos.y < 300){
			mState = 1;
		}
	}else if (mState == 1){
		mRad = mRot * 3.14 / 180;	// 角度からラジアンに変換する
		mRot += 4;
		
		if( mRot > 720){
			//二週半する
			mRot = 720;
			mState = 2;
		}
		
		if(startFlag == 0){
			//右回転
			mPos.x = cos(mRad+(90*2*3.14/180)) * mRadius + mRadius + mPosInX;
			mPos.y = sin(mRad+(90*2*3.14/180)) * mRadius + 300;
		}else if (startFlag == 1){
			//左回転
			mPos.x = sin(mRad+(90*1*3.14/180)) * mRadius + mPosInX - mRadius;
			mPos.y = cos(mRad+(90*1*3.14/180)) * mRadius + 300;
		}
	}else if (mState == 2){
		mV.y = -4;
		
		if(startFlag == 0){
			mV.x = 2;
			
		}else if(startFlag == 1){
			mV.x = -2;
		}
		
		mState = 3;
	}else if (mState == 3){
		if (mPos.y < -50){
			mState = 4;
		}
	}else if (mState == 4){
		return false;
	}
	
	mAngle += mAngleSpeed;
	mCount++;
    return true;
}

*/


/* ============================================================== */
// Enemy1000	ボスキャラ
/* ============================================================== */
Enemy1000::Enemy1000(const GMVector2D& pos, int life, int number , int deadScore ,int item )
: Enemy(pos, life) 
{
	
	mState = 0; 
	mCount = 0;
	mItem = item;
	mDeadScore = (deadScore != -1)? deadScore : life;

	mPos.x = 0;
	mPos.y = 480;
	mV = 0.0;
	mA = 0.0;
	
	
	mAngle = 0.0;
	mAngleSpeed = 0.1;
	
	mCount_temp = 0;
	count_temp = 0;
	
	mSize = GMVector2D(180,180);
    mTex = new GMTexture2D("boss1_0.png");
	mTexLife = new GMTexture2D("LifeGauge.png");
	
	
    if (GMRandom::NextInt(2) == 0) {
        mAngleSpeed *= -1;
    }
}

Enemy1000::~Enemy1000()
{
	delete mTex;
    mTex = NULL;
	delete mTexLife;
	mTexLife = NULL;
	
	gGameInst->mGlobal->setBossFlag(9999);
}

GMRect2D Enemy1000::getDefenceBounds() const
{
    return GMRect2D(mPos.x+20, mPos.y+20, 180 -40, 180-40);
}

void Enemy1000::draw(GMSpriteBatch* batch)
{	
	//ボス表示
	if(mLife < 1000){
		if(mCount % 10 > 5){
			batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::White);
		}else {
			batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::Red);
		}
	}else if(mLife < 2000){
		if(mCount % 20 > 10){
			batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::White);
		}else {
			batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::Red);
		}
	}else if(mLife < 3000){
		if(mCount % 30 > 15){
			batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::White);
		}else {
			batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::Red);
		}
	}else {
		batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::White);
	}
	
	//ライフゲージ
	batch->draw(mTexLife, GMRect2D(10,460,380*((double)mLife/(double)mLifeMax),10), GMColor::Red );
	batch->draw(mTexLife, GMRect2D(380*((double)mLife/(double)mLifeMax)+7,460,3,10), GMColor::Brown );
}


bool Enemy1000::moveImpl(Player *player)
{
	
	
	if(mState == 0){
		mState =1;
	}else if(mState == 1){
		if (movePhysical(200-180/2-(mPos.x), 280-(mPos.y), 60) == true){
			mState = 2;
		}
	}else if(mState == 2){
		mCount_temp++;
		if (mCount_temp > 60){
			mV.x = 3;
			mState = 3;
			mCount_temp = 0;
		}
		if(mCount % 3 == 0){
			setBullet(3,1,12);
		}
		
	}else if(mState == 3){
		if(mPos.x > 400-180){
			mV.x *= -1;
		}else if(mPos.x < 0){
			mV.x = 0;
			mState = 4;
			
		}
		
		if(mPos.x > 50 && mPos.x < 350-180){
			if(mCount % 2 == 0){
				setBullet(4,0,1);
			}
		}
		
	}else if(mState == 4){
		if (movePhysical(200-180/2-(mPos.x), 0, 60) == true){
			count_temp++;
			if(count_temp == 2){
				count_temp=0;
				mState = 5;
			}else {
				mState = 2;
			}
		}
	}else if(mState == 5){
		if (movePhysical(player->getPosX()-(mPos.x) - 180/2 + 16, player->getPosY() - (mPos.y) - 16, 60) == true){
			mState = 6;
		}
	}else if(mState == 6){
		if (movePhysical(200-180/2-(mPos.x), 280 - (mPos.y), 120) == true){
			mState = 5;
			count_temp++;
			if(count_temp == 2){
				count_temp = 0;
				mState = 2;
			}
		}
	}
	
	mCount++;
    return true;
}




