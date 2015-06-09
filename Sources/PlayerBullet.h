//
//  PlayerBullet.h
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/04.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__


#include "Karakuri.h"


class PlayerBullet {
    
    GMVector2D  mPos;
	GMVector2D	mSize;
    GMVector2D  mV;
    GMVector2D  mA;
	
	double          mAngle;
    double          mAngleSpeed;
	
public:
	double rot;	// 円の角度(0 ～ 360)
	double rot_speed;	// 円の角度変化量(0 ～ 360)
	double radius ;	// 円の半径
	double rad;
	
public:
	int mType;
	
	
public:
    PlayerBullet(const GMVector2D& pos,int type,GMInput* input);
    virtual ~PlayerBullet();
    
public:
    GMRect2D    getAttackBounds() const;
	int			getType() const;
	GMVector2D	getSize() const;
	
public:
    void    draw(GMSpriteBatch* batch, GMTexture2D* tex);
    bool    move();
	
};





#endif  //#ifndef __PLAYER_BULLET_H__

