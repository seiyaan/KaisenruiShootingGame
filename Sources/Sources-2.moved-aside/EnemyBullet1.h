/*
 *  EnemyBullet1.h
 *  Karakuri2 Mac for Xcode 4
 *
 *  Created by KAI Seiya on 11/12/18.
 *  Copyright 2011 Satoshi Numata. All rights reserved.
 *
 */

#include "EnemyBullet.h"




/* ============================================================== */
// EnemyBullet1
/* ============================================================== */
class EnemyBullet1 : public EnemyBullet {
    
    GMTexture2D*    mTex;
	double temp_posX;
	
public:
    EnemyBullet1(const GMVector2D& pos, int life, int number, int deadScore, int item);
    virtual ~EnemyBullet1();
    
public:
    virtual GMRect2D    getDefenceBounds() const;
    
public:
    virtual void    draw(GMSpriteBatch* batch);
    virtual bool    moveImpl(Player *player);
	
};
