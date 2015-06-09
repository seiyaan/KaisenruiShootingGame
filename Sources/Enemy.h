//
//  Enemy.h
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/21.
//  Copyright 2011 Satoshi Numata. All rights reserved.
//

#ifndef __ENEMY_H__
#define __ENEMY_H__


#include "Karakuri.h"
#include "Player.h"
#include "EnemyBullet.h"


/* ============================================================== */
// Enemy
/* ============================================================== */
class Enemy {
    
protected:
	
    GMVector2D      mPos;
    GMVector2D		mSize;
	GMVector2D      mV;
    GMVector2D      mA;
    int             mState;
    int             mLife;
	int				mLifeMax;
	int				mNumber;
	int				mType;
	int				mCount;
	
	int				mDeadScore;
	
	double          mAngle;
    double          mAngleSpeed;
	
    
	double			mRot;		// 円の角度(0 ～ 360)
	double			mRot_speed;	// 円の角度変化量(0 ～ 360)
	double			mRadius;	// 円の半径
	double			mRad;		// ラジアン
	
	int				mItem;
	int				mBulletType1;
	int				mBulletType2;
	int				mBulletNumber;
	
public:

    Enemy(const GMVector2D& pos, int life );
    virtual ~Enemy();
    

	
public:
    virtual GMRect2D    getDefenceBounds() const = 0;
    
    GMVector2D	getPos() const;
	GMVector2D	getSize() const;
    void		decreaseLife(int power);
    bool		isDead() const;
	int			isItem() const;
	

	int			getBulletNumber() const;
	int			getBulletType1() const;
	int			getBulletType2() const;
	void		setBullet(int type1, int type2, int number);
	
	
public:
    virtual void    draw(GMSpriteBatch* batch) = 0;
    bool            move(Player *player);
    virtual bool    moveImpl(Player *player) = 0;


public:
	int			phyFlag;
	GMVector2D	phyA;
	GMVector2D	phyVo;
	GMVector2D	phyMaxPos;
	GMVector2D	phyPrePos;
	int			phyNowT;
	int			phyPreT;
	bool		movePhysical(double maxPosX,double maxPosY,int maxT);

public:
	int			fuwaFlag;
	GMVector2D	fuwaA;
	int			fuwaNowT;
	int			fuwaPreT;
	
	
};


/* ============================================================== */
// EnemyGenerator
/* ============================================================== */
struct EnemyAppearance {
    
    int     frame;
    int     type;
    int     x;
    int     y;
    int     life;
    int     size;
    int		deadScore;
	
	int		itemType;
};

class EnemyGenerator {
	
	int		mFrameCount;
    std::vector<EnemyAppearance>    mAppearances;
    
    int                 mCurrentPos;
    EnemyAppearance     mNextAppearance;
	
public:
    EnemyGenerator();
    ~EnemyGenerator();
    
private:
	void    addEnemyAppearance(int frame, int type, int itemType ,int x, int y, int life, int size ,int score );
    Enemy*  createEnemy(EnemyAppearance* appearance, int number);
	
public:
    void    loadEnemyAppearances(int stage);
    void    generateEnemies(std::list<Enemy *> *enemies);

	
};

/* ============================================================== */
// EnemyManager
/* ============================================================== */
class EnemyManager {

	EnemyGenerator      mEnemyGenerator;
	std::list<Enemy*>	mEnemies;
	
public:
	EnemyManager();
	~EnemyManager();
	
public:
    void    loadEnemyAppearances(int stage);
    void    generateEnemies();
	void	drawAllEnemies(GMSpriteBatch *batch);
	void	moveAllEnemies(Player *player);

    std::list<Enemy *>* getEnemies();

};



#endif  //#ifndef __ENEMY_H__

