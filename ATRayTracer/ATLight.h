#ifndef _ATLIGHT_H_
#define _ATLIGHT_H_
#include "ATVector3D.h"
#include "ATColor.h"

class ATLight
{
public:
    ATColor color;
	ATVector3D position;
    
    ATLight();
	ATLight(ATVector3D pos, ATColor col);
    ATLight(const ATLight& copy);
	~ATLight();
};
#endif