#pragma once
#include"geometry.h"
#include"TGAImage.h"
#include<vector>
using namespace std;
#pragma region The Line
/*
//绘制直线 vision1
void line(int x0, int y0, int x1, int y1, TGAImage& img, TGAColor color)
{
	for (float t = 0.; t < 1.; t += .01)//递增t来绘制一条直线
	{
		int x = x0 + (x1 - x0) * t;//每一次会在x-x1的方向上多绘制一个单位的像素
		int y = y0 + (y1 - y0) * t;//每一次会在y-y1的方向上多绘制一个单位的像素
		img.set(x, y, color);//设置像素颜色
	}//但这样太慢了，我们能否优化一下它呢？
}

void line2(int x0, int y0, int x1, int y1, TGAImage& img, TGAColor color)
{
	for (int x = x0; x <= x1; x++)
	{
		float t = (x - x0) / (float)(x1 - x0);//利用百分比来绘制
		int y = y0 * (1. - t) + y1 * t;//每一次在xy之间的直线上绘制的位置增加一定距离
		img.set(x, y, color);//设置像素颜色
	}
}
//这个问题在于我们绘制直线时不能只取决于点的顺序，并且需要保证x0一直小于x1；

void line3(int x0, int y0, int x1, int y1, TGAImage& img, TGAColor color)
{
	bool steep = false;//判断线段是否是陡的，如果是就调用绘制陡线段的代码，区分为y=x
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);//交换x0，y0位置
		std::swap(x1, y1);//交换x1，y1位置
		steep = true;//设置线段为陡
	}
	if (x0 > x1)//交换左右，如果x1<x2,那么就交换他们
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	for (int x = 0; x < x1; x++)//和2相同的绘制函数
	{
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1. - t) + y1 * t;
		if (steep)
		{
			img.set(y, x, color);
		}
		else
		{
			img.set(x, y, color);
		}
	}
}
//到现在已经完美了吗？不！我们还要继续优化！因为复制函数本身花费了大量的时间，我们需要进行重构和优化
void line4(int x0, int y0, int x1, int y1, TGAImage& img, TGAColor color)
{
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);

	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror = std::abs(dy) * 2;
	float error = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
		{
			img.set(y, x, color);
		}
		else
		{
			img.set(x, y, color);
		}
		error += derror;
		if (error > .5)
		{
			y += (y1 > y0 ? 1 : -1);
			error -= dx * 2;
		}
	}
	//直线是离散的，所以在绘制过程中本质是在x和y方向进行位移绘制，如果累计的差距超过了0.5，那么就会增加y值来贴近原有直线
	//本质上是一个波动增加的拟合过程
	//但这个算法依然可以进行优化，在编程中使用分支是一个不得已的举动，尤其是for循环中使用分支，因此，我们可以继续对该函数进行优化
}
void line5(int x0, int y0, int x1, int y1, TGAImage& img, TGAColor color)
{
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);

	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror = std::abs(dy) * 2;
	float error = 0;
	int y = y0;
	if (steep)
	{
		for (int x = x0; x <= x1; ++x)
		{
			img.set(y, x, color);
			error += derror;
			if (error > dx)
			{
				y += (y1 > y0 ? 1 : -1);
				error -= dx * 2;
			}
		}

	}
	else
	{
		for (int x = x0; x <= x1; ++x)
		{
			img.set(x, y, color);
			error += derror;
			if (error > dx)
			{
				y += (y1 > y0 ? 1 : -1);
				error -= dx * 2;
			}
		}

	}
}
*/
/*vector<int>interpolate(int i0, int d0, int i1, int d1)
{
	std::vector<int> values;
	int a =  (i0 - i1)/(d0 - d1);
	float d = d0;
	for (int i = i0; i<=i1;++i)
	{
		values.push_back(d);
		d += a;
	}
	return values;
}
*/

//重构后的line函数第六版
void line(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color)
{
	bool steep = false;
	if (std::abs(p0.x - p1.x) < std::abs(p0.y - p1.y))
	{
		std::swap(p0.x, p0.y);
		std::swap(p1.x, p1.y);
		steep = true;
	}
	if (p0.x > p1.x)
	{
		std::swap(p0.x, p1.x);
		std::swap(p0.y, p1.y);
	}
	//vector<int> ys = interpolate(p0.x, p0.y, p1.x, p1.y);
	for (int x = p0.x; x <= p1.x; x++)
	{
		
		float t = (x - p0.x) / (float)(p1.x - p0.x);
		int y = p0.y * (1.-t) + p1.y * t;
		if (steep)
		{
			image.set(y,x, color);
		}
		else 
		{
			image.set(x, y, color);
		}
	}
}
#pragma endregion