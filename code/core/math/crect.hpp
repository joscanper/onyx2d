#ifndef _CRECT_HPP_
#define _CRECT_HPP_
#pragma once

#include "cvector2.h"

class cRect
{
public:
    cRect( int x = 0, int y = 0, int w = 0, int h = 0 );
    ~cRect( void ) {};

    inline int Left( void ) const { return x; }
    inline int Right( void ) const { return x + w; }
    inline int Top( void ) const { return y; }
    inline int Bottom( void ) const { return y + h; }

    bool Contains( Vector2<float>& vVec ) const;
    bool Contains( int x, int y ) const;

    static cRect Empty();

    // Static methods below are derived from the cRectExtensions class
    // written in C#, released under the MSPL
    static Vector2<float> GetIntersectionDepth( const cRect& rectA, const cRect& rectB );
    static Vector2<float> GetBottomCenter( const cRect& rect );
    static Vector2<float> GetCenter( const cRect& rect );
    static float GetDistance( const cRect& rectA, const cRect& rectB);
    static Vector2<float> GetDirection( const cRect& rectA, const cRect& rectB);

    cRect& operator= ( const cRect& r2 );

    bool operator== ( const cRect& r2 ) const;
    bool operator!= ( const cRect& r2 ) const;

public:
    int x, y, w, h;
};

#endif // _CRECT_HPP_
