#include "ATRaster3D.h"
using namespace std;

ATRaster3D::ATRaster3D(int _width, int _height)
{
	height = _height;
	width = _width;
	rasterPixels = new ATColor[height*width];
	size = height*width;
	depths = new float[height*width];
	for(int i=0; i < height*width; i++)
	{
		depths[i] = -FLT_MAX;
	}

}

ATRaster3D::ATRaster3D(const ATRaster3D &copy)
{
	height = copy.height;
	width = copy.width;
	size = copy.size;

	rasterPixels = new ATColor[height*width];
	depths = new float[height*width];

	for(unsigned int i=0; i<height*width; i++)
	{
		rasterPixels[i] = copy.rasterPixels[i];
		depths[i] = copy.depths[i];
	}
}

ATRaster3D::ATRaster3D()
{
	height = 500;
	width = 500;
	rasterPixels = new ATColor[height*width];
	depths = new float[height*width];
	size = height*width;

	for(int i=0; i < height*width; i++)
	{
		depths[i] = -FLT_MAX;
	}
}


// Destructor
ATRaster3D::~ATRaster3D()
{

}


// Sets the color of a specific pixel
void ATRaster3D::setPixel(int index, ATColor color)
{
	if(index < size)
	{
		rasterPixels[index] = color;
	}
}


// Gets the barycentric coordinates (using lambda1,2, and 3 as pointers to float.
void ATRaster3D::GetBarycentricCoordinates(ATVector3D vect, ATVector3D atv1, ATVector3D atv2, ATVector3D atv3, float* lambda1, float* lambda2, float* lambda3)
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


float ATRaster3D::getDepth(unsigned int index)
{
 	return depths[index];
}
	
ATColor ATRaster3D::getPixel(int index)
{
	return rasterPixels[index];
}
	
void ATRaster3D::setDepth(unsigned int index, float value)
{
	depths[index] = value;
}

void ATRaster3D::blendPixel(int index, ATColor color, float alpha)
{
	ATColor thisColor = rasterPixels[index];
	color.scaleColor(alpha);
	thisColor.scaleColor(1.0f - alpha);
	ATColor finColor = ATColor::addTwoColors(color, thisColor);
	setPixel(index, finColor);
}

// Saves image in raster to PPM format
void ATRaster3D::saveToPPM(ATColor pixels[], int width, int height, char* path)
{
    // Open a file for writing
    FILE* f = fopen(path, "w");
    if (f == NULL)
    {
        printf("Couldn't open file %s for writing", path);
        return;
    }
    
    // Write out information required by plain PPM header definition
    fprintf(f, "P3\n");
    fprintf(f, "%i %i\n", width, height);
    fprintf(f, "%i\n", 255);
    
    // Write out pixel information
    
	int index = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            ATColor color = pixels[index];
			fprintf(f, "%i ", color.getredB());
            fprintf(f, "%i ", color.getgreenB());
			fprintf(f, "%i ", color.getblueB());
			index++;
        }
        fprintf(f, "\n");
    }
}

// Saves image in raster BMP format
void ATRaster3D::saveToBMP(ATColor rasterPixels[], int rasterWidth, int rasterHeight, char* path)
{
    //BMP (Windows V3)
    //Offset    Size    Description
    //0         2       the magic number used to identify the BMP file: 0x42 0x4D (Hex code points for B and M in big-endian order)
    //2         4       the size of the BMP file in bytes
    //6         2       reserved; actual value depends on the application that creates the image
    //8         2       reserved; actual value depends on the application that creates the image
    //10        4       the offset, i.e. starting address, of the byte where the bitmap data can be found.
    //14        4       the size of this header (40 bytes)
    //18        4       the bitmap width in pixels (signed integer).
    //22        4       the bitmap height in pixels (signed integer).
    //26        2       the number of color planes being used. Must be set to 1.
    //28        2       the number of bits per pixel, which is the color samplesPerPixel of the image. Typical values are 1, 4, 8, 16, 24 and 32.
    //30        4       the compression method being used. See the next table for a list of possible values.
    //34        4       the image size. This is the size of the raw bitmap data (see below), and should not be confused with the file size.
    //38        4       the horizontal resolution of the image. (pixel per meter, signed integer)
    //42        4       the vertical resolution of the image. (pixel per meter, signed integer)
    //46        4       the number of colors in the color palette, or 0 to default to 2n.
    //50        4       the number of important colors used, or 0 when every color is important; generally ignored.

    //Open file for writing
    FILE* file = fopen(path, "wb");
    if (file == NULL)
        return;
    
    //Define header data
    uint16_t magicNumber = 0x4D42;
    uint16_t reserved0 = 0;//0x4D41;
    uint16_t reserved1 = 0;//0x5454;
    uint32_t dataOffset = 54;
    uint32_t infoHeaderSize = 40;
    uint32_t width = rasterWidth;
    uint32_t height = rasterHeight;
    uint16_t colorPlanes = 1;
    uint16_t bitsPerPixel = 32;
    uint32_t compression = 0;
    uint32_t dataSize = width * height * bitsPerPixel / 8;
    uint32_t horizontalResolution = 2835;
    uint32_t verticalResolution = 2835;
    uint32_t paletteColorCount = 0;
    uint32_t importantPaletteColorCount = 0;
    uint32_t fileSize = 54 + dataSize;
    
    //Write BMP header (Windows V3, 32bbp)
    fwrite(&magicNumber, sizeof(magicNumber), 1, file);
    fwrite(&fileSize, sizeof(fileSize), 1, file);
    fwrite(&reserved0, sizeof(reserved0), 1, file);
    fwrite(&reserved1, sizeof(reserved1), 1, file);
    fwrite(&dataOffset, sizeof(dataOffset), 1, file);
    fwrite(&infoHeaderSize, sizeof(infoHeaderSize), 1, file);
    fwrite(&width, sizeof(width), 1, file);
    fwrite(&height, sizeof(height), 1, file);
    fwrite(&colorPlanes, sizeof(colorPlanes), 1, file);
    fwrite(&bitsPerPixel, sizeof(bitsPerPixel), 1, file);
    fwrite(&compression, sizeof(compression), 1, file);
    fwrite(&dataSize, sizeof(dataSize), 1, file);
    fwrite(&horizontalResolution, sizeof(horizontalResolution), 1, file);
    fwrite(&verticalResolution, sizeof(verticalResolution), 1, file);
    fwrite(&paletteColorCount, sizeof(paletteColorCount), 1, file);
    fwrite(&importantPaletteColorCount, sizeof(importantPaletteColorCount), 1, file);
    
    //Write BMP body (XXRRGGBB)
    for (int y = rasterHeight - 1; y >= 0; y--)
    {
        for (int x = 0; x < rasterWidth; x++)
        {
			uint32_t color = rasterPixels[y*rasterWidth + x].getColor();

            fwrite(&color, 1, sizeof(color), file);
        }
    }
    
    //Cleanup
    fclose(file);
}

