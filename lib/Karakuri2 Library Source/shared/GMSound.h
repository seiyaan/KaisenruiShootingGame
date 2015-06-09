/*
 *  GMSound.h
 *  Game Framework
 *
 *  Created by numata on 09/07/23.
 *  Copyright 2009 Satoshi Numata. All rights reserved.
 *
 */

#ifndef __GM_SOUND_H__
#define __GM_SOUND_H__


#include "GMObject.h"
#include "GMTypes.h"
#include <string>


void _GMInitSound();


/*!
    @class  GMSound
    @group  Audio
    <p>ゲームの効果音を再生するためのクラスです。</p>
 
    <h3>複数回の再生について</h3>
    <p>再生中に play() 関数を呼んだ場合、その再生は中断され、冒頭から再生が再開されます。</p>

    <h3>3次元の音場操作について</h3>
    <p>このクラスでは、3次元の音場に1人の聴取者（リスナ）と、複数の音源（ソース）があるものとしてモデル化されています。
    ひとつひとつのソースの位置は移動させることができ、それぞれの位置に応じて聞こえ方が変化します。またリスナの位置や向きも変化させることができます。</p>
 */
class GMSound : public GMObject {
    
private:
    std::string mFileName;
    void*       mSoundImpl;
    GMVector3D  mSourcePos;
    bool        mDoLoop;

public:
    /*!
        @task コンストラクタ
     */
    
    /*!
        @method GMSound
        @abstract ファイル名（拡張子含む）を指定して、効果音再生用のインスタンスを作成します。
        デフォルトではループ再生しませんが、第2引数に true を指定するとループ再生するようになります。
     */
    GMSound(const std::string& filename, bool doLoop = false);
    ~GMSound();
    
public:
    /*!
        @task 基本の操作
     */
    
    
    /*!
        @method getVolume
        現在設定されている音量を取得します。
     */
    double      getVolume() const;

    /*!
        @method isPlaying
        このサウンドが再生中かどうかをリターンします。
     */
    bool        isPlaying() const;

    /*!
        @method play
        @abstract サウンドの再生を開始します。
        このサウンドがすでに再生済みであった場合には、その再生が中断され、頭から再生が再開されます。
     */
    void        play();

    /*!
        @method stop
        @abstract サウンドの再生を中断します。
     */
    void        stop();
    
    /*!
        @method getPitch
        @abstract 現在設定されているピッチを取得します。
     */
    double      getPitch() const;
    
    /*!
        @method setPitch
        @abstract ピッチを設定します。
        <p>動作が保証されている値の範囲は、0.5〜2.0 です。</p>
        <p>デフォルトで設定されている値は 1.0 で、これが通常の再生速度となります。</p>
     */
    void        setPitch(double value);
    
    /*!
        @method setVolume
        音量を設定します。
     */
    void        setVolume(double value);
    
    /*!
        @task 3次元音場の操作（ソースの操作）
     */    
    
    /*!
        @method getSourcePos
        このサウンドの3次元音場での現在位置を取得します。
     */
    GMVector3D  getSourcePos() const;

    /*!
        @method setSourcePos
        このサウンドの3次元音場での位置を設定します。
     */
    void        setSourcePos(const GMVector3D &vec3);
    
public:
    /*!
        @task 3次元音場の操作（リスナの操作）
     */
    
    /*!
        @method getListenerHorizontalOrientation
        水平線上でのリスナの向きを取得します。
     */
    static  double      getListenerHorizontalOrientation();
    
    /*!
        @method getListenerPos
        3次元空間上でのリスナの現在位置を取得します。
     */
    static  GMVector3D  getListenerPos();
    
    /*!
        @method setListenerHorizontalOrientation
        水平線上でのリスナの向きを設定します。
     */
    static  void        setListenerHorizontalOrientation(double radAngle);
    
    /*!
        @method setListenerPos
        3次元空間上でのリスナの現在位置を設定します。
     */
    static  void        setListenerPos(double x, double y, double z);
    
    /*!
        @method setListenerPos
        3次元空間上でのリスナの現在位置を設定します。
     */
    static  void        setListenerPos(const GMVector3D& vec3);
        
#pragma mark -
#pragma mark Debug Support

public:
    std::string to_s() const;

};


#endif  //#ifndef __GM_SOUND_H__

