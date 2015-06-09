//
//  EnemyDamageEffect.h
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/22.
//  Copyright (c) 2011 Satoshi Numata. All rights reserved.
//

#ifndef __ENEMY_DAMAGE_EFFECT_H__
#define __ENEMY_DAMAGE_EFFECT_H__


#include "Karakuri.h"



class EnemyDamageEffectData {
    
    GMVector2D  mPos;
    GMVector2D  mV;
    double      mAngle;
    double      mAngleSpeed;
    int         mLife;
    
public:
    EnemyDamageEffectData(const GMVector2D& pos);
    
public:
    void    draw(GMSpriteBatch* spriteBatch, GMTexture2D* tex);
    bool    step();
    
};


class EnemyDamageEffect {
    
    std::list<EnemyDamageEffectData*>   mEffectData;
    GMTexture2D*                        mTex;
    
public:
    EnemyDamageEffect();
    ~EnemyDamageEffect();

public:
    void    addEffect(const GMVector2D& pos);
    
public:
    void    draw(GMSpriteBatch* spriteBatch);
    void    step();
    
};


#endif  //#ifndef __ENEMY_DAMAGE_EFFECT_H__

