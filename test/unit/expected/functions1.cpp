/* This file is auto generated by C-Sugar @author Steven Dellamore 
URL = https://github.com/Dellamoresteven/C-Sugar */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
#include <list>
#include <sys/stat.h>
#include <unistd.h>
#include <functional>
#include <map>
#include <sstream>
#include <iterator>
#include <string>

auto autoRet(  ) {
    // x @TODO
    int x = 6;
}

auto withParams( int x, bool y ) {
}

int intRet(  ) {
}

template <typename T, typename U >
int intRetWithParams( T steven, U john ) {
}

int intRetWithParams1( int steven, std::string john ) {
}

template <typename T, typename U >
int intWithNoTypeParam( T a, U b ) {
}

template <typename T, typename U >
int intWithNoTypeParam1( T a, U b ) {
}

template <typename T >
int intWithAny1TypeParam( T a, T b ) {
}

template <typename T, typename U >
int intWithAny12TypeParam( T a, U b ) {
}

template <typename T, typename U, typename G, typename H >
int intWithAny12TypeParam( T a, U b, G c, H d ) {
}

template <typename T, typename U, typename G, typename H >
auto add( T a, U b, G c, H d ) {
    return (a + b + c + d);
}

int normalFunction(int x, int y) {
    return 7;
}

int normalVoidFunction() {
    return 7;
}