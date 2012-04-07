#include "ATLight.h"


ATLight::ATLight(ATVector3D pos, ATColor col)
{
	position = pos;
	color = col;
}


ATLight::~ATLight(void)
{
}

ATColor ATLight::getColor()
{
	return color;
}

ATVector3D ATLight::getPosition()
{
	return position;
}

void ATLight::setColor(float a, float r, float g, float b)
{
	color.setColor(a, r, g, b);
}

void ATLight::setPosition(float x, float y, float z)
{
	position = ATVector3D(x, y, z);
}