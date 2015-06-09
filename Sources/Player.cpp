//
//  Player.cpp
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/04.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//


#include "Player.h"
#include "GameMain.h"



Player::Player(int type)
: mType(type)
{

	//mTex = new GMTexture2D(GMFS("player%d.png", mType));
	if(mType == 1){
		mTex = new GMTexture2D("player1_tako.png");
	}else if(mType == 2){
		mTex = new GMTexture2D("player3_uni.png");
	}else if(mType == 3){
		mTex = new GMTexture2D("player2_ika.png");
	}
    
	mTexDeadEffect = new GMTexture2D("player_deadeffect.png");
	
    mPos = GMVector2D((400-37)/2, -mSize.y);
	mSize = GMVector2D(36,36);
	
    mAnimationCount = 0;
    mCount = 0;
	mCount_temp = 0;
	mStatus = 10;
	mNodamageFlag = 1;
	mDeadEffectFlag = 0;
	mDeadEffectCount = 0;
	mDeadEffectPos = GMVector2D(0,0);
	mOptionCount = 0;
	
	
	gGameInst->mOwn->setMyPower(1.0);
	addOptionCount();

}

Player::~Player()
{
    delete mTex;
    mTex = NULL;
	
	delete mTexDeadEffect;
	mTexDeadEffect = NULL;
	
	std::list<Option *>::iterator it_end = mOptions.end();
    for (std::list<Option *>::iterator it = mOptions.begin(); it != it_end; it++) {
        delete *it;
    }
    mOptions.clear();
}

//アイテム取得時の処理
void Player::UpGrade(int type){	
	if(type == 1){									//点
		gGameInst->mScore->addCurrentScore(1000);
	}else if(type == 2){							//P
		gGameInst->mOwn->addMyPower(0.05);
		setOptionCount((int)gGameInst->mOwn->getMyPower());
	}else if(type == 3){							//B
		gGameInst->mOwn->addMyBoms(0.25);
	}
}

//プレイヤー初期化
void Player::resetStatus(){
	mDeadEffectPos = mPos + mSize/2;
	mStatus = 10;
	mPos = GMVector2D((400-37)/2, -mSize.y);
	mNodamageFlag = 1;
	mDeadEffectFlag = 1;
}


void Player::draw(GMSpriteBatch* batch)
{
    int index = (mAnimationCount / 8) % 3;
    int status = (mStatus < 10)? mStatus: 0;
	
	
	
	if(mNodamageFlag == 0){
		//自機が普通の時
		if(status == 0){
			batch->draw(mTex, mPos, GMRect2D((index+status*3)*37, 0, 37, 36));		
		}else{
			batch->draw(mTex, mPos, GMRect2D((2+status)*37, 0, 37, 36));
		}
	}else {
		//プレイヤー死亡後の無敵状態
		if(status == 0){
			if(mCount % 15 > 5){
				batch->draw(mTex, mPos, GMRect2D((index+status*3)*37, 0, 37, 36), GMColor::Blue);	
			}else {
				batch->draw(mTex, mPos, GMRect2D((index+status*3)*37, 0, 37, 36), GMColor::White);
			}
		}else{
			if(mCount % 15 > 5){
				batch->draw(mTex, mPos, GMRect2D((2+status)*37, 0, 37, 36),GMColor::Blue);
			}else {
				batch->draw(mTex, mPos, GMRect2D((2+status)*37, 0, 37, 36),GMColor::White);
			}
		}
	}
	
	
	//自機が死亡した時のEffect
	if(mDeadEffectFlag == 1){
		if(mDeadEffectCount > 60){
			mDeadEffectCount = 0;
			mDeadEffectFlag = 0;
		}else {
			mDeadEffectCount++;
			batch->draw(mTexDeadEffect, mDeadEffectPos , GMRect2D::Empty , GMColor(GMVector4D(1.0,1.0,1.0,1.0-((double)mDeadEffectCount/60.0))), 0.0 , GMVector2D(25, 25) , GMVector2D(mDeadEffectCount,mDeadEffectCount),GMSpriteFlipNone,0.0);
		}
	}
	
	
	
	for (std::list<Option*>::iterator it = mOptions.begin(), itEnd = mOptions.end(); it != itEnd;) {
		if((*it) != NULL ){
			(*it)->draw(batch);
			it++;
		}else {
            delete *it;
            it = mOptions.erase(it);
            itEnd = mOptions.end();
        }
	}
}


void Player::move(GMInput* input)
{
	mCount++; 
    // ゲーム開始時の出現アニメーション
    if (mStatus == 10) {
        mPos.y += 0.5;
        if (mPos.y > 40) {
            mPos.y = 40;
            mStatus = 0;
			mCount_temp = mCount;
			mNodamageFlag = 2;	//出現後無敵時間を与える
        }
        return;
    }
	
	//自機が死亡したあとの無敵時間管理
	if(mNodamageFlag == 2){
		if(mCount_temp+60 < mCount){
			mNodamageFlag = 0;
		}
	}
	
	//Sキーを押すと無敵になる もしくは 無敵解除
	if(input->isKeyDownTriggered(GMKeyMaskS)){
		if(mNodamageFlag != 999){
			mNodamageFlag = 999;
		}else {
			mNodamageFlag = 0;
		}
	}
	
	
    // キーボード状態チェック
    bool left	= input->isKeyDown(GMKeyMaskLeft);
    bool right	= input->isKeyDown(GMKeyMaskRight);
    bool up		= input->isKeyDown(GMKeyMaskUp);
    bool down	= input->isKeyDown(GMKeyMaskDown);
	
	
	
    // スピード調整
    double speed = 4.5;
    if ((up ^ down) && (left ^ right)) {
        speed *= 0.62;//0.7071; // 飛行機が斜めに速く進めるということは原理的にないので、少し遅めに設定する。
    }
    if (input->isKeyDown(GMKeyMaskShift)) {
        speed *= 0.4;
		
    }
	
	
    // 縦の移動
    if (input->isKeyDown(GMKeyMaskUp)) {
        mPos.y += speed;
    }
    if (input->isKeyDown(GMKeyMaskDown)) {
        mPos.y -= speed;
    }
	

    // 横の移動
    if (left && !right) {
        mPos.x -= speed;
        if (mStatus != 1 && mStatus != 2) {
            mStatusCount = 14;
            mStatus = 1;
        }
    } else if (right && !left) {
        mPos.x += speed;
        if (mStatus != 3 && mStatus != 4) {
            mStatusCount = 14;
            mStatus = 3;
        }
    } else {
        mStatus = 0;
    }
	
	

	
    // 横移動のアニメーション遷移
    if (mStatus == 1 || mStatus == 3) {
        mStatusCount--;
        if (mStatusCount == 0) {
            mStatus += 1;
        }
    }
	

	
    
    // 移動可能範囲の制限
	
    if (mPos.x < -18) {
        mPos.x = -18;
    } else if (mPos.x > 400-19) {
        mPos.x = 400-19;
    }
    
    if (mPos.y < 0) {
        mPos.y = 0;
    } else if (mPos.y > 480-36) {
        mPos.y = 480-36;
    }
	
	
	if(mNodamageFlag == 0  || mNodamageFlag == 999){
		int number=0;
		for (std::list<Option*>::iterator it = mOptions.begin(), itEnd = mOptions.end(); it != itEnd;) {
			if((*it) != NULL ){
				(*it)->move(input,number);
				it++;
				number++;
			}else {
				delete *it;
				it = mOptions.erase(it);
				itEnd = mOptions.end();
			}
		}
	}
	// アニメーション用カウンタ
    mAnimationCount++;
}

void Player::addOptionCount()
{
	if(mOptionCount < 5){
		Option* op1 = new Option(this , mType);
		mOptions.push_back(op1);
		mOptionCount += 1;
	}
}
void Player::removeOptionCount(){
	if(mOptionCount > 0){
		mOptions.pop_back();
		mOptionCount -= 1;
	}
}
void Player::setOptionCount(int inValue){
	if(mOptionCount < inValue){
		for ( int i = 0 ; i < inValue - mOptionCount ; i++){
			addOptionCount();
		}
	} else if (mOptionCount > inValue ){
		for ( int i = 0 ; i < mOptionCount - inValue ; i++){
			removeOptionCount();
		}
	} 
}

Option* Player::getOption(int index)
{
	std::list<Option*>::iterator it = mOptions.begin();
	advance( it, index );
	return *it;
}


GMRect2D Player::getDefenceBounds() const
{
	return GMRect2D(mPos.x+15,mPos.y+15,mSize.x-30,mSize.y-30); 
}

int	Player::getStatus()	const
{
	return mStatus; 
}



double Player::getAnimationCountToAngle() const
{
	return (double)mAnimationCount * 1.0; 
}

int	Player::getOptionCount() const
{
	return mOptionCount;
}

GMVector2D Player::getPos() const 
{
	return mPos; 
}

double Player::getPosX() const 
{
	return (double)mPos.x; 
}

double Player::getPosY() const 
{ 
	return (double)mPos.y; 
}

GMVector2D Player::getSize() const
{
	return mSize;
}

int Player::getNoDamageFlag() const
{
	return mNodamageFlag;
}


/* ============================================================== */
// Option
/* ============================================================== */


GMTexture2D *gOptionTex = NULL;
Option::Option (Player *player ,int type)
{
	
	mParentPlayer = player;
	mType = type;
	
	mPos = GMVector2D(999,999);
	
	mAngle = 0.0;
	mAngleSpeed = 0.1;
    if (GMRandom::NextInt(2) == 0) {
        mAngleSpeed *= -1;
    }
	
	
	rot = 0;	// 円の角度(0 ～ 360)
	rot_speed = 5;	// 円の角度変化量(0 ～ 360)
	radius = 50;	// 円の半径
	rad = 0;
	
	
	
	
	if(type == 1){
		if(gOptionTex == NULL){
			gOptionTex = new GMTexture2D("option_takoyaki.png");
		}
	} else if (type == 2){
		if(gOptionTex == NULL){
			gOptionTex = new GMTexture2D("option_takoyaki.png");
		}	
	} else if (type == 3){
		if(gOptionTex == NULL){
			gOptionTex = new GMTexture2D("option_takoyaki.png");
		}
	} else {
		throw GMException("Invalid Option Type : %d", type);	//例外処理 デバックしやすく
	}
}

Option::~Option()
{
	// Do nothing
}
bool Option::move(GMInput* input,int number)
{
	mAngle += mAngleSpeed;
	rot = mParentPlayer->getAnimationCountToAngle()*5;	// 角度を変化させる
	
	rad = rot * 3.14 / 180;	// 角度からラジアンに変換する
	
	if (input->isKeyDown(GMKeyMaskShift)) {
		radius -= 1.5;		
		if(radius < 26){
			radius = 26;
		}
    } else {
		radius += 1.5;
		if(radius > 50){
			radius = 50;
		}
	}
	
	if(mParentPlayer->getOptionCount() == 0){
		//Nothing
	}else if(mParentPlayer->getOptionCount() == 1){
		mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad)*radius) + 6, (cos(rad)*radius)+6 );   
	}else if(mParentPlayer->getOptionCount() == 2){
		if(number == 0){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad)*radius) + 6, (cos(rad)*radius)+6 );   
		} else if (number == 1){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad + 180*3.14/180)*radius) + 6 ,(cos(rad + 180*3.14/180)*radius) + 6);   
		}
	}else if(mParentPlayer->getOptionCount() == 3){
		if(number == 0){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad)*radius) + 6, (cos(rad)*radius)+6 );   
		} else if (number == 1){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad + 120*3.14/180)*radius) + 6 ,(cos(rad + 120*3.14/180)*radius) + 6);   
		} else if (number == 2){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad + 240*3.14/180)*radius) + 6 ,(cos(rad + 240*3.14/180)*radius) + 6);   
		}
	}else if(mParentPlayer->getOptionCount() == 4){
		if(number == 0){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad)*radius) + 6, (cos(rad)*radius)+6 );   
		} else if (number == 1){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad + 90*3.14/180)*radius) + 6 ,(cos(rad + 90*3.14/180)*radius) + 6);   
		} else if (number == 2){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad + 180*3.14/180)*radius) + 6 ,(cos(rad + 180*3.14/180)*radius) + 6);   
		} else if (number == 3){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad + 270*3.14/180)*radius) + 6 ,(cos(rad + 270*3.14/180)*radius) + 6);   
		}
	}else if(mParentPlayer->getOptionCount() == 5){
		if(number == 0){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad)*radius) + 6, (cos(rad)*radius)+6 );   
		} else if (number == 1){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad + 72*3.14/180)*radius) + 6 ,(cos(rad + 72*3.14/180)*radius) + 6);   
		} else if (number == 2){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad + 144*3.14/180)*radius) + 6 ,(cos(rad + 144*3.14/180)*radius) + 6);   
		} else if (number == 3){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad + 216*3.14/180)*radius) + 6 ,(cos(rad + 216*3.14/180)*radius) + 6);   
		} else if (number == 4){
			mPos = mParentPlayer->getPos() + GMVector2D( (sin(rad + 288*3.14/180)*radius) + 6 ,(cos(rad + 288*3.14/180)*radius) + 6);   
		}
	}
	
	return true;
}
void Option::draw(GMSpriteBatch *batch)
{
	//自機が出てくるときは描画しない
	if(mParentPlayer->getNoDamageFlag() == 0 || mParentPlayer->getNoDamageFlag() == 999){
		batch->draw(gOptionTex, mPos , GMRect2D::Empty, GMColor::White );
	}
}

GMVector2D Option::getPos() const
{
    return mPos;
}

