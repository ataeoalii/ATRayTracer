#include "ATColor.h"
#include <iostream>

// Default constructor makes black
ATColor::ATColor()
{
	alphaB	= 255;
	redB	= 0;
	greenB	= 0;
	blueB	= 0;
}


// Constructor for color created by 32 bit number ARGB format
ATColor::ATColor(uint32_t colorValueARGB)
{
	alphaB	= (colorValueARGB & 0xFF000000) >> 24;
	redB	= (colorValueARGB & 0x00FF0000) >> 16;
	greenB	= (colorValueARGB & 0x0000FF00) >> 8;
	blueB	= colorValueARGB & 0x000000FF;

}

// Constructor with 8bit channels for ARGB
ATColor::ATColor(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	alphaB	= a;
	redB	= r;
	greenB	= g;
	blueB	= b;
}

// Constructor with floats from 0.0f to 1.0f for ARGB
ATColor::ATColor(float a, float r, float g, float b)
{
	alphaB = (uint8_t)(a*255.0f);
	redB = (uint8_t)(r*255.0f);
	greenB = (uint8_t)(g*255.0f);
	blueB = (uint8_t)(b*255.0f);
}

// Constructor with RGB floats and alpha set to full
ATColor::ATColor(float r, float g, float b)
{
    alphaB = 255.0f;
    redB = (uint8_t)(r*255.0f);
	greenB = (uint8_t)(g*255.0f);
	blueB = (uint8_t)(b*255.0f);
}

// Copy constructor
ATColor::ATColor(const ATColor &copy)
{
	alphaB = copy.alphaB;
	redB   =   copy.redB;
	greenB = copy.greenB;
	blueB  =  copy.blueB;
}

// returns red floating pt value
float ATColor::getredF()
{
	return (float) redB / 255;
}

// returns green floating pt value
float ATColor::getgreenF()
{
	return (float) (greenB) / 255.0f;
}

// returns blue floating pt value
float ATColor::getblueF()
{
	return (float) (blueB) / 255.0f;
}

// returns alpha floating pt value
float ATColor::getalphaF()
{
	return (float) (alphaB) / 255.0f;
}

// returns red bits
uint8_t ATColor::getredB()
{
	return redB;
}

// returns green bits
uint8_t ATColor::getgreenB()
{
	return greenB;
}

// returns blue bits
uint8_t ATColor::getblueB()
{
	return blueB;
}

// returns alpha bits
uint8_t ATColor::getalphaB()
{
	return alphaB;
}

// scales each channel by a float
void ATColor::scaleColor(float scalar)
{
	alphaB*=scalar;
	redB*=scalar;
	greenB*=scalar;
	blueB*=scalar;
    

}

// clamps a color
void ATColor::clampColor()
{
    if(alphaB > 255)
        alphaB = 255;
    if(redB > 255)
        redB = 255;
    if(greenB > 255)
        greenB = 255;
    if(blueB > 255)
        blueB = 255;
    
    if(alphaB < 0)
        alphaB = 0;
    if(redB < 0)
        redB = 0;
    if(greenB < 0)
        greenB = 0;
    if(blueB < 0)
        blueB = 0;
}

// adds two colors together
ATColor ATColor::addTwoColors(ATColor col1, ATColor col2)
{
	float fa = col1.getalphaF() + col2.getalphaF();
	float fr = col1.getredF() + col2.getredF();
	float fg = col1.getgreenF() + col2.getgreenF();
	float fb = col1.getblueF() + col2.getblueF();

	if(fa>1.0f) fa = 1.0f;
	if(fr>1.0f) fr = 1.0f;
	if(fg>1.0f) fg = 1.0f;
	if(fb>1.0f) fb = 1.0f;

	ATColor newColor(fa, fr, fg, fb);
	return newColor;
}

// sets the red bits
void ATColor::setredB(uint8_t r)
{
	redB = r;
}

// sets the green bits
void ATColor::setgreenB(uint8_t g)
{
	greenB = g;
}

// sets the blue bits
void ATColor::setblueB(uint8_t b)
{
	blueB = b;
}

// sets the alpha bits
void ATColor::setalphaB(uint8_t a)
{
	alphaB = a;
}

// sets the color to the 8 bit values ARGB
void ATColor::setColor(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	alphaB = a;
	redB = r;
	greenB = g;
	blueB = b;

}

// sets the color the floating pt values ARGB
void ATColor::setColor(float a, float r, float g, float b)
{
	alphaB = (uint8_t)(a*255.0f);
	redB = (uint8_t)(r*255.0f);
	greenB = (uint8_t)(g*255.0f);
	blueB = (uint8_t)(b*255.0f);
}

// returns the 32 bit color value
uint32_t ATColor::getColor()
{
	if (alphaB > 255) alphaB = 255;
	if (redB > 255) redB = 255;
	if (greenB > 255) greenB = 255;
	if (blueB > 255) blueB = 255;

	if (alphaB < 0) alphaB = 0;
	if (redB < 0) redB = 0;
	if (greenB < 0) greenB = 0;
	if (blueB < 0) blueB = 0;


	return alphaB << 24 | redB << 16 | greenB << 8 | blueB;
}


// multiplies two colors together
ATColor ATColor::multiply(ATColor col1, ATColor col2)
{
	float alf    = col1.getalphaF() * col2.getalphaF();
	float red    = col1.getredF()   *   col2.getredF();
	float green  = col1.getgreenF() * col2.getgreenF();
	float blue   = col1.getblueF()  *  col2.getblueF();

	ATColor atc(alf, red, green, blue);

	return atc;

}