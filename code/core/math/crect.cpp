#include "crect.hpp"
#include <stdlib.h>

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
cRect::cRect( int x, int y, int w, int h )
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

//-----------------------------------------------------------------------------
// Purpose: Check if cRect contains a 2D vector
//-----------------------------------------------------------------------------
bool cRect::Contains( Vector2<float>& vVec ) const
{
    if ( ( vVec.x >= x )&&
         ( vVec.x <= x + w ) &&
         ( vVec.y >= y ) &&
         ( vVec.x <= y + h ) )
    {
        return true;
    }
    else
        return false;
}

//-----------------------------------------------------------------------------
// Purpose: Check if cRect contains a set of coords
//-----------------------------------------------------------------------------
bool cRect::Contains( int x, int y ) const
{
    if ( ( x >= this->x )&&
        ( x <= this->x + this->w ) &&
        ( y >= this->y ) &&
        ( x <= this->y + this->h ) )
    {
        return true;
    }
    else
        return false;
}

//-----------------------------------------------------------------------------
// Purpose: Return an empty cRect
//-----------------------------------------------------------------------------
cRect cRect::Empty()
{
    return cRect();
}

//-----------------------------------------------------------------------------
// Purpose: Get intersection depth between two cRects
//-----------------------------------------------------------------------------
Vector2<float> cRect::GetIntersectionDepth( const cRect& rectA, const cRect& rectB )
{
    // Calculate half sizes.
    float halfWidthA = rectA.w / 2.0f;
    float halfHeightA = rectA.h / 2.0f;
    float halfWidthB = rectB.w / 2.0f;
    float halfHeightB = rectB.h / 2.0f;

    // Calculate centers.
    Vector2<float> centerA(rectA.x + halfWidthA, rectA.y + halfHeightA);
    Vector2<float> centerB(rectB.x + halfWidthB, rectB.y + halfHeightB);

    // Calculate current and minimum-non-intersecting distances between centers.
    float distanceX = centerA.x - centerB.x;
    float distanceY = centerA.y - centerB.y;
    float minDistanceX = halfWidthA + halfWidthB;
    float minDistanceY = halfHeightA + halfHeightB;

    // If we are not intersecting at all, return (0, 0).
    if ( abs(distanceX) >= minDistanceX || abs(distanceY) >= minDistanceY )
    {
        Vector2<float> a;
        a.SetZero();
        return a;
    }

    // Calculate and return intersection depths.
    float depthX = distanceX > 0 ? minDistanceX - distanceX : -minDistanceX - distanceX;
    float depthY = distanceY > 0 ? minDistanceY - distanceY : -minDistanceY - distanceY;
    return Vector2<float>(depthX, depthY);
}

//-----------------------------------------------------------------------------
// Purpose: Gets the position of the center of the bottom edge of the cRect.
//-----------------------------------------------------------------------------
Vector2<float> cRect::GetBottomCenter(const cRect& rect)
{
    return Vector2<float>( (float)(rect.x + rect.w / 2.0f), (float)(rect.y + rect.h) );
}

//-----------------------------------------------------------------------------
// Purpose: Gets the position of the center point of a cRect
//-----------------------------------------------------------------------------
Vector2<float> cRect::GetCenter(const cRect& rect)
{
    return Vector2<float>( (float)(rect.x + rect.w / 2.0f), (float)(rect.y + rect.h / 2.0f) );
}

//-----------------------------------------------------------------------------
// Purpose: Gets the floating point distance between the center point
//          of one cRect and the center point of another.
//-----------------------------------------------------------------------------
float cRect::GetDistance( const cRect& rectA, const cRect& rectB )
{

    return Vector2<float>::Distance(GetCenter(rectA), GetCenter(rectB));
}

//-----------------------------------------------------------------------------
// Purpose: Gets the unit vector from one cRect to another
//-----------------------------------------------------------------------------
Vector2<float> cRect::GetDirection( const cRect& rectA, const cRect& rectB )
{
    Vector2<float> direction = GetCenter(rectA) - GetCenter(rectB);
    direction.Normalize();
    return direction;
}

cRect& cRect::operator= ( const cRect& r2 )
{
    if (this == &r2)
        return *this;

    x = r2.x;
    y = r2.y;
    w = r2.w;
    h = r2.h;

    return *this;
}

bool cRect::operator== ( const cRect& r2 ) const
{
    return ((w == r2.w) && (h == r2.h));
}

bool cRect::operator!= ( const cRect& r2 ) const
{
    return !((w == r2.w) && (h == r2.h));
}
