//
//  GMAppDelegate.h
//  Karakuri2 Mac
//
//  Created by Satoshi Numata on 11/08/07.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GMOpenGLView.h"


@interface GMAppDelegate : NSObject {
    IBOutlet NSWindow*       window;
    IBOutlet GMOpenGLView*   glView;
}

+ (GMAppDelegate*)sharedInstance;

- (NSWindow*)window;

@end
