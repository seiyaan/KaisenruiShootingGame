/*
 *  GMMusic.mm
 *  Game Framework
 *
 *  Created by numata on 09/07/23.
 *  Copyright 2009 Satoshi Numata. All rights reserved.
 *
 */

#include "GMMusic.h"
#include "GMException.h"

#if TARGET_OS_IPHONE
#import <AVFoundation/AVFoundation.h>
#else
#import <Foundation/Foundation.h>
#if (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
#include "GMSoundImpl.h"
#endif
#endif


GMMusic::GMMusic(const std::string& filename, bool loop)
{
    mFileName = filename;
    mDoLoop = loop;

    mIsPausing = false;
    mImpl = nil;
    mBGMID = -1;
    
    NSString* filenameStr = [NSString stringWithCString:filename.c_str() encoding:NSUTF8StringEncoding];

#if (MAC_OS_X_VERSION_MAX_ALLOWED >= 1060 || TARGET_OS_IPHONE)
    NSURL* url = [[NSBundle mainBundle] URLForResource:[filenameStr stringByDeletingPathExtension] withExtension:[filenameStr pathExtension]];
#else
    NSString* path = [[NSBundle mainBundle] pathForResource:[filenameStr stringByDeletingPathExtension] ofType:[filenameStr pathExtension]];
    NSURL* url = [NSURL fileURLWithPath:path];
#endif
    if (url) {
#if TARGET_OS_IPHONE
        NSError* error = nil;
        mImpl = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
        [(AVAudioPlayer*)mImpl prepareToPlay];
#elif (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
        mImpl = [[GMSoundImpl alloc] initWithName:filenameStr doLoop:(loop? YES: NO)];
#else
        mImpl = [[NSSound alloc] initWithContentsOfURL:url byReference:YES];
#endif
    }
    if (!mImpl) {
        throw GMException("Failed to load a music file: \"%s\"", filename.c_str());
    }
    if (loop) {
#if TARGET_OS_IPHONE
        ((AVAudioPlayer*)mImpl).numberOfLoops = -1;
#elif (MAC_OS_X_VERSION_MAX_ALLOWED >= 1050)
        // In Mac OS X 10.4 version, loop mode is already set.
        [(NSSound*)mImpl setLoops:YES];
#endif
    }
}


GMMusic::~GMMusic()
{
    stop();

    if (mImpl) {
#if TARGET_OS_IPHONE
        [(AVAudioPlayer*)mImpl release];
#elif (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
        [(GMSoundImpl*)mImpl release];
#else
        [(NSSound*)mImpl release];
#endif
        mImpl = nil;
    }
}

bool GMMusic::isPlaying() const
{
    if (mImpl) {
#if TARGET_OS_IPHONE
        return ((AVAudioPlayer*)mImpl).playing;
#elif (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
        return [(GMSoundImpl*)mImpl isPlaying];
#else
        return [(NSSound*)mImpl isPlaying];
#endif
    }
    return false;
}

void GMMusic::play()
{
    if (mImpl) {
        if (mIsPausing) {
#if TARGET_OS_IPHONE
            [(AVAudioPlayer*)mImpl play];
#elif (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
            [(GMSoundImpl*)mImpl play];
#else
            [(NSSound*)mImpl resume];
#endif
        } else {
#if TARGET_OS_IPHONE
            [(AVAudioPlayer*)mImpl play];
#elif (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
            [(GMSoundImpl*)mImpl play];
#else
            [(NSSound*)mImpl play];
#endif
        }
    }

    mIsPausing = false;
}

void GMMusic::pause()
{
    if (mImpl) {
#if TARGET_OS_IPHONE
        [(AVAudioPlayer*)mImpl pause];
#elif (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
        [(GMSoundImpl*)mImpl pause];
#else
        [(NSSound*)mImpl pause];
#endif
    }
    
    mIsPausing = true;
}

void GMMusic::stop()
{
    if (mImpl) {
#if TARGET_OS_IPHONE
        [(AVAudioPlayer*)mImpl pause];
        ((AVAudioPlayer*)mImpl).currentTime = 0.0;
#elif (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
        [(GMSoundImpl*)mImpl stop];
#else
        [(NSSound*)mImpl stop];
        [(NSSound*)mImpl setCurrentTime:0.0];
#endif
    }
    
    mIsPausing = false;
}

double GMMusic::getVolume() const
{
    if (mImpl) {
#if TARGET_OS_IPHONE
        return (double)((AVAudioPlayer*)mImpl).volume;
#elif (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
        return (double)[(GMSoundImpl*)mImpl volume];
#else
        return (double)[(NSSound*)mImpl volume];
#endif
    }
    return 0.0;
}

void GMMusic::setVolume(double value)
{
    if (mImpl) {
#if TARGET_OS_IPHONE
        ((AVAudioPlayer*)mImpl).volume = (float)value;
#elif (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
        [(GMSoundImpl*)mImpl setVolume:(float)value];
#else
        [(NSSound*)mImpl setVolume:(float)value];
#endif
    }
}

std::string GMMusic::to_s() const
{
    return "<music>(file=\"" + mFileName + "\", loop=" + (mDoLoop? "true": "false") + ")";
}

