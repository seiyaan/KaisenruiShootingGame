//
//  PlayScene.cpp
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/04.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "PlayScene.h"
#include <sstream>
#include <iomanip>

PlayScene*   gPlaySceneInst = NULL;


BackStar::BackStar()
{
    mPos.x = GMRandom::NextDouble() * 430 + 42;
    mPos.y = 480 + 4;
    mV.x = GMRandom::NextDouble() * 0.8;
    mV.y = (GMRandom::NextDouble() * -2) - 2;
}

void BackStar::draw(GMSpriteBatch* batch, GMTexture2D* tex)
{
    batch->draw(tex, mPos);
}

bool BackStar::move()
{
    mPos += mV;
    if (mPos.y < -4) {
        return false;
    }
    return true;
}


PlayScene::PlayScene()
{
    gPlaySceneInst = this;
    
    // PlaySceneから開始したときのデバッグ用
    //mPlayerType = 1;
}

PlayScene::~PlayScene()
{
    // Do nothing
}



void PlayScene::willAppear(GMGraphics* g)
{
	gGameInst->mOwn->setMyLife(4.0);
	gGameInst->mOwn->setMyPower(1.0);
	gGameInst->mOwn->setMyBoms(3.0);
	gGameInst->mScore->setCurrentScore(0);
	
	gGameInst->mGlobal->setBossBGMFlag(0);
	gGameInst->mGlobal->setBossFlag(0);
	
	
	
	mCountKeyDownX = 0;
	mFrameCount = 0;
    
	// 基本のシェーダ、2D描画用バッチ
    mBasicEffect = new GMBasicEffect();
    mSpriteBatch = new GMSpriteBatch();
    
    GMVector2D screenSize = g->getScreenSize();
    mBasicEffect->setProjectionMatrix(GMMatrix::CreateOrthographicOffCenter(0.0, screenSize.x, 0.0, screenSize.y, -1.0, 1.0));
    mBasicEffect->setViewMatrix(GMMatrix::Identity);
    
    mTexBack1 = new GMTexture2D("play_back1.png");
    mTexBack2 = new GMTexture2D("play_back2.png");
    mTexStar = new GMTexture2D("play_star.png");
    mTexTitle = new GMTexture2D("stage1_title.png");
    
	mTexItem1 = new GMTexture2D("Item_score.png");
	mTexItem2 = new GMTexture2D("Item_power.png");
	mTexItem3 = new GMTexture2D("Item_bom.png");
	
	mCounter = new GMTexture2D("counter1.png");
	mGaugeLife = new GMTexture2D("gauge_heart2.png");
	mGaugeBoms = new GMTexture2D("gauge_star.png");
	
	
	//たこ
	mTexPlayerBullet1 = new GMTexture2D("player_bullet_tako.png");
	mTexOptionBullet1 = new GMTexture2D("player_bullet2.png");
	
	//いか
	mTexPlayerBullet3 = new GMTexture2D("player_bullet_ika.png");
	mTexOptionBullet3 = new GMTexture2D("player_bullet2.png");
	
	//うに
	mTexPlayerBullet2 = new GMTexture2D("player_bullet_uni.png");
	mTexOptionBullet2 = new GMTexture2D("player_bullet2.png");
	
    mPlayer = new Player(mPlayerType);
    mOwn = new Own();
	
	mShowScore = new GMLabel("HelveticaNeue-Bold",22.0);
	mShowPower = new GMLabel("HelveticaNeue-Bold",22.0);
	mShowPowerDecimal = new GMLabel("HelveticaNeue-Bold",22.0);
	
	mEnemyManager = new EnemyManager();
    mEnemyManager->loadEnemyAppearances(1);
	
	mEnemyBulletManager = new EnemyBulletManager;
	
	
    mStatus = 0;    // フェードイン
    mFadeCount = 80;
    mIsPausing = false;
    mTitleCount = 300;
    mPlayerBulletState = 0;
	
	
	
    mSEShot = new GMSound("shot_se2.m4a");
    mSEShot->setVolume(gGameInst->getSoundVolume());
	
    mSEEnemyBreak = new GMSound("enemy_break.aif");
    mSEEnemyBreak->setVolume(gGameInst->getSoundVolume());
	
	mSEExplosion = new GMSound("explosion.mp3");
	mSEExplosion->setVolume(gGameInst->getSoundVolume());
	
	mSEExplosion2 = new GMSound("explosion2.mp3");
	mSEExplosion2->setVolume(gGameInst->getSoundVolume());

    mBGM = new GMMusic("kamikaze.mp3");
    mBGM->setVolume(gGameInst->getBgmVolume());
	mBGM->play();
	
	mBGMBoss1 = new GMMusic("boss1.mp3");	
    mBGMBoss1->setVolume(gGameInst->getBgmVolume());

    
    mEnemyDamageEffect = new EnemyDamageEffect();
	
	mWaitClearScene = 0;
}

void PlayScene::didDisappear()
{
    delete mEnemyDamageEffect;
    mEnemyDamageEffect = NULL;
    
    mBGM->stop();
    delete mBGM;
    mBGM = NULL;
	
	mBGMBoss1->stop();
	delete mBGMBoss1;
	mBGMBoss1 = NULL;
    
    delete mTexTitle;
    mTexTitle = NULL;
    
    delete mSEEnemyBreak;
    mSEEnemyBreak = NULL;
    
    delete mSEShot;
    mSEShot = NULL;
	
	delete mSEExplosion;
	mSEExplosion = NULL;
	
	
	delete mSEExplosion2;
	mSEExplosion2 = NULL;
	
    
    delete mBasicEffect;
    mBasicEffect = NULL;
    
    delete mSpriteBatch;
    mSpriteBatch = NULL;
    
    delete mTexBack1;
    mTexBack1 = NULL;
    
    delete mTexBack2;
    mTexBack2 = NULL;
    
    delete mTexStar;
    mTexStar = NULL;
    
    delete mTexPlayerBullet1;
    mTexPlayerBullet1 = NULL;
	
	delete mTexOptionBullet1;
	mTexOptionBullet1 = NULL;
    
	delete mTexPlayerBullet2;
    mTexPlayerBullet2 = NULL;
	
	delete mTexOptionBullet2;
	mTexOptionBullet2 = NULL;
    
	delete mTexPlayerBullet3;
    mTexPlayerBullet3 = NULL;
	
	delete mTexOptionBullet3;
	mTexOptionBullet3 = NULL;
	
    delete mPlayer;
    mPlayer = NULL;
    
    delete mEnemyManager;
    mEnemyManager = NULL;
	
	delete mEnemyBulletManager;
	mEnemyBulletManager = NULL;
	
	delete mGaugeLife;
	mGaugeLife = NULL;
	
	delete mGaugeBoms;
	mGaugeBoms = NULL;
	
	delete mCounter;
	mCounter = NULL;

	delete mTexItem1;
	mTexItem1 = NULL;
	
	delete mTexItem2;
	mTexItem2 = NULL;
	
	delete mTexItem3;
	mTexItem3 = NULL;
	
	delete mShowScore;
	mShowScore = NULL;
	
	delete mShowPower;
	mShowPower = NULL;
	
	delete mShowPowerDecimal;
	mShowPowerDecimal = NULL;
	
	
}

void PlayScene::drawBackground()
{
    
    for (std::list<BackStar*>::iterator itStar = mStars.begin(), itEnd = mStars.end(); itStar != itEnd; itStar++) {
        (*itStar)->draw(mSpriteBatch, mTexStar);
    }
}

void PlayScene::drawView(GMGraphics* g)
{
    g->clear(GMColor(0.1, 0.1, 0.1, 1.0));
    
    mBasicEffect->begin();
    {
        mBasicEffect->setWorldMatrix(GMMatrix::CreateTranslation(72, 0, 0));

        GMDrawSys::SetBlendMode(GMBlendModeAlpha);
        mSpriteBatch->begin();
        drawBackground();
        mSpriteBatch->end();

		
        GMDrawSys::SetBlendMode(GMBlendModeAdd);
        mSpriteBatch->begin();
		
		// 弾sの描画
		for (std::list<PlayerBullet*>::iterator it = mPlayerBullets.begin(), itEnd = mPlayerBullets.end(); it != itEnd; it++) {
			if((*it)->getType() == 0 || (*it)->getType() == 10) {
				
				if(gPlaySceneInst->getPlayerType() == 1){
					(*it)->draw(mSpriteBatch, mTexPlayerBullet1);
				}else if(gPlaySceneInst->getPlayerType() == 2){
					(*it)->draw(mSpriteBatch, mTexPlayerBullet2);
				}else if(gPlaySceneInst->getPlayerType() == 3){
					(*it)->draw(mSpriteBatch, mTexPlayerBullet3);
				}
				
			}else if((*it)->getType() == 100){
				(*it)->draw(mSpriteBatch, mTexOptionBullet1);
			}
		}
		
		
		// アイテムの描画
		for (std::list<Item*>::iterator it = mItems.begin(), itEnd = mItems.end(); it != itEnd; it++) {
			if((*it)->getType() == 1){
				(*it)->draw(mSpriteBatch,mTexItem1);
			}else if((*it)->getType() == 2){
				(*it)->draw(mSpriteBatch,mTexItem2);
			}else if((*it)->getType() == 3){
				(*it)->draw(mSpriteBatch,mTexItem3);
			}
        }
		
		
        mPlayer->draw(mSpriteBatch);
        mSpriteBatch->end();

		// 敵と弾の衝突を描画
        GMDrawSys::SetBlendMode(GMBlendModeAdd);
        mSpriteBatch->begin();
        mEnemyDamageEffect->draw(mSpriteBatch);
        mSpriteBatch->end();        

		// 敵の弾描画
		GMDrawSys::SetBlendMode(GMBlendModeAlpha);
        mSpriteBatch->begin();
        mEnemyBulletManager->drawAllEnemyBullets(mSpriteBatch);
        mSpriteBatch->end();
		
        // 敵の描画
        GMDrawSys::SetBlendMode(GMBlendModeAlpha);
        mSpriteBatch->begin();
        mEnemyManager->drawAllEnemies(mSpriteBatch);
        mSpriteBatch->end();
		
		
        // スコアボードの描画
        GMDrawSys::SetBlendMode(GMBlendModeAlpha);
        mSpriteBatch->begin();
        mBasicEffect->setWorldMatrix(GMMatrix::Identity);
        mSpriteBatch->draw(mTexBack1, GMVector2D::Zero, GMColor::White);
        mSpriteBatch->draw(mTexBack2, GMVector2D(640-168, 0), GMColor::White);
		
		
		//得点
		std::ostringstream ossScore;
		ossScore << std::setw(8);
		ossScore << std::setfill('0');
		ossScore << gGameInst->mScore->getCurrentScore();
		mShowScore->setText(ossScore.str());
		mSpriteBatch->draw(mShowScore->getTexture(), GMVector2D(530,442), GMColor(GMVector3D(0.3,0.4,1.0)));
		
		
		//仁侠
		std::ostringstream ossPower;
		ossPower << (int)(floor(gGameInst->mOwn->getMyPower()+0.001));
		ossPower << ".";
		mShowPower->setText(ossPower.str());
		mSpriteBatch->draw(mShowPower->getTexture(), GMVector2D(530,374), GMColor(GMVector3D(1.0,0.4,0.3)));
		
		std::ostringstream ossPowerDecimal;
		ossPowerDecimal << std::setw(2);
		ossPowerDecimal << std::setfill('0');
		ossPowerDecimal << gGameInst->mOwn->getMyPower()*100;
		std::string ossPowerDecimalTemp = ossPowerDecimal.str();
		ossPowerDecimalTemp = ossPowerDecimalTemp.substr(ossPowerDecimalTemp.length()-2, 2);
		ossPowerDecimalTemp += "/5.00";
		mShowPowerDecimal->setText(ossPowerDecimalTemp);
		mSpriteBatch->draw(mShowPowerDecimal->getTexture(), GMVector2D(550,374), GMColor(GMVector3D(1.0,0.4,0.3)));
		
		
		
		//残り自機数
		int my_life_int = (int)gGameInst->mOwn->getMyLife();
		
		for ( int i=7 ; i >= 0 ; i-- ){
			if( i < my_life_int ){
				mSpriteBatch->draw(mGaugeLife, GMVector2D(527+(12*i),412),GMRect2D(18*1,0,18,18), GMColor::White);
			}else {
				mSpriteBatch->draw(mGaugeLife, GMVector2D(527+(12*i),412),GMRect2D(18*0,0,18,18), GMColor::White);
			}
		}
		
		
        mSpriteBatch->end();

        if (mTitleCount > 0) {
            GMRect2D titleRect(72, 200, 404, 219);
            double alpha = 1.0;
            if (mTitleCount < 50) {
                titleRect.width += (50 - mTitleCount) * 2;
                titleRect.x -= (50 - mTitleCount);
                titleRect.height -= (50-mTitleCount) * 2;
                titleRect.y += (50-mTitleCount);
                alpha = mTitleCount / 50.0;
            } else if (mTitleCount > 250) {
                titleRect.width += (mTitleCount-250) * 2;
                titleRect.x -= (mTitleCount-250);
                titleRect.height -= (mTitleCount-250) * 2;
                titleRect.y += (mTitleCount-250);
                alpha = 1.0 - ((mTitleCount-250) / 50.0);
            }
            GMDrawSys::SetBlendMode(GMBlendModeAdd);
            mSpriteBatch->begin();
            mSpriteBatch->draw(mTexTitle, titleRect, GMColor(1, 1, 1, alpha));
            mSpriteBatch->end();
        }
        
        // フェードイン
        if (mStatus == 0) {
            double alpha = mFadeCount / 80.0;
            
            mBasicEffect->enableTexture(false);
            GMDrawSys::SetBlendMode(GMBlendModeAlpha);
            GMDraw::Begin();
            GMDraw::FillQuad(GMVector2D(0, 0), GMVector2D(640, 0), GMVector2D(640, 480), GMVector2D(0, 480), GMColor(1, 1, 1, alpha));
            GMDraw::End();
        }
    }
    mBasicEffect->end();
}

void PlayScene::updateModel(GMInput* input)
{
	if(gGameInst->mGlobal->getBossFlag() == 1){
		if(gGameInst->mGlobal->getBossBGMFlag() == 0){
			
			mBGM->stop();
			mBGMBoss1->play();
			gGameInst->mGlobal->setBossBGMFlag(1);
		}
	}else if(gGameInst->mGlobal->getBossFlag() == 9999){
		if(mWaitClearScene == 0){
			mSEExplosion2->play();
		}
		
		if(mWaitClearScene > 300){
			GMGame::ChangeScene("game_clear");
		}
		
		mWaitClearScene++;
	}
	
	
    if (mIsPausing) {
        if (input->isKeyDownTriggered(GMKeyMaskEscape)) {
            mBGM->play();
            mIsPausing = false;
        } else {
            return;
        }
    } else if (input->isKeyDownTriggered(GMKeyMaskEscape)) {
        mBGM->pause();
        mIsPausing = true;
        return;
    }
    
    // フェードイン
    if (mStatus == 0) {
        mFadeCount--;
        if (mFadeCount == 0) {
            mStatus = 1;
        }
    }
    
    if (mTitleCount > 0) {
        mTitleCount--;
    }
    
    for (std::list<BackStar*>::iterator itStar = mStars.begin(), itEnd = mStars.end(); itStar != itEnd;) {
        if ((*itStar)->move()) {
            itStar++;
        } else {
            delete *itStar;
            itStar = mStars.erase(itStar);
            itEnd = mStars.end();
        }
    }
    
	
	// プレイヤーの弾s生成
	if(mPlayer->getNoDamageFlag() == 0 || mPlayer->getNoDamageFlag() == 999 ){
		if (mPlayer->getStatus() < 10 && input->isKeyDown(GMKeyMaskZ)) {
			
			
			
			if( mCountKeyDownX % 3 == 0){
				PlayerBullet* bullet0_0 = 
				new PlayerBullet(mPlayer->getPos() + mPlayer->getSize()/2 + GMVector2D(-8-7,0) ,0,input);
				
				PlayerBullet* bullet0_1 = 
				new PlayerBullet(mPlayer->getPos() + mPlayer->getSize()/2 + GMVector2D(-8+8,0) ,0,input);
				
				
				mPlayerBullets.push_back(bullet0_0);
				mPlayerBullets.push_back(bullet0_1);
			}
			
			
			// オプションの弾
			int optionCount = mPlayer->getOptionCount();
			for (int i = 0; i < optionCount; i++) {
				Option *anOption = mPlayer->getOption(i);
				PlayerBullet* bullet = new PlayerBullet(anOption->getPos() + GMVector2D(10, 10),100,input);
				mPlayerBullets.push_back(bullet);
			}
			
			mSEShot->play();
			mCountKeyDownX++;
			
		}else if (mPlayer->getStatus() < 10 && input->isKeyUpTriggered(GMKeyMaskZ)){
			mCountKeyDownX = 0;
		}
	}
	
	// 敵の弾sを動かす
	mEnemyBulletManager->moveAllEnemyBullets(mPlayer);
	
	//敵を動かす
    mEnemyManager->generateEnemies();
    mEnemyManager->moveAllEnemies(mPlayer);
	
	// 弾sを動かす
    for (std::list<PlayerBullet*>::iterator it = mPlayerBullets.begin(), itEnd = mPlayerBullets.end(); it != itEnd;) {
        if ((*it)->move()) {
            it++;
        } else {
            delete *it;
            it = mPlayerBullets.erase(it);
            itEnd = mPlayerBullets.end();
        }
    }
    
	// アイテムを動かす
	for (std::list<Item*>::iterator it = mItems.begin(), itEnd = mItems.end(); it != itEnd;) {
        if ((*it)->move()) {
            it++;
        } else {
            delete *it;
            it = mItems.erase(it);
            itEnd = mItems.end();
        }
    }
	
	
    std::list<Enemy *> *enemies = mEnemyManager->getEnemies();
	
	
	for (std::list<Enemy*>::iterator it = enemies->begin(), itEnd = enemies->end(); it != itEnd; it++) {
		
		// 敵が砲台タイプを持っていた場合，敵の弾sを生成
		if((*it)->getBulletType1() != 0){
			
			if((*it)->getBulletType2() == 1){
				for( int i = (*it)->getBulletNumber() ; i > 0 ; i--){
					mEnemyBulletManager->createEnemyBullet(mPlayer,(*it)->getPos() + (*it)->getSize()/2, (*it)->getBulletType1() , i );
				}
			}else {
				mEnemyBulletManager->createEnemyBullet(mPlayer,(*it)->getPos() + (*it)->getSize()/2, (*it)->getBulletType1() , (*it)->getBulletNumber() );

			}
			(*it)->setBullet(0,0,0);
		}
		
		
		
	}
	
	
	 
	
	
	// 弾sと敵の当たりイテレーター
    for (std::list<PlayerBullet*>::iterator it = mPlayerBullets.begin(), itEnd = mPlayerBullets.end(); it != itEnd;) {
        GMRect2D attackBounds = (*it)->getAttackBounds();
        bool hit = false;
				
        for (std::list<Enemy*>::iterator it2 = enemies->begin(), it2End = enemies->end(); it2 != it2End; it2++) {
			
			
			
            GMRect2D defenceBounds = (*it2)->getDefenceBounds();
            if (attackBounds.intersects(defenceBounds)) {
				mEnemyDamageEffect->addEffect((*it2)->getPos()+GMVector2D((*it2)->getSize().x/2 -10, -5 ));
                hit = true;
                (*it2)->decreaseLife(1);
				
				
                if ((*it2)->isDead()) {	//死んだかどうか？
                    mSEEnemyBreak->play();
					
					if ((*it2)->isItem() != 0){	//アイテムを出すかどうか？
						Item* item1 = new Item((*it2)->getPos()+(*it2)->getSize()/2,(*it2)->isItem());
						mItems.push_back(item1);
					}
					
					//イテレータ削除
                    delete *it2;
                    it2 = enemies->erase(it2);
                    it2End = enemies->end();
				}
				
				
                break;
            }
        }
        if (hit) {	//弾sと敵が衝突（破壊ではない）
            delete *it;
            it = mPlayerBullets.erase(it);
            itEnd = mPlayerBullets.end();
			
			//スコアを追加
			gGameInst->mScore->addCurrentScore(10);
        } else {
            it++;
        }
    }
    
	
	
	
	
	
	if(mPlayer->getNoDamageFlag() == 0){
		GMRect2D defenceBounds = mPlayer->getDefenceBounds();
		
		//プレイヤーと敵弾sとの当たり判定
		std::list<EnemyBullet *> *enemybullets = mEnemyBulletManager->getEnemyBullets();
		for(std::list<EnemyBullet*>::iterator it = enemybullets->begin(), itEnd = enemybullets->end(); it!= itEnd; it++){
			GMRect2D attackBounds = (*it)->getDefenceBounds();
			
			
			if(attackBounds.intersects(defenceBounds)){
				
				mSEExplosion->play();
				mPlayer->resetStatus();
				gGameInst->mOwn->addMyLife(-1);	//自機数を減らす
				
				/*
				delete *it;
				it = enemybullets->erase(it);
				itEnd = enemybullets->end();
				 */
				
				
				enemybullets->clear();
				it = enemybullets->begin();
				itEnd = enemybullets->end();
				break;
			}
		}
		
		//プレイヤーと敵の当たり判定
		for (std::list<Enemy*>::iterator it = enemies->begin(), itEnd = enemies->end(); it != itEnd; it++){
			GMRect2D attackBounds = (*it)->getDefenceBounds();
			
			if(attackBounds.intersects(defenceBounds)){
				
				mSEExplosion->play();
				mPlayer->resetStatus();
				gGameInst->mOwn->addMyLife(-1);
				
				/*delete *it;
				it = enemies->erase(it);
				itEnd = enemies->end();
				 */
				break;
			}
		}
		
	}
	
	
	//アイテムリスト
	for(std::list<Item*>::iterator it = mItems.begin(), itEnd = mItems.end(); it!=itEnd;){
		GMRect2D defenceBounds = mPlayer->getDefenceBounds();
		GMRect2D attackBounds = (*it)->getAttackBounds();
		GMRect2D approachBounds = (*it)->getApproachBounds();
		
		
		if(attackBounds.intersects(defenceBounds)){
			//自機とアイテムが重なったらit削除
			mPlayer->UpGrade((*it)->getType());
			delete *it;
			it = mItems.erase(it);
			itEnd = mItems.end();
			break;
			
		}else if ((*it)->getCollect() == true){
			//Item::collect が true になったら自動回収
			GMVector2D dif_pos = (*it)->getPos() - mPlayer->getPos()-18;
			double abs_dif_pos_x = (dif_pos.x >= 0)?dif_pos.x : -1*dif_pos.x;
			double abs_dif_pos_y = (dif_pos.y >= 0)?dif_pos.y : -1*dif_pos.y;
			
			if ( abs_dif_pos_x < 20 || abs_dif_pos_y < 20){
				(*it)->setPos( ((*it)->getPos()) - ( (*it)->getPos() - mPlayer->getPos()-18 )/ 4 );
			}else {
				(*it)->setPos( ((*it)->getPos()) - ( (*it)->getPos() - mPlayer->getPos()-18 )/ 10 );
			}
			it++;
		}else if(mPlayer->getPos().y > 320) {
			//自機がY320以上になったら
			if((*it)->getState() > 0 ){
				(*it)->setCollect(true);

			}
			it++;
			
		}else if(approachBounds.intersects(defenceBounds)){
			//ある程度自機の近くに来たら
			if((*it)->getState() > 0 ){
				(*it)->setCollect(true);

			}
			it++;
			
		}else if(input->isKeyDown(GMKeyMaskShift)){
			//Shiftキーを押したら
			if((*it)->getState() > 0 ){
				(*it)->setCollect(true);
			}
			it++;
		}else {
			it++;
		}
	}
	
	
	
	
    mEnemyDamageEffect->step();
    
    if (GMRandom::NextInt(20) == 0) {
        BackStar* star = new BackStar();
        mStars.push_back(star);
    }
    
    mPlayer->move(input);
	
	mFrameCount++;
}

void PlayScene::setPlayerType(int type)
{
    mPlayerType = type;
}

int PlayScene::getPlayerType() const
{
    return mPlayerType;
}



