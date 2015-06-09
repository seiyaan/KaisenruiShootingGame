//
//  GMRenderTarget2D.cpp
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/09/01.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMRenderTarget2D.h"

#include <iostream>
#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#else
#include <OpenGL/OpenGL.h>
#endif


GMRenderTarget2D::GMRenderTarget2D(int width, int height) throw(GMInvalidOperationException, GMOutOfMemoryException)
    : GMTexture2D(width, height)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, __getName());

#if GL_ARB_framebuffer_object
    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, __getName(), 0);
#elif GL_EXT_framebuffer_object
    glGenFramebuffersEXT(1, &mFramebuffer);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFramebuffer);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, __getName(), 0);
#else
    std::cerr << "GMRenderTarget2D::GMRenderTarget2D(GMRenderTarget2D::GMRenderTarget2D(int, int) - FBO is not supported!!" << std::endl;
#endif

    glBindTexture(GL_TEXTURE_2D, 0);
}

GMRenderTarget2D::GMRenderTarget2D(int width, int height, GMTextureFormat format) throw(GMInvalidOperationException, GMOutOfMemoryException)
    : GMTexture2D(width, height, format)
{
    glBindTexture(GL_TEXTURE_2D, __getName());

#if GL_ARB_framebuffer_object
    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, __getName(), 0);
#elif GL_EXT_framebuffer_object
    glGenFramebuffersEXT(1, &mFramebuffer);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFramebuffer);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, __getName(), 0);
#else
    std::cerr << "GMRenderTarget2D::GMRenderTarget2D(GMRenderTarget2D::GMRenderTarget2D(int, int,GMTextureFormat) - FBO is not supported!!" << std::endl;
#endif

    glBindTexture(GL_TEXTURE_2D, 0);
}

GMRenderTarget2D::~GMRenderTarget2D()
{
    if (mFramebuffer) {
#if GL_ARB_framebuffer_object
        glDeleteFramebuffers(1, &mFramebuffer);
#elif GL_EXT_framebuffer_object
        glDeleteFramebuffersEXT(1, &mFramebuffer);
#else
        std::cerr << "GMRenderTarget2D::~GMRenderTarget2D() - FBO is not supported!!" << std::endl;
#endif
        mFramebuffer = 0;
    }
}

GLuint GMRenderTarget2D::__getFramebuffer() const
{
    return mFramebuffer;
}

