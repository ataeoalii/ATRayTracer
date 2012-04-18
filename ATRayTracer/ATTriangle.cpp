#include "ATTriangle.h"

// Constructor without color given.
ATTriangle::ATTriangle(ATVector3D v1, ATVector3D v2, ATVector3D v3)
{
	vertA = v1;
	vertB = v2;
	vertC = v3;
    
    color = ATColor(1.0f, 1.0f, 0.0f, 1.0f);
}

// Constructor with color
ATTriangle::ATTriangle(ATVector3D v1, ATVector3D v2, ATVector3D v3, ATColor col)
{
	vertA = v1;
	vertB = v2;
	vertC = v3;

	color = col;
}

// Copy constructor
ATTriangle::ATTriangle(const ATTriangle &copy)
{
	vertA = copy.vertA;
	vertB = copy.vertB;
	vertC = copy.vertC;
    
	color = copy.color;
}


// Default constructor.
ATTriangle::ATTriangle()
{
	vertA = ATVector3D();
	vertB = ATVector3D();
	vertC = ATVector3D();
    
    color = ATColor(1.0f, 1.0f, 0.0f, 1.0f);
}

// destructor
ATTriangle::~ATTriangle()
{
    
}

// determines where a ray intersects a triangle
void ATTriangle::intersect(ATRay ray, float *intersectPt1, float *intersectPt2) const
{
    // TODO: implement this
    *intersectPt2 = NAN;
    
    ATVector3D normal = ATVector3D::crossProduct(ATVector3D::subtractTwoVectors(vertB, vertA), ATVector3D::subtractTwoVectors(vertC, vertA));
    
    float denom = ATVector3D::dot(ray.direction, normal);
    if (fabsf(denom) < 0.00001f)
    {
        *intersectPt1 = NAN;
        return;
    }
    
    float numerator = ATVector3D::dot(ATVector3D::subtractTwoVectors(vertA, ray.origin), normal);
    
    float intersection = numerator / denom;
    
    if(intersection < 0.0f)
    {
        *intersectPt1 = NAN;
        return;
    }
    
    ATVector3D intersectVect = ray.direction;
    intersectVect.scaleVector(intersection);
    intersectVect = ATVector3D::addTwoVectors(ray.origin, intersectVect);
    
    float lambda1 = 0.0f;
    float lambda2 = 0.0f;
    float lambda3 = 0.0f;
    
    ATTriangle::GetBarycentricCoordinates(intersectVect, vertA, vertB, vertC, &lambda1, &lambda2, &lambda3);
    
    
    if(lambda1 >= 0.0f && lambda2 >= 0.0f && lambda3 >= 0.0f)
    {
        *intersectPt1 = intersection;
    }
    else 
    {
        *intersectPt1 = NAN;
    }
}

// determines the normal for a point in a triangle
ATVector3D ATTriangle::pointNormal(ATVector3D point) const
{ 
    return ATVector3D::normalize(ATVector3D::crossProduct(vertA, vertB));
}

// gets the color of the triangle
ATColor ATTriangle::getColor() const
{
    return color;
}

// Gets the barycentric coordinates (using lambda1, 2, and 3 as pointers to floats .)
void ATTriangle::GetBarycentricCoordinates(ATVector3D vect, ATVector3D atv1, ATVector3D atv2, ATVector3D atv3, float* lambda1, float* lambda2, float* lambda3)
{
    ATVector3D bmina = ATVector3D::subtractTwoVectors(atv2, atv1);
    ATVector3D cminb = ATVector3D::subtractTwoVectors(atv3, atv2);
    ATVector3D bminp = ATVector3D::subtractTwoVectors(atv2, vect);
    ATVector3D cminp = ATVector3D::subtractTwoVectors(atv3, vect);
    
    ATVector3D aminc = ATVector3D::subtractTwoVectors(atv1, atv3);
    ATVector3D aminp = ATVector3D::subtractTwoVectors(atv1, vect);

    
    
    ATVector3D denom = ATVector3D::crossProduct(bmina, cminb);
    ATVector3D lAnum = ATVector3D::crossProduct(bminp, cminb);
    ATVector3D lBnum = ATVector3D::crossProduct(cminp, aminc);
    ATVector3D lCnum = ATVector3D::crossProduct(aminp, bmina);
    
	float lambdaA = ATVector3D::magnitude(lAnum)/ATVector3D::magnitude(denom);
	float lambdaB = ATVector3D::magnitude(lBnum)/ATVector3D::magnitude(denom);
	float lambdaC = ATVector3D::magnitude(lCnum)/ATVector3D::magnitude(denom);
    
    if(ATVector3D::dot(lAnum, denom) >= 0.0f)
       *lambda1 = lambdaA;
    else {
        *lambda1 = lambdaA*-1.0f;
    }
    if(ATVector3D::dot(lBnum, denom) >= 0.0f)
        *lambda2 = lambdaB;
    else {
        *lambda2 = lambdaB*-1.0f;
    }
    if(ATVector3D::dot(lCnum, denom) >= 0.0f)
        *lambda3 = lambdaC;
    else {
        *lambda3 = lambdaC*-1.0f;
    }
    
}
