/*
 *  GMStringSupport.h
 *  Karakuri2 iOS
 *
 *  Created by numata on 07/08/26.
 *  Copyright 2007 Satoshi Numata. All rights reserved.
 *
 */

#pragma once

#include <string>
#include <vector>


/*!
    @function   GMFS
    @group      System
    @abstract   C++版の sprintf() です。
    指定された書式に従って C++ 文字列を生成します。
 */
std::string GMFS(const char* format, ...);

/*!
    @function   GMSplitString
    @group      System
    @abstract   文字列を分割します。
    指定された区切り文字を使って文字列を分割し、分割された文字列を格納した vector をリターンします。
 */
std::vector<std::string> GMSplitString(const std::string& str, const std::string& separators);

