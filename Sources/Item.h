//
//  PlayerBullet.h
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/04.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __ITEM_H__
#define __ITEM_H__


#include "Karakuri.h"



class Item {
    
    GMVector2D	mPos;
	GMVector2D	mSize;
    GMVector2D  mV;
    GMVector2D  mA;
    double	mAngle;
	double	mAngleSpeed;
	

	
	int			mType;
	int			mState;
	int			mCount;
	
	bool		collect;
	
public:
    Item(const GMVector2D& pos,int type);
    virtual ~Item();
    
public:
    GMRect2D    getAttackBounds() const;
    GMRect2D	getApproachBounds() const;
	
public:
    void    draw(GMSpriteBatch* batch,GMTexture2D* tex);
    bool    move();
	
public:
	int		getType() const;
	GMVector2D	getPos() const;
	void	setPos(GMVector2D pos);
    int		getState() const;
	void	setCollect(bool flag);
	bool	getCollect() const;
	

	
};


#endif  //#ifndef __ITEM_H__

