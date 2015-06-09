/*
 *  Physical.cpp
 *  Karakuri2 Mac for Xcode 4
 *
 *  Created by KAI Seiya on 11/12/15.
 *  Copyright 2011 Satoshi Numata. All rights reserved.
 *
 */

#include "Physical.h"


Physical::Physical()
{
    // Do nothing
}

Physical::~Physical()
{
    // Do nothing
}

void Physical::initPhysical(){
	phyFlag = 0;
}
bool Physical::movePhysical(double startingPosX, double startingPosY, double maxPosX,double maxPosY,int nowT , int maxT){
	// movePyhsical(X移動値,Y移動値,移動に所要する時間){}
	
	
	if (phyFlag == 0){
		phyPrePos.x = startingPosX;
		phyPrePos.y = startingPosY;
		phyPreT = nowT;
		phyFlag = 1;
	}
	
	phyNowT = nowT - phyPreT;
	
	phyMaxPos.x = maxPosX;
	phyMaxPos.y = maxPosY;
	
	phyA.x = 2*phyMaxPos.x / (maxT * maxT);
	phyA.y = 2*phyMaxPos.y / (maxT * maxT);
	
	phyVo.x = 2*phyMaxPos.x / maxT;
	phyVo.y = 2*phyMaxPos.y / maxT;
	
	
	
	
	mPos.x = phyPrePos.x + phyVo.x*phyNowT - 0.5*phyA.x*(phyNowT*phyNowT);
	mPos.y = phyPrePos.y + phyVo.y*phyNowT - 0.5*phyA.y*(phyNowT*phyNowT);
	
	if(phyNowT == maxT){
		return true;
	}else {
		return false; 
	}
}