//
//  Enemy1.h
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/21.
//  Copyright 2011 Satoshi Numata. All rights reserved.
//

#ifndef __ENEMY1_H__
#define __ENEMY1_H__


#include "Enemy.h"


/* ============================================================== */
// Enemy0
/* ============================================================== */
class Enemy0 : public Enemy {
    
    GMTexture2D*    mTex;

	
public:
    Enemy0(const GMVector2D& pos, int life, int number, int deadScore , int item );
    virtual ~Enemy0();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
	
	
};


/* ============================================================== */
// Enemy1
/* ============================================================== */
class Enemy1 : public Enemy {
    
    GMTexture2D*    mTex;
	double mPosInX;
	double mPosInY;
	
public:
    Enemy1(const GMVector2D& pos, int life, int number, int deadScore, int item );
    virtual ~Enemy1();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);

};

/* ============================================================== */
// Enemy2
/* ============================================================== */
class Enemy2 : public Enemy {
    
    GMTexture2D*    mTex;
	
public:
    Enemy2(const GMVector2D& pos, int life, int number, int deadScore, int item );
    virtual ~Enemy2();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
	
};

/* ============================================================== */
// Enemy3
/* ============================================================== */
class Enemy3 : public Enemy {
    
    int startFlag;
	double mPosInX;
	double mPosInY;
	
    GMTexture2D*    mTex;	
	
	
public:
    Enemy3(const GMVector2D& pos, int life, int number , int deadScore, int item );
    virtual ~Enemy3();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
	
};


/* ============================================================== */
// Enemy4
/* ============================================================== */
/*
 class Enemy4 : public Enemy {
    
    int startFlag;
	double mPosInX;
	double mPosInY;
	
    GMTexture2D*    mTex;	
	
	
public:
    Enemy4(const GMVector2D& pos, int life, int number , int deadScore, int item );
    virtual ~Enemy4();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
	
};
*/

class Enemy4 : public Enemy {
    int startFlag;
    GMTexture2D*    mTex;	
public:
    Enemy4(const GMVector2D& pos, int life, int number , int deadScore, int item );
    virtual ~Enemy4();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
	
};


/* ============================================================== */
// Enemy5
/* ============================================================== */
class Enemy5 : public Enemy {
	int startFlag;
    GMTexture2D*    mTex;	
public:
    Enemy5(const GMVector2D& pos, int life, int number , int deadScore, int item );
    virtual ~Enemy5();
public:
    virtual GMRect2D    getDefenceBounds() const;
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
};


/* ============================================================== */
// Enemy6
/* ============================================================== */
class Enemy6 : public Enemy {
    GMTexture2D*    mTex;	
public:
    Enemy6(const GMVector2D& pos, int life, int number , int deadScore, int item );
    virtual ~Enemy6();
public:
    virtual GMRect2D    getDefenceBounds() const;
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
};

/* ============================================================== */
// Enemy7
/* ============================================================== */
class Enemy7 : public Enemy {
    GMTexture2D*    mTex;	
public:
    Enemy7(const GMVector2D& pos, int life, int number , int deadScore, int item );
    virtual ~Enemy7();
public:
    virtual GMRect2D    getDefenceBounds() const;
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
};

/* ============================================================== */
// Enemy8
/* ============================================================== */
class Enemy8 : public Enemy {
    GMTexture2D*    mTex;	
public:
    Enemy8(const GMVector2D& pos, int life, int number , int deadScore, int item );
    virtual ~Enemy8();
public:
    virtual GMRect2D    getDefenceBounds() const;
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
};

/* ============================================================== */
// Enemy9
/* ============================================================== */
class Enemy9 : public Enemy {
    GMTexture2D*    mTex;	
public:
    Enemy9(const GMVector2D& pos, int life, int number , int deadScore, int item );
    virtual ~Enemy9();
public:
    virtual GMRect2D    getDefenceBounds() const;
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
};

/* ============================================================== */
// Enemy1000
/* ============================================================== */
class Enemy1000 : public Enemy {
    int startFlag;
	double mPosInX;
	double mPosInY;
	
    GMTexture2D*    mTex;	
	GMTexture2D*	mTexLife;
	
	int		mCount_temp;
	int		count_temp;
	
public:
    Enemy1000(const GMVector2D& pos, int life, int number , int deadScore, int item );
    virtual ~Enemy1000();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);

};






#endif  //#ifndef __ENEMY1_H__

