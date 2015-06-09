/*
 *  EnemyBullet.h
 *  Karakuri2 Mac for Xcode 4
 *
 *  Created by KAI Seiya on 11/12/19.
 *  Copyright 2011 Satoshi Numata. All rights reserved.
 *
 */

#ifndef __ENEMY_BULLET_H__
#define __ENEMY_BULLET_H__

#include "Karakuri.h"
#include "Player.h"


/* ============================================================== */
// EnemyBullet
/* ============================================================== */
class EnemyBullet {
	
protected:
	
    int			mCount;
	int			mState;

	
	GMVector2D	mPos;
	GMVector2D	mPlayerIniPos;
	GMVector2D	mV;
    GMVector2D	mA;
	double		mAngle;
    double		mAngleSpeed;
	int			mNumber;
	GMVector2D	mEnemySize;
	GMVector2D	mSize;
	
	double		mRad;	//ラジアン
	double		mRot;	//角度
	
	
public:
    EnemyBullet(const GMVector2D& pos);
    virtual ~EnemyBullet();
	
public:
	virtual GMRect2D    getDefenceBounds() const = 0;
	virtual void    draw(GMSpriteBatch* batch) = 0;
	bool	move(Player *player);
	virtual bool    moveImpl(Player *player)  = 0;;
	
    GMVector2D	getPos() const;
	GMVector2D	getSize() const;

	
};


/* ============================================================== */
// EnemyBulletManager
/* ============================================================== */
class EnemyBulletManager{
	std::list<EnemyBullet*>	mEnemyBullets;
	
public:
	EnemyBulletManager();
	virtual ~EnemyBulletManager();
	
	void	createEnemyBullet(Player* player,GMVector2D pos, int type , int number);
	
	void	drawAllEnemyBullets(GMSpriteBatch *batch);
	void	moveAllEnemyBullets(Player *player);
	
	void	addEnemyBulletAppearance(int type,int x, int y);
	std::list<EnemyBullet *>* getEnemyBullets();
};





/* ============================================================== */
// EnemyBullet1
/* ============================================================== */
class EnemyBullet1 : public EnemyBullet{
    GMTexture2D*    mTex;

public:
    EnemyBullet1(Player* player,const GMVector2D& pos , int number );
    virtual ~EnemyBullet1();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
	virtual bool    moveImpl(Player *player);
	
};
/* ============================================================== */
// EnemyBullet2
/* ============================================================== */
class EnemyBullet2 : public EnemyBullet{
    GMTexture2D*    mTex;
	
public:
    EnemyBullet2(Player* player,const GMVector2D& pos , int number );
    virtual ~EnemyBullet2();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
	virtual bool    moveImpl(Player *player);
	
};
/* ============================================================== */
// EnemyBullet3
/* ============================================================== */
class EnemyBullet3 : public EnemyBullet{
    GMTexture2D*    mTex;
	
public:
    EnemyBullet3(Player* player,const GMVector2D& pos , int number );
    virtual ~EnemyBullet3();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
	virtual bool    moveImpl(Player *player);
	
};
/* ============================================================== */
// EnemyBullet4
/* ============================================================== */
class EnemyBullet4 : public EnemyBullet{
    GMTexture2D*    mTex;
	
public:
    EnemyBullet4(Player* player,const GMVector2D& pos , int number );
    virtual ~EnemyBullet4();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
	virtual bool    moveImpl(Player *player);
	
};
/* ============================================================== */
// EnemyBullet5
/* ============================================================== */
class EnemyBullet5 : public EnemyBullet{
    GMTexture2D*    mTex;
	
public:
    EnemyBullet5(Player* player,const GMVector2D& pos , int number );
    virtual ~EnemyBullet5();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
	virtual bool    moveImpl(Player *player);
	
};

/* ============================================================== */
// EnemyBullet6
/* ============================================================== */
class EnemyBullet6 : public EnemyBullet{
    GMTexture2D*    mTex;
	
public:
    EnemyBullet6(Player* player,const GMVector2D& pos , int number );
    virtual ~EnemyBullet6();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
	virtual bool    moveImpl(Player *player);
	
};

/* ============================================================== */
// EnemyBullet7
/* ============================================================== */
class EnemyBullet7 : public EnemyBullet{
    GMTexture2D*    mTex;
	
public:
    EnemyBullet7(Player* player,const GMVector2D& pos , int number );
    virtual ~EnemyBullet7();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
	virtual bool    moveImpl(Player *player);
	
};
/* ============================================================== */
// EnemyBullet8
/* ============================================================== */
class EnemyBullet8 : public EnemyBullet{
    GMTexture2D*    mTex;
	
public:
    EnemyBullet8(Player* player,const GMVector2D& pos , int number );
    virtual ~EnemyBullet8();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
	virtual bool    moveImpl(Player *player);
	
};
#endif  //#ifndef __ENEMY_BULLET_H__
