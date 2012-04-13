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
    return ATVector3D::normalize(ATVector3D::crossProduct(vertA, vertC));
}

// gets the color of the triangle
ATColor ATTriangle::getColor() const
{
    return color;
}

// Gets the barycentric coordinates (using lambda1, 2, and 3 as pointers to floats .)
void ATTriangle::GetBarycentricCoordinates(ATVector3D vect, ATVector3D atv1, ATVector3D atv2, ATVector3D atv3, float* lambda1, float* lambda2, float* lambda3)
{
	float lambdaA = ((atv2.y - atv3.y)*(vect.x - atv3.x) + (atv3.x - atv2.x)*(vect.y - atv3.y)) / 
    ((atv2.y - atv3.y)*(atv1.x - atv3.x) + ((atv3.x - atv2.x) * (atv1.y - atv3.y)));
    
	float lambdaB = ((atv3.y - atv1.y)*(vect.x - atv3.x) + (atv1.x - atv3.x)*(vect.y - atv3.y)) / 
    ((atv2.y - atv3.y)*(atv1.x - atv3.x) + ((atv3.x - atv2.x) * (atv1.y - atv3.y)));
    
	float lambdaC = 1.0f - lambdaA - lambdaB;
    
    *lambda1 = lambdaA;
    *lambda2 = lambdaB;
    *lambda3 = lambdaC;
    
    
}
