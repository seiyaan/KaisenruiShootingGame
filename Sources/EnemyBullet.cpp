/*
 *  EnemyBullet.cpp
 *  Karakuri2 Mac for Xcode 4
 *
 *  Created by KAI Seiya on 11/12/19.
 *  Copyright 2011 Satoshi Numata. All rights reserved.
 *
 */

#include "Karakuri.h"
#include "EnemyBullet.h"


/* ============================================================== */
// EnemyBullet
/* ============================================================== */
EnemyBullet::EnemyBullet(const GMVector2D& pos) 
:mPos(pos)
{
	mCount	= 0;
	mState	= 0;
}
	
EnemyBullet::~EnemyBullet(){
	//No
}

bool EnemyBullet::move(Player *player)
{
	bool ret = moveImpl(player);
    mV += mA;
    mPos += mV;
    return ret;
}

GMVector2D EnemyBullet::getPos() const{
	return mPos;
}

GMVector2D EnemyBullet::getSize() const{
	return mSize;
}

/* ============================================================== */
// EnemyBulletManager
/* ============================================================== */
EnemyBulletManager::EnemyBulletManager()
{
    // Do nothing
}

EnemyBulletManager::~EnemyBulletManager()
{
	std::list<EnemyBullet *>::iterator it_end = mEnemyBullets.end();
    for (std::list<EnemyBullet *>::iterator it = mEnemyBullets.begin(); it != it_end; it++) {
		delete *it;
    }
}

void EnemyBulletManager::drawAllEnemyBullets(GMSpriteBatch *batch)
{
    std::list<EnemyBullet *>::iterator it_end = mEnemyBullets.end();
    for (std::list<EnemyBullet *>::iterator it = mEnemyBullets.begin(); it != it_end; it++) {
        (*it)->draw(batch);
    }
}

void EnemyBulletManager::moveAllEnemyBullets(Player *player)
{
	
	std::list<EnemyBullet *>::iterator it_end = mEnemyBullets.end();
    for (std::list<EnemyBullet *>::iterator it = mEnemyBullets.begin(); it != it_end;) {
        
		
		if ((*it)->move(player)) {
            it++;
        } else {
            delete *it;
            it = mEnemyBullets.erase(it);
            it_end = mEnemyBullets.end();
        }
    }
}

void EnemyBulletManager::createEnemyBullet(Player* player,GMVector2D pos, int type , int number)
{
	EnemyBullet* eb;
	
	
	if (type == 1) {
		eb = new EnemyBullet1(player, pos, number);
		mEnemyBullets.push_back(eb);
	} else if (type == 2) {
		eb = new EnemyBullet2(player, pos, number);
		mEnemyBullets.push_back(eb);
	} else if (type == 3) {
		eb = new EnemyBullet3(player, pos, number);
		mEnemyBullets.push_back(eb);
	} else if (type == 4) {
		eb = new EnemyBullet4(player, pos, number);
		mEnemyBullets.push_back(eb);
	} else if (type == 5) {
		eb = new EnemyBullet5(player, pos, number);
		mEnemyBullets.push_back(eb);
	} else if (type == 6) {
		eb = new EnemyBullet6(player, pos, number);
		mEnemyBullets.push_back(eb);
	} else if (type == 7) {
		eb = new EnemyBullet7(player, pos, number);
		mEnemyBullets.push_back(eb);
	} else if (type == 8) {
		eb = new EnemyBullet8(player, pos, number);
		mEnemyBullets.push_back(eb);
	}else {
		throw GMException("Invalid enemy type: %d", type);
	}
	
	
}

std::list<EnemyBullet *>* EnemyBulletManager::getEnemyBullets()
{
    return &mEnemyBullets;
}

/* ============================================================== */
// EnemyBullet1
/* ============================================================== */
// 四方八方に撃ってくる 12まで
EnemyBullet1::EnemyBullet1(Player* player,const GMVector2D& pos ,int number)
: EnemyBullet( pos )
{
	mSize = GMVector2D(16,16);
	mTex = new GMTexture2D("enemy_bullet_1.png");
	
	mCount = 0;
	mState = 0;

	mPos = pos - mSize/2;
	mNumber = number;
	mPlayerIniPos = player->getPos();
	
	mRot = (mNumber - 1) * 30; // 角度
	mRad = (mRot-105.0) * M_PI / 180;	//ラジアン
	
	mV.x = cos( mRad ) * 3.0;
	mV.y = sin( mRad ) * 3.0;
	mA = GMVector2D(0,0);
}

EnemyBullet1::~EnemyBullet1()
{
	delete mTex;
	mTex = NULL;
}

GMRect2D EnemyBullet1::getDefenceBounds() const
{
	return GMRect2D(mPos.x,mPos.y,mSize.x,mSize.y);
}

void EnemyBullet1::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::Lime);
}

bool EnemyBullet1::moveImpl(Player *player)
{	
	if(mPos.y < 0-mSize.y || mPos.y > 480+mSize.y || mPos.x < 0-mSize.x || mPos.x > 400+mSize.x){
		return false;
	}
	
	mCount++;
    return true;
}

/* ============================================================== */
// EnemyBullet2
/* ============================================================== */
// 四方八方に撃ってくる 12まで 自機に向かって
EnemyBullet2::EnemyBullet2(Player* player,const GMVector2D& pos  ,int number)
: EnemyBullet( pos )
{
	mSize = GMVector2D(16,16);
	mTex = new GMTexture2D("enemy_bullet_1.png");
	
	mCount = 0;
	mState = 0;
	
	mPos = pos - mSize/2;
	mNumber = number;
	mPlayerIniPos = player->getPos() + mSize/2;
	
	mRot = (mNumber - 1) * 30; // 角度
	if(mPlayerIniPos.x > mPos.x){
		mRad = (mRot-90.0) * M_PI / 180 + atan(fabs(mPlayerIniPos.x - mPos.x)/fabs(mPlayerIniPos.y - mPos.y)) ;	//ラジアン
	}else {
		mRad = (mRot-90.0) * M_PI / 180 - atan(fabs(mPlayerIniPos.x - mPos.x)/fabs(mPlayerIniPos.y - mPos.y)) ;	//ラジアン
	}
	
	mV.x = cos( mRad ) * 3.0;
	mV.y = sin( mRad ) * 3.0;
	mA = GMVector2D(0,0);
}

EnemyBullet2::~EnemyBullet2()
{
	delete mTex;
	mTex = NULL;
}

GMRect2D EnemyBullet2::getDefenceBounds() const
{
	return GMRect2D(mPos.x,mPos.y,mSize.x,mSize.y);
}

void EnemyBullet2::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::White);
}

bool EnemyBullet2::moveImpl(Player *player)
{	
	if(mPos.y < 0-mSize.y || mPos.y > 480+mSize.y || mPos.x < 0-mSize.x || mPos.x > 400+mSize.x){
		return false;
	}
	mCount++;
    return true;
}


/* ============================================================== */
// EnemyBullet3
/* ============================================================== */
// 四方八方に撃ってくる 12まで 速い
EnemyBullet3::EnemyBullet3(Player* player,const GMVector2D& pos ,int number)
: EnemyBullet( pos )
{
	mSize = GMVector2D(16,16);
	mTex = new GMTexture2D("enemy_bullet_1.png");
	
	mCount = 0;
	mState = 0;
	
	mPos = pos - mSize/2;
	mNumber = number;
	mPlayerIniPos = player->getPos();
	
	mRot = (mNumber - 1) * 30; // 角度
	mRad = (mRot-105.0) * M_PI / 180;	//ラジアン
	
	mV.x = cos( mRad ) * 5.0;
	mV.y = sin( mRad ) * 5.0;
	mA = GMVector2D(0,0);
}

EnemyBullet3::~EnemyBullet3()
{
	delete mTex;
	mTex = NULL;
}

GMRect2D EnemyBullet3::getDefenceBounds() const
{
	return GMRect2D(mPos.x,mPos.y,mSize.x,mSize.y);
}

void EnemyBullet3::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::White);
}

bool EnemyBullet3::moveImpl(Player *player)
{	
	if(mPos.y < 0-mSize.y || mPos.y > 480+mSize.y || mPos.x < 0-mSize.x || mPos.x > 400+mSize.x){
		return false;
	}
	
	mCount++;
    return true;
}

/* ============================================================== */
// EnemyBullet4
/* ============================================================== */
// 1つ撃ってくる 
EnemyBullet4::EnemyBullet4(Player* player,const GMVector2D& pos  ,int number)
: EnemyBullet( pos )
{
	mSize = GMVector2D(16,16);
	mTex = new GMTexture2D("enemy_bullet_1.png");
	
	mCount = 0;
	mState = 0;
	
	mPos = pos - mSize/2;
	mNumber = number;
	mPlayerIniPos = player->getPos() + mSize/2;
	
	mV.x = 0.0;
	mV.y = -3.0;
	mA = GMVector2D(0,0);
}

EnemyBullet4::~EnemyBullet4()
{
	delete mTex;
	mTex = NULL;
}

GMRect2D EnemyBullet4::getDefenceBounds() const
{
	return GMRect2D(mPos.x,mPos.y,mSize.x,mSize.y);
}

void EnemyBullet4::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::Red);
}

bool EnemyBullet4::moveImpl(Player *player)
{	
	
	if( mPos.y < 0-mSize.y || mPos.y > 480+mSize.y || mPos.x < 0-mSize.x || mPos.x > 400+mSize.x){
		return false;
	}
	
	
	mCount++;
    return true;
}
/* ============================================================== */
// EnemyBullet5
/* ============================================================== */
// 自機に向かって撃ってくる 1つ
EnemyBullet5::EnemyBullet5(Player* player,const GMVector2D& pos  ,int number)
: EnemyBullet( pos )
{
	mSize = GMVector2D(16,16);
	mTex = new GMTexture2D("enemy_bullet_1.png");
	
	mCount = 0;
	mState = 0;
	
	mPos = pos - mSize/2;
	mNumber = number;
	mPlayerIniPos = player->getPos() + mSize/2;
	
	mRot = 0; // 角度
	if(mPlayerIniPos.x > mPos.x){
		mRad = (mRot-90.0) * M_PI / 180 + atan(fabs(mPlayerIniPos.x - mPos.x)/fabs(mPlayerIniPos.y - mPos.y)) ;	//ラジアン
	}else {
		mRad = (mRot-90.0) * M_PI / 180 - atan(fabs(mPlayerIniPos.x - mPos.x)/fabs(mPlayerIniPos.y - mPos.y)) ;	//ラジアン
	}
	
	mV.x = cos( mRad ) * 3.0;
	mV.y = sin( mRad ) * 3.0;
	mA = GMVector2D(0,0);
}

EnemyBullet5::~EnemyBullet5()
{
	delete mTex;
	mTex = NULL;
}

GMRect2D EnemyBullet5::getDefenceBounds() const
{
	return GMRect2D(mPos.x,mPos.y,mSize.x,mSize.y);
}

void EnemyBullet5::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::Red);
}

bool EnemyBullet5::moveImpl(Player *player)
{	
	
	if( mPos.y < 0-mSize.y || mPos.y > 480+mSize.y || mPos.x < 0-mSize.x || mPos.x > 400+mSize.x){
		return false;
	}
	
	
	mCount++;
    return true;
}

/* ============================================================== */
// EnemyBullet6
/* ============================================================== */
// 1つ撃ってくる 加速度あり
EnemyBullet6::EnemyBullet6(Player* player,const GMVector2D& pos  ,int number)
: EnemyBullet( pos )
{
	mSize = GMVector2D(16,16);
	mTex = new GMTexture2D("enemy_bullet_1.png");
	
	mCount = 0;
	mState = 0;
	
	mPos = pos - mSize/2;
	mNumber = number;
	mPlayerIniPos = player->getPos() + mSize/2;
	
	mV.x = 0.0;
	mV.y = -3.0;
	mA = GMVector2D(0,-0.05);
}

EnemyBullet6::~EnemyBullet6()
{
	delete mTex;
	mTex = NULL;
}

GMRect2D EnemyBullet6::getDefenceBounds() const
{
	return GMRect2D(mPos.x,mPos.y,mSize.x,mSize.y);
}

void EnemyBullet6::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::Red);
}

bool EnemyBullet6::moveImpl(Player *player)
{	
	
	if( mPos.y < 0-mSize.y || mPos.y > 480+mSize.y || mPos.x < 0-mSize.x || mPos.x > 400+mSize.x){
		return false;
	}
	
	mCount++;
    return true;
}

/* ============================================================== */
// EnemyBullet7
/* ============================================================== */
// 自機に向かって撃ってくる 1つ 加速度あり
EnemyBullet7::EnemyBullet7(Player* player,const GMVector2D& pos  ,int number)
: EnemyBullet( pos )
{
	mSize = GMVector2D(16,16);
	mTex = new GMTexture2D("enemy_bullet_1.png");
	
	mCount = 0;
	mState = 0;
	
	mPos = pos - mSize/2;
	mNumber = number;
	mPlayerIniPos = player->getPos() + mSize/2;
	
	mRot = 0; // 角度
	if(mPlayerIniPos.x > mPos.x){
		mRad = (mRot-90.0) * M_PI / 180 + atan(fabs(mPlayerIniPos.x - mPos.x)/fabs(mPlayerIniPos.y - mPos.y)) ;	//ラジアン
	}else {
		mRad = (mRot-90.0) * M_PI / 180 - atan(fabs(mPlayerIniPos.x - mPos.x)/fabs(mPlayerIniPos.y - mPos.y)) ;	//ラジアン
	}
	
	mV.x = cos( mRad ) * 3.0;
	mV.y = sin( mRad ) * 3.0;
	mA = GMVector2D(cos( mRad )*0.05 ,sin( mRad )*0.05);
}

EnemyBullet7::~EnemyBullet7()
{
	delete mTex;
	mTex = NULL;
}

GMRect2D EnemyBullet7::getDefenceBounds() const
{
	return GMRect2D(mPos.x,mPos.y,mSize.x,mSize.y);
}

void EnemyBullet7::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos, GMRect2D::Empty, GMColor::Yellow);
}

bool EnemyBullet7::moveImpl(Player *player)
{	
	
	if( mPos.y < 0-mSize.y || mPos.y > 480+mSize.y || mPos.x < 0-mSize.x || mPos.x > 400+mSize.x){
		return false;
	}
	
	
	mCount++;
    return true;
}


/* ============================================================== */
// EnemyBullet8
/* ============================================================== */
// わさび用
EnemyBullet8::EnemyBullet8(Player* player,const GMVector2D& pos  ,int number)
: EnemyBullet( pos )
{
	mSize = GMVector2D(20,20);
	mTex = new GMTexture2D("enemy_bullet_2.png");
	
	mCount = 0;
	mState = 0;
	
	if(pos.x < 200 ){
		mV.x = 4;
	}else {
		mV.x = -4;
	}
	
	mPos = pos - mSize/2;
	mNumber = number;
	mRot = 0; // 角度
	
	mV.y = -1.0;
	mA = GMVector2D::Zero;
}

EnemyBullet8::~EnemyBullet8()
{
	delete mTex;
	mTex = NULL;
}

GMRect2D EnemyBullet8::getDefenceBounds() const
{
	return GMRect2D(mPos.x,mPos.y,mSize.x,mSize.y);
}

void EnemyBullet8::draw(GMSpriteBatch* batch)
{
    batch->draw(mTex, mPos, GMColor::White);
}

bool EnemyBullet8::moveImpl(Player *player)
{	
	
	if(mPos.x+mSize.x < 0 || mPos.x > 400){
		return false;
	}
	
	
	mCount++;
    return true;
}

