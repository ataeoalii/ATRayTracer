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
    *intersectPt1 = NAN;
    *intersectPt2 = NAN;
    ATVector3D u = ATVector3D::subtractTwoVectors(vertB, vertA);
    ATVector3D v = ATVector3D::subtractTwoVectors(vertC, vertA);
    ATVector3D n = ATVector3D::crossProduct(u, v);
    
    ATVector3D dir = ray.direction;
    ATVector3D w;          // ray vectors
    float     r, a, b;             // params to calc ray-plane intersect
    
    ATVector3D w0 = ATVector3D::subtractTwoVectors(ray.origin, vertA);

    a = -(ATVector3D::dot(n,w0));
    b = ATVector3D::dot(n,dir);
    
    if (fabsf(b) < 0.00001f) {     // ray is parallel to triangle plane            // ray lies in triangle plane
            return;           // ray disjoint from plane
    }
    
    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)                   // ray goes away from triangle
        return;                  // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect
    dir.scaleVector(r);
    ATVector3D intersection = ATVector3D::addTwoVectors(ray.origin, dir);           // intersect point of ray and plane
    
    // is I inside T?
    float    udotu, udotv, vdotv, wdotu, wdotv, denom;
    udotu = ATVector3D::dot(u,u);
    udotv = ATVector3D::dot(u,v);
    vdotv = ATVector3D::dot(v,v);
    w = ATVector3D::subtractTwoVectors(intersection, vertA);
    wdotu = ATVector3D::dot(w,u);
    wdotv = ATVector3D::dot(w,v);
    
    denom = udotv * udotv - udotu * vdotv;
    
    // get and test parametric coords
    float s, t;
    s = (udotv * wdotv - vdotv * wdotu) / denom;
    if (s < 0.0 || s > 1.0)        // I is outside T
        return;
    t = (udotv * wdotu - udotu * wdotv) / denom;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
        return;
    
    if(r<=1.0f)
    *intersectPt1 = r;                     // I is in T
    
    
    
//    // TODO: implement this
//    *intersectPt2 = NAN;
//    
//    ATVector3D normal = ATVector3D::crossProduct(ATVector3D::subtractTwoVectors(vertB, vertA), ATVector3D::subtractTwoVectors(vertC, vertA));
//    
//    float denom = ATVector3D::dot(ray.direction, normal);
//    if (fabsf(denom) < 0.00001f)
//    {
//        *intersectPt1 = NAN;
//        return;
//    }
//    
//    float numerator = ATVector3D::dot(ATVector3D::subtractTwoVectors(vertA, ray.origin), normal);
//    
//    float intersection = numerator / denom;
//    
//    if(intersection < 0.0f)
//    {
//        *intersectPt1 = NAN;
//        return;
//    }
//    
//    ATVector3D intersectVect = ray.direction;
//    intersectVect.scaleVector(intersection);
//    intersectVect = ATVector3D::addTwoVectors(ray.origin, intersectVect);
//    
//    float lambda1 = 0.0f;
//    float lambda2 = 0.0f;
//    float lambda3 = 0.0f;
//    
//    ATTriangle::GetBarycentricCoordinates(intersectVect, vertA, vertB, vertC, &lambda1, &lambda2, &lambda3);
//    
//    
//    if(lambda1 >= 0.0f && lambda2 >= 0.0f && lambda3 >= 0.0f)
//    {
//        *intersectPt1 = intersection;
//    }
//    else 
//    {
//        *intersectPt1 = NAN;
//    }
}

// determines the normal for a point in a triangle
ATVector3D ATTriangle::pointNormal(ATVector3D point) const
{ 
    float lambda1 = 0.0f;
    float lambda2 = 0.0f;
    float lambda3 = 0.0f;
    
    ATTriangle::GetBarycentricCoordinates(point, vertA, vertB, vertC, &lambda1, &lambda2, &lambda3);
    ATVector3D normA = ATVector3D::normalize(ATVector3D::crossProduct(vertA, vertB));
    normA.scaleVector(lambda1);
    ATVector3D normB = ATVector3D::normalize(ATVector3D::crossProduct(vertB, vertC));
    normB.scaleVector(lambda2);
    ATVector3D normC = ATVector3D::normalize(ATVector3D::crossProduct(vertC, vertA));
    normC.scaleVector(lambda3);
    
    return ATVector3D::normalize(ATVector3D::addTwoVectors(normA, ATVector3D::addTwoVectors(normB, normC)));
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
    
    if(ATVector3D::dot(denom, lAnum) > 0.0f)
        *lambda1 = lambdaA;
    else {
        *lambda1 = -MAXFLOAT;
    }
    
    if(ATVector3D::dot(denom, lBnum) > 0.0f)
        *lambda2 = lambdaB;
    else {
        *lambda2 = -MAXFLOAT;
    }
    
    if(ATVector3D::dot(denom, lCnum) > 0.0f)
        *lambda3 = lambdaC;
    else {
        *lambda3 = -MAXFLOAT;
    }

    
}
