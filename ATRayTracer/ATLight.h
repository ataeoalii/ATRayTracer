#ifndef _ATLIGHT_H_
#define _ATLIGHT_H_
#include "ATVector3D.h"
#include "ATColor.h"

class ATLight
{
private:
	ATColor color;
	ATVector3D position;
public:
	ATLight(ATVector3D pos, ATColor col);
	~ATLight(void);

	ATColor getColor();
	ATVector3D getPosition();
	void setPosition(float x, float y, float z);
	void setColor(float a, float r, float g, float b);
};
#endif