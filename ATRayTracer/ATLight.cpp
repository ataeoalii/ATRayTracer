#include "ATLight.h"

// default constructor
ATLight::ATLight()
{
    position = ATVector3D(0.0f, 10.0f, 0.0f);
    color = ATColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// constructor specifies position/color
ATLight::ATLight(ATVector3D pos, ATColor col)
{
	position = pos;
	color = col;
}

// copy constructor
ATLight::ATLight(const ATLight& copy)
{
    position = copy.position;
    color = copy.color;
}

// destructor
ATLight::~ATLight()
{
    
}
