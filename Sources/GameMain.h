//
//  GameMain.h
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__


#include "Karakuri.h"
#include "Globals.h"


// このクラスのインスタンスには、gGameInst 変数でアクセスできます。

class Score;
class Own;
class Global;

class GameMain : public GMGame {

public:
    GameMain();
    virtual ~GameMain();
	
public:
	double	bgmVolume;
	double	soundVolume;

public:
	double	getBgmVolume() const;
	double	getSoundVolume() const;
	
	void	setSoundVolume(double inValue);
	
	
public:
	Score*	mScore;
	Own*	mOwn;
	Global* mGlobal;
};



class Score {
private:
	long	currentScore;
	

	
public:
	Score();
    virtual ~Score();
	
	
public:
	void	setCurrentScore(long inScore);
	long	getCurrentScore() const;
	void	addCurrentScore(long inScore);
};

class Own {

private:
	double		myLife;
	double		myPower;
	double		myBoms;

public:
	Own();
	virtual ~Own();
	
public:
	//自機数
	void	setMyLife(double inMyLife);
	double	getMyLife() const;
	void	addMyLife(double inMyLife);

	//パワー
	void	setMyPower(double inMyPower);
	double	getMyPower() const;
	void	addMyPower(double inMyPower);
	
	//ボム数
	void	setMyBoms(double inMyBoms);
	double	getMyBoms() const;
	void	addMyBoms(double inMyBoms);
	
};

class Global{
private:
	int bossFlag;
	int bossBGMFlag;
	int selectCharacterFlag;
public:
	Global();
	virtual ~Global();
	
	void setBossFlag(int flag);
	int getBossFlag() const;
	
	void setBossBGMFlag(int flag);
	int getBossBGMFlag() const;
	
	void setSelectCharacterFlag(int flag);
	int getSelectCharacterFlag() const;
};


extern GameMain *gGameInst;


#endif  //#ifndef __GAMEMAIN_H__

