#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"


#include"line.h"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const int width = 1920;
const int height = 1080;
int main()
{
	TGAImage image(width,height,TGAImage::RGB);
	Vec2i p1(0, 0);
	Vec2i p2(1920, 1080);
	Vec2i p3(0, 1080);
	Vec2i p4(1920, 0);
	line(p1, p2,image, red);
	line(p3, p4, image, green);
	image.write_tga_file("Line.tga");
	return 0;
}