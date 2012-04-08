#ifndef _ATTRIANGLE_H_
#define _ATTRIANGLE_H_
#include "ATVector3D.h"
#include "ATColor.h"
#include "ATShape.h"

class ATTriangle : public ATShape
{

public:
	ATVector3D vertA, vertB, vertC;
	ATColor color;

    ATTriangle();
	ATTriangle(ATVector3D v1, ATVector3D v2, ATVector3D v3);
	ATTriangle(ATVector3D v1, ATVector3D v2, ATVector3D v3, ATColor col);
    ATTriangle(const ATTriangle &copy);
    ~ATTriangle();
    
    virtual void intersect(ATRay ray, float* intersectPt1, float* intersectPt2) const;
    
    virtual ATVector3D pointNormal(ATVector3D point) const;
    
    virtual ATColor getColor() const;
};

#endif