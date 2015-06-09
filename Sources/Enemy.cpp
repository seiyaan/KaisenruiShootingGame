//
//  Enemy.cpp
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/21.
//  Copyright 2011 Satoshi Numata. All rights reserved.
//

#include "Enemy.h"
#include "Enemy1.h"


static GMSound* sHitSound = NULL;


/* ============================================================== */
// Enemy
/* ============================================================== */
Enemy::Enemy(const GMVector2D& pos, int life )
    : mPos(pos), mLife(life) , mLifeMax(life)
{
    if (sHitSound == NULL) {
        sHitSound = new GMSound("enemy_damage.aif");
        sHitSound->setVolume(0.7);
    }
	
	mBulletType1 = 0;
	mBulletType2 = 0;
	phyFlag = 0;
}

Enemy::~Enemy()
{
	//No
}

bool Enemy::move(Player *player)
{
    bool ret = moveImpl(player);
    
    mV += mA;
    mPos += mV;
    
    return ret;
}

GMVector2D Enemy::getPos() const
{
    return mPos;
}

GMVector2D Enemy::getSize() const
{
	return mSize;
}

bool Enemy::isDead() const
{
	if(mLife <= 0){
		gGameInst->mScore->addCurrentScore(mDeadScore);		//点数を追加
		return true;	//死んだ
	}else {
		return false;	//生きてる
	}
}

int Enemy::isItem() const
{
	return mItem;
}

int Enemy::getBulletType1() const
{
	return mBulletType1;
}

int Enemy::getBulletType2() const
{
	return mBulletType2;
}

int Enemy::getBulletNumber() const
{
	return mBulletNumber;
}

void Enemy::setBullet(int type1, int type2 ,int number)
{
	mBulletType1 = type1;
	mBulletType2 = type2;
	mBulletNumber = number;
}


void Enemy::decreaseLife(int power)
{
    mLife -= power;
    //sHitSound->play();
	
}

bool Enemy::movePhysical(double maxPosX,double maxPosY,int maxT){
	// movePyhsical(X移動値,Y移動値,移動に所要する時間){}
	
	
	if (phyFlag == 0){
		phyPrePos.x = mPos.x;
		phyPrePos.y = mPos.y;
		phyPreT = mCount;
		phyMaxPos.x = maxPosX;
		phyMaxPos.y = maxPosY;
		phyFlag = 1;
	}
	
	phyNowT = mCount - phyPreT;
	
	phyA.x = 2*phyMaxPos.x / (maxT * maxT);
	phyA.y = 2*phyMaxPos.y / (maxT * maxT);
	
	phyVo.x = 2*phyMaxPos.x / maxT;
	phyVo.y = 2*phyMaxPos.y / maxT;
	
	
	
	
	mPos.x = phyPrePos.x + phyVo.x*phyNowT - 0.5*phyA.x*(phyNowT*phyNowT);
	mPos.y = phyPrePos.y + phyVo.y*phyNowT - 0.5*phyA.y*(phyNowT*phyNowT);

	
	if(phyNowT == maxT){
		phyFlag = 0;
		return true;
	}else {
		return false; 
	}
}


/* ============================================================== */
// EnemyGenerator
/* ============================================================== */

EnemyGenerator::EnemyGenerator()
{
    mFrameCount = 0;
    mCurrentPos = 0;
}

EnemyGenerator::~EnemyGenerator()
{
    // Do nothing
}

void EnemyGenerator::loadEnemyAppearances(int stage)
{
	
    if (stage == 1) {
		
		/*addEnemyAppearance(t ,type ,item,   X,	  Y,   体力, n,score ) */
		
		//マグロ
		addEnemyAppearance(5*60,	4, 	2,	  60,	480,	10, 8,	-1);
		addEnemyAppearance(10*60,	4, 	2,340-58,	480,	10, 8,	-1);
		addEnemyAppearance(17*60,	5, 	2,	  60,	480,	10, 8,	-1);
		addEnemyAppearance(22*60,	5, 	2,340-58,	480,	10, 8,	-1);
		
		//プリン
		addEnemyAppearance(30*60,	2, 	2,	286,	480,    60, 1,	20000);
		addEnemyAppearance(30*60,	2, 	2,	 60,	480,    60, 1,	20000);
		addEnemyAppearance(36*60,	2, 	2,	286,	480,    60, 1,	20000);
		addEnemyAppearance(36*60,	2, 	2,	 60,	480,    60, 1,	20000);
		
		//お茶
		addEnemyAppearance(42*60,	0, 	2,	  0,	480,	10, 8,	-1);
		addEnemyAppearance(48*60,	0, 	2,	400,	480,	10, 8,	-1);
		
		//卵
		addEnemyAppearance(54*60,	6, 	1,	400,	400,	2, 8,	-1);
		addEnemyAppearance(54*60,	6, 	2,	-58,	400,	2, 8,	-1);
		
		//数の子
		addEnemyAppearance(58*60,	7, 	1,	400,	400,	2, 8,	-1);
		addEnemyAppearance(58*60,	7, 	2,	-58,	400,	2, 8,	-1);
		
		
		//卵
		addEnemyAppearance(62*60,	6, 	1,	400,	400,	2, 8,	-1);
		addEnemyAppearance(62*60,	6, 	2,	-58,	400,	2, 8,	-1);
		addEnemyAppearance(62*60,	6, 	1,	400,	250,	2, 8,	-1);
		addEnemyAppearance(62*60,	6, 	2,	-58,	250,	2, 8,	-1);
		
		//数の子&卵
		addEnemyAppearance(66*60,	6, 	1,	400,	400,	2, 4,	-1);
		addEnemyAppearance(66*60,	6, 	2,	-58,	400,	2, 4,	-1);
		addEnemyAppearance(66*60,	7, 	1,	510,	400,	2, 4,	-1);
		addEnemyAppearance(66*60,	7, 	2, -168,	400,	2, 4,	-1);
		addEnemyAppearance(66*60,	6, 	1,	400,	250,	2, 4,	-1);
		addEnemyAppearance(66*60,	6, 	2,	-58,	250,	2, 4,	-1);
		addEnemyAppearance(66*60,	7, 	1,	510,	250,	2, 4,	-1);
		addEnemyAppearance(66*60,	7, 	2, -168,	250,	2, 4,	-1);
		
		//わさび&ほたて
		addEnemyAppearance(67*60,	8, 	2,  -37,	520,   10, 1,	-1);
		
		addEnemyAppearance(68*60,	9, 	2,   75,	480,   50, 3,	-1);
		addEnemyAppearance(68*60,	8, 	2,400-60,	520,   10, 1,	-1);
		
		addEnemyAppearance(69*60,	9, 	2,   75,	480,   50, 3,	-1);
		addEnemyAppearance(69*60,	8, 	2,  -37,	520,   10, 1,	-1);
		
		//ボス(板前)
		addEnemyAppearance(79*60,1000,	1,	140,	480,12000,	1,	120000);
		
		/*
		addEnemyAppearance(4*60,	0, 	2,	  0,	480,	10, 8,	-1);
		
		addEnemyAppearance(11*60,	2, 	2,	286,	480,    80, 1,	20000);
		addEnemyAppearance(11*60,	2, 	2,	 60,	480,    80, 1,	20000);
		addEnemyAppearance(11*60,	1, 	1,	  5,	480,	10, 5,	-1);
		
		addEnemyAppearance(18*60,	2, 	2,	286,	480,    80, 1,	20000);
		addEnemyAppearance(18*60,	2, 	2,	 60,	480,    80, 1,	20000);
		addEnemyAppearance(18*60,	1, 	2,	363,	480,	10, 5,	-1);

		addEnemyAppearance(25*60,	3, 	2,	  0,	480,	10, 8,	-1);
		addEnemyAppearance(32*60,	3, 	2,	400,	480,	10, 8,	-1);
		
		addEnemyAppearance(40*60,1000,	1,	140,	480,  2000,	1,	120000);
		 */
    }
    
    mFrameCount = 0;
    if (mAppearances.empty()) {
        throw GMException("No Enemy Data has been loaded for stage %d", stage);
    }

    mCurrentPos = 0;
    mNextAppearance = mAppearances[mCurrentPos++];
}

void EnemyGenerator::addEnemyAppearance(int frame, int type, int itemType, int x, int y, int life, int size ,int score)
{
    EnemyAppearance info;
    info.frame = frame;
    info.type = type;
    info.x = x;
    info.y = y;
    info.life = life;
    info.size = size;
	info.deadScore = score;
	
	info.itemType = itemType;
    mAppearances.push_back(info);
}

Enemy* EnemyGenerator::createEnemy(EnemyAppearance* info, int number)
{
    GMVector2D pos(info->x, info->y);
    
	if (info->type == 1000){
		gGameInst->mGlobal->setBossFlag(1);
	}
	
    /* 学生の方へ：敵のクラスを追加するたびに、敵のインスタンスを new するコードを書いてください。 */
    if (info->type == 0) {
        return new Enemy0(pos, info->life, number , info->deadScore , info->itemType );
	} else if (info->type == 1) {
        return new Enemy1(pos, info->life, number , info->deadScore , info->itemType );
    } else if (info->type == 2) {
        return new Enemy2(pos, info->life, number , info->deadScore , info->itemType );
    }else if (info->type == 3) {
        return new Enemy3(pos, info->life, number , info->deadScore , info->itemType );
    }else if (info->type == 4) {
        return new Enemy4(pos, info->life, number , info->deadScore , info->itemType );
    }else if (info->type == 5) {
        return new Enemy5(pos, info->life, number , info->deadScore , info->itemType );
    }else if (info->type == 6) {
        return new Enemy6(pos, info->life, number , info->deadScore , info->itemType );
    }else if (info->type == 7) {
        return new Enemy7(pos, info->life, number , info->deadScore , info->itemType );
    }else if (info->type == 8) {
        return new Enemy8(pos, info->life, number , info->deadScore , info->itemType );
    }else if (info->type == 9) {
        return new Enemy9(pos, info->life, number , info->deadScore , info->itemType );
    }else if (info->type == 1000) {
        return new Enemy1000(pos, info->life, number , info->deadScore , info->itemType );
    }else {
        throw GMException("Invalid enemy type: %d (frame=%d)", info->type, info->frame);
    }
}

void EnemyGenerator::generateEnemies(std::list<Enemy *> *enemies)
{
    // 出現する敵がもういない
    if (mNextAppearance.x > 9999) {
        return;
    }
    
    if (mFrameCount >= mNextAppearance.frame) {
        for (int i = 0; i < mNextAppearance.size; i++) {
            Enemy *enemy = createEnemy(&mNextAppearance, i);
            enemies->push_back(enemy);
        }
        if (mCurrentPos >= mAppearances.size()) {
            mNextAppearance.x = 10000;
        } else {
            mNextAppearance = mAppearances[mCurrentPos++];
        }
    }
	
	mFrameCount++;
}





/* ============================================================== */
// EnemyManager
/* ============================================================== */
EnemyManager::EnemyManager()
{
    // Do nothing
}

EnemyManager::~EnemyManager()
{
    std::list<Enemy *>::iterator it_end = mEnemies.end();
    for (std::list<Enemy *>::iterator it = mEnemies.begin(); it != it_end; it++) {
        delete *it;
    }
    mEnemies.clear();
}

void EnemyManager::loadEnemyAppearances(int stage)
{
    mEnemyGenerator.loadEnemyAppearances(stage);
}

void EnemyManager::generateEnemies()
{
    mEnemyGenerator.generateEnemies(&mEnemies);
}

void EnemyManager::drawAllEnemies(GMSpriteBatch *batch)
{
    std::list<Enemy *>::iterator it_end = mEnemies.end();
    for (std::list<Enemy *>::iterator it = mEnemies.begin(); it != it_end; it++) {
        (*it)->draw(batch);
    }
}

void EnemyManager::moveAllEnemies(Player *player)
{
	
    std::list<Enemy *>::iterator it_end = mEnemies.end();
    for (std::list<Enemy *>::iterator it = mEnemies.begin(); it != it_end;) {
        if ((*it)->move(player)) {
            it++;
        } else {
            delete *it;
            it = mEnemies.erase(it);
            it_end = mEnemies.end();
        }
    }
}

std::list<Enemy *>* EnemyManager::getEnemies()
{
    return &mEnemies;
}



