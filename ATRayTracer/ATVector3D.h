#ifndef _ATVECTOR3D_H_
#define _ATVECTOR3D_H_

class ATVector3D
{

public:
    float x, y, z;
	ATVector3D();
	ATVector3D(const ATVector3D &copy);
	ATVector3D(float _x, float _y, float _z);
	ATVector3D(float _x, float _y);
    ~ATVector3D();

	void addVector(ATVector3D atv);
	void scaleVector(float scalar);
	void multiplyVector(ATVector3D atv);
    
	static ATVector3D multiplyTwoVectors(ATVector3D atv1, ATVector3D atv2);
	static ATVector3D addTwoVectors(ATVector3D atv1, ATVector3D atv2);
	static ATVector3D subtractTwoVectors(ATVector3D atv1, ATVector3D atv2);
	static ATVector3D crossProduct(ATVector3D atv1, ATVector3D atv2);
	static ATVector3D normalize(ATVector3D atv);
    static float dot(ATVector3D atv1, ATVector3D atv2);
};

#endif