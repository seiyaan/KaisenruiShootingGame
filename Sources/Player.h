//
//  Player.h
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/04.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Karakuri.h"
#include "GameMain.h"

class Option;	//クロスリファレンス

class Player {
    
    GMTexture2D*    mTex;
	GMTexture2D*	mTexDeadEffect;
	GMVector2D      mPos;
	GMVector2D		mSize;
	
    int     mAnimationCount;
    int		mCount;
	int		mCount_temp;
    int     mType;
    int     mStatus;
    int     mStatusCount;
	int		mNodamageFlag;
	int		mDeadEffectFlag;
	int		mDeadEffectCount;
	GMVector2D mDeadEffectPos;
	
	std::list<Option*>			mOptions;
	
	
	//Option		*mOptions[10];	//PlayerクラスでOptionクラスを使う
	int		mOptionCount;
	
	
    
public:
    Player(int type);
    ~Player();
	
    
public:
	void		addOptionCount();
	void		removeOptionCount();
	void		setOptionCount(int inValue);
	
	void		resetStatus();
	void		UpGrade(int type);
	Option		*getOption(int index);
    
	GMVector2D  getPos() const;
	double		getPosX() const;
	double		getPosY() const;
	double		getAnimationCountToAngle() const;
    int         getStatus() const;
	int			getOptionCount() const;
	GMRect2D	getDefenceBounds()	const;
	GMVector2D	getSize() const;
	int			getNoDamageFlag() const;
	
	
public:
    void    draw(GMSpriteBatch* batch);
    void    move(GMInput* input);
};





/* ============================================================== */
// Option
/* ============================================================== */

class Option {
	
	Player		*mParentPlayer;
	GMVector2D	mPos;
	int			mType;
	
	
	
public:
	Option(Player *player , int type);	//コンストラクタ new された時
	~Option();	//デストラクタ 破壊された時
	
public :
	bool	move(GMInput* input , int number );
	void	draw(GMSpriteBatch* batch);
	
	GMVector2D  getPos() const;
	
	
public:
	double mAngle;
	double mAngleSpeed;
	
	
	double rot;	// 円の角度(0 ～ 360)
	double rot_speed;	// 円の角度変化量(0 ～ 360)
	double radius ;	// 円の半径
	double rad;
	
	
	
};




#endif  //#ifndef __PLAYER_H__


