//
//  EnemyDamageEffect.cpp
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/22.
//  Copyright (c) 2011 Satoshi Numata. All rights reserved.
//

#include "EnemyDamageEffect.h"


static const double sEffectSpeed = 3;
static const int sEffectLife = 20;


EnemyDamageEffectData::EnemyDamageEffectData(const GMVector2D& pos)
    : mPos(pos)
{
    mV = GMVector2D(GMRandom::NextDouble() * sEffectSpeed - sEffectSpeed/2, GMRandom::NextDouble() * sEffectSpeed * -2.5);
    mAngle = GMRandom::NextDouble() * M_PI;
    mAngleSpeed = GMRandom::NextDouble() * 0.5 - 0.25;
    mLife = sEffectLife;
}

void EnemyDamageEffectData::draw(GMSpriteBatch* spriteBatch, GMTexture2D* tex)
{
    double alpha = (double)mLife / sEffectLife;
    spriteBatch->draw(tex, mPos+GMVector2D(10, 10), GMRect2D::Empty, GMColor(1, 1, 1, mLife), mAngle, GMVector2D(10, 10), GMVector2D(alpha*2+0.5, alpha*2+0.5), GMSpriteFlipNone, 0.0);
}

bool EnemyDamageEffectData::step()
{
    mAngle += mAngleSpeed;
    mPos += mV;
    mLife--;
    
    return (mLife > 0);
}


EnemyDamageEffect::EnemyDamageEffect()
{
    mTex = new GMTexture2D("enemy_damage.png");
}

EnemyDamageEffect::~EnemyDamageEffect()
{
    delete mTex;
    mTex = NULL;
	
	
}

void EnemyDamageEffect::addEffect(const GMVector2D& pos)
{
    EnemyDamageEffectData* data = new EnemyDamageEffectData(pos);
    mEffectData.push_back(data);
}

void EnemyDamageEffect::draw(GMSpriteBatch* spriteBatch)
{
    std::list<EnemyDamageEffectData*>::iterator it = mEffectData.begin();
    std::list<EnemyDamageEffectData*>::iterator it_end = mEffectData.end();
    
    while (it != it_end) {
        (*it)->draw(spriteBatch, mTex);
        it++;
    }
}

void EnemyDamageEffect::step()
{
    std::list<EnemyDamageEffectData*>::iterator it = mEffectData.begin();
    std::list<EnemyDamageEffectData*>::iterator it_end = mEffectData.end();
    
    while (it != it_end) {
        if (!(*it)->step()) {
            delete *it;
            it = mEffectData.erase(it);
            it_end = mEffectData.end();
        } else {
            it++;
        }
    }
}



