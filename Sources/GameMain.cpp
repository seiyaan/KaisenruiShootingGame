//
//  GameMain.cpp
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GameMain.h"
#include "Globals.h"

#include "TitleScene.h"
#include "PlayerSelectScene.h"
#include "PlayScene.h"
#include "Player.h"
#include "GameClearScene.h"
#include "GameOverScene.h"

GameMain*   gGameInst = NULL;


GameMain::GameMain()
{
    gGameInst = this;
    
	
	
    ///// ゲームの初期化
	bgmVolume = 1.0;	//BGMボリューム
	soundVolume = 0.8;	//サウンドのボリューム
	
    // TODO: ゲーム内で共通して利用する変数などがあれば、ここで準備してください。
    // TODO: GameMain クラスのインスタンスには、GameMain.h をインクルードして gGameInst 変数で参照します。
	mScore = new Score();
	mOwn = new Own();
	mGlobal = new Global();
	
    ///// シーンの追加
    addScene("title", new TitleScene());
    addScene("player_select", new PlayerSelectScene());
    addScene("play", new PlayScene());
    
	addScene("game_clear", new GameClearScene());
	addScene("game_over", new GameOverScene());
	
    ///// 最初のシーンの選択
    GMGame::ChangeScene("title");
}

GameMain::~GameMain()
{
    ///// ゲームの解放
    // TODO: ゲーム内で共通して利用していた変数などがあれば、ここで解放してください。
	
	// インスタンスを開放
	delete mScore;	
	delete mOwn;
	delete mGlobal;
}

double GameMain::getBgmVolume() const{
	return bgmVolume;
}

double GameMain::getSoundVolume() const{
	return soundVolume;
}

void GameMain::setSoundVolume(double inValue)
{
	soundVolume = inValue;
}





Score::Score()
{
	currentScore = 0;
}
Score::~Score(){ 
	//Do Nothing
}

long	Score::getCurrentScore() const 
{
	return currentScore; 
}

void	Score::addCurrentScore(long inScore)
{
	currentScore += inScore; 
	if(currentScore > 99999999)
	{
		currentScore = 99999999;
	}
}
void	Score::setCurrentScore(long inScore)
{
	currentScore = inScore;
	if(currentScore > 99999999)
	{
		currentScore = 99999999;
	}
}




Own::Own()
{
	//Do Nothing
	myLife = 5.0;
	myPower = 5.0;
	myBoms = 5.0;
}
Own::~Own(){ 
	//Do Nothing 
}

//自機数
double	Own::getMyLife() const 
{ 
	return myLife; 
}

void	Own::addMyLife(double inMyLife)
{
	myLife += inMyLife; 
	if(myLife > 8){ 
		myLife = 8; 
	}else if(myLife < 0){
		GMGame::ChangeScene("game_over");
	}
}
void	Own::setMyLife(double inMyLife)
{
	myLife = inMyLife; 
	if(myLife > 8) 
	{ 
		myLife = 8; 
	}
}

//パワー
double	Own::getMyPower() const 
{ 
	return myPower; 
}

void	Own::addMyPower(double inMyPower){ 
	myPower += inMyPower; 
	if(myPower > 5.0)
	{
		myPower = 5.0;
	}
}
void	Own::setMyPower(double inMyPower){
	myPower = inMyPower;
	if(myPower > 5.0)
	{
		myPower = 5.0;
	}
}

//ボム数
double	Own::getMyBoms() const 
{
	return myBoms; 
}
void	Own::addMyBoms(double inMyBoms)
{
	myBoms += inMyBoms; 
	if(myBoms > 8)
	{
		myBoms = 8;
	}
}
void	Own::setMyBoms(double inMyBoms)
{
	myBoms = inMyBoms;
	if(myBoms > 8)
	{
		myBoms = 8;
	}
}



Global::Global()
{
	selectCharacterFlag = 0;
	bossFlag = 0;
	bossBGMFlag = 0;
}
Global::~Global()
{
	//Do Nothing
}
void Global::setBossFlag(int flag)
{
	bossFlag = flag;
}
int Global::getBossFlag() const
{
	return bossFlag;
}
void Global::setBossBGMFlag(int flag)
{
	bossBGMFlag = flag;
}
int Global::getBossBGMFlag() const
{
	return bossBGMFlag;
}
void Global::setSelectCharacterFlag(int flag)
{
	selectCharacterFlag = flag;
}
int Global::getSelectCharacterFlag() const
{
	return selectCharacterFlag;
}


