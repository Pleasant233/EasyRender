#pragma once
#include"geometry.h"
#include"TGAImage.h"
#include<vector>
using namespace std;
#pragma region The Line
/*
//����ֱ�� vision1
void line(int x0, int y0, int x1, int y1, TGAImage& img, TGAColor color)
{
	for (float t = 0.; t < 1.; t += .01)//����t������һ��ֱ��
	{
		int x = x0 + (x1 - x0) * t;//ÿһ�λ���x-x1�ķ����϶����һ����λ������
		int y = y0 + (y1 - y0) * t;//ÿһ�λ���y-y1�ķ����϶����һ����λ������
		img.set(x, y, color);//����������ɫ
	}//������̫���ˣ������ܷ��Ż�һ�����أ�
}

void line2(int x0, int y0, int x1, int y1, TGAImage& img, TGAColor color)
{
	for (int x = x0; x <= x1; x++)
	{
		float t = (x - x0) / (float)(x1 - x0);//���ðٷֱ�������
		int y = y0 * (1. - t) + y1 * t;//ÿһ����xy֮���ֱ���ϻ��Ƶ�λ������һ������
		img.set(x, y, color);//����������ɫ
	}
}
//��������������ǻ���ֱ��ʱ����ֻȡ���ڵ��˳�򣬲�����Ҫ��֤x0һֱС��x1��

void line3(int x0, int y0, int x1, int y1, TGAImage& img, TGAColor color)
{
	bool steep = false;//�ж��߶��Ƿ��Ƕ��ģ�����Ǿ͵��û��ƶ��߶εĴ��룬����Ϊy=x
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);//����x0��y0λ��
		std::swap(x1, y1);//����x1��y1λ��
		steep = true;//�����߶�Ϊ��
	}
	if (x0 > x1)//�������ң����x1<x2,��ô�ͽ�������
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	for (int x = 0; x < x1; x++)//��2��ͬ�Ļ��ƺ���
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
//�������Ѿ��������𣿲������ǻ�Ҫ�����Ż�����Ϊ���ƺ����������˴�����ʱ�䣬������Ҫ�����ع����Ż�
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
	//ֱ������ɢ�ģ������ڻ��ƹ����б�������x��y�������λ�ƻ��ƣ�����ۼƵĲ�೬����0.5����ô�ͻ�����yֵ������ԭ��ֱ��
	//��������һ���������ӵ���Ϲ���
	//������㷨��Ȼ���Խ����Ż����ڱ����ʹ�÷�֧��һ�������ѵľٶ���������forѭ����ʹ�÷�֧����ˣ����ǿ��Լ����Ըú��������Ż�
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

//�ع����line����������
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