//
//  GMAppDelegate.mm
//  Karakuri2 Mac
//
//  Created by Satoshi Numata on 11/08/07.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GMAppDelegate.h"

#import "Globals.h"
#import "GMSoundImpl.h"


// Mac OS X 10.4 のサポート
#if (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
typedef long NSInteger;
typedef unsigned int NSUInteger;
#endif


static GMAppDelegate*   sInstance = nil;


@interface GMOpenGLView (Private)

- (void)prepareGame;
- (void)stopGame;

@end


@implementation GMAppDelegate

+ (GMAppDelegate*)sharedInstance
{
    return sInstance;
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    sInstance = self;
    
    _GMInitSound();
    _GMInitOpenAL();
    
    [glView prepareGame];

    GameMain* game = [glView game];
    std::string title = game->getTitle();
    [window setTitle:[NSString stringWithCString:title.c_str() encoding:NSUTF8StringEncoding]];
    
    [window setContentSize:NSMakeSize((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y)];
    [window center];
    [window makeKeyAndOrderFront:self];
    [window makeFirstResponder:glView];
    
    if (gGMHasGameStartError) {
        [NSTimer scheduledTimerWithTimeInterval:0 target:self selector:@selector(showStartError:) userInfo:nil repeats:NO];
    }
}

- (void)showStartError:(NSTimer *)timer
{
    NSAlert* alert = [NSAlert alertWithMessageText:@"Runtime Error"
                                     defaultButton:@"OK"
                                   alternateButton:nil
                                       otherButton:nil
                         informativeTextWithFormat:@"%s", gGMErrorStr.c_str(), nil];
    [alert beginSheetModalForWindow:window modalDelegate:self didEndSelector:@selector(alertDidEnd:returnCode:contextInfo:) contextInfo:nil];
}

- (void)alertDidEnd:(NSAlert*)alert returnCode:(NSInteger)returnCode contextInfo:(void*)contextInfo
{
    [NSApp terminate:self];
}
     
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
{
    return YES;
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender
{
    if (gGMHasGameStartError || gGMHasTerminatedWithError) {
        return NSTerminateNow;
    } else {
        [glView stopGame];
        _GMCleanUpOpenAL();
        return NSTerminateLater;
    }
}

- (NSWindow*)window
{
    return window;
}

@end

