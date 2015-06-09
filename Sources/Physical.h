/*
 *  Physical.h
 *  Karakuri2 Mac for Xcode 4
 *
 *  Created by KAI Seiya on 11/12/15.
 *  Copyright 2011 Satoshi Numata. All rights reserved.
 *
 */

#include "Karakuri.h"


class Physical {
	
public:
    Physical();
    virtual ~Physical();
	
public:
	int			phyFlag;
	GMVector2D	phyA;
	GMVector2D	phyVo;
	GMVector2D	phyMaxPos;
	GMVector2D	phyPrePos;
	int			phyNowT;
	int			phyPreT;
	
	void		initPhysical();
	bool		movePhysical(double startingPosX, double startingPosY, double maxPosX,double maxPosY,int nowT , int maxT);
	
};