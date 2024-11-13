#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"


#include"line.h"
Model* model;
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const int width = 1080;
const int height = 1080;
int main(int argc,char** argv)
{
    if (2 == argc) {
       model = new Model(argv[1]);
    }
    else{
       model = new Model("obj/AppleForEasyRender.obj");
    }
	TGAImage image(width,height,TGAImage::RGB);
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j = 0; j < 3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);
            int x0 = (v0.x + 1.) * width / 2;
            int y0 = (v0.y + 1.) * height / 2;
            int x1 = (v1.x + 1.) * width / 2;
            int y1 = (v1.y + 1.) * height / 2;
            Vec2i v0v = { x0,y0 };
            Vec2i v1v = { x1,y1 };
            line(v0v,v1v,image, white);
        }
    }
    image.flip_vertically();
	image.write_tga_file("AppleWithLine.tga");
	return 0;
}