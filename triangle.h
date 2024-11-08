#pragma once
#include<iostream>
#include"TGAImage.h"
#include"line.h"
#include"geometry.h"
#include<vector>

Vec3f barycentric(const Vec2i& A, const Vec2i& B, const Vec2i& C, const Vec2i& P) {
	Vec2i v0 = Vec2i(B.x - A.x, B.y - A.y);
	Vec2i v1 = Vec2i(C.x - A.x, C.y - A.y);
	Vec2i v2 = Vec2i(P.x - A.x, P.y - A.y);

	int d00 = v0.x * v0.x + v0.y * v0.y;
	int d01 = v0.x * v1.x + v0.y * v1.y;
	int d11 = v1.x * v1.x + v1.y * v1.y;
	int d20 = v2.x * v0.x + v2.y * v0.y;
	int d21 = v2.x * v1.x + v2.y * v1.y;

	float denom = d00 * d11 - d01 * d01;
	float v = (d11 * d20 - d01 * d21) / denom;
	float w = (d00 * d21 - d01 * d20) / denom;
	float u = 1.0f - v - w;

	if (u < 0 && v < 0 && w < 0)
		return Vec3f(-1, 1, 0);
	
	return Vec3f(u, v, w);
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color)
{
	if (t0.y == t1.y && t0.y == t2.y)return;

	if (t0.y > t1.y) std::swap(t0, t1);
	if (t0.y > t2.y)std::swap(t0, t2);
	if (t1.y > t2.y)std::swap(t1, t2);
	int total_height = t2.y - t0.y;
	for (int i = 0; i<= total_height; i++)
	{
		bool second_half = i > t1.y - t0.y || t1.y == t0.y;
		int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
		float alpha = (float)i/ total_height;
		float beta = (float)(i -(second_half ? t2.y-t1.y:0)) / segment_height;
		Vec2i A = t0 + (t2 - t0) * alpha;
		Vec2i B = second_half?t1+(t2-t1)*beta:t0 + (t1 - t0) * beta;
		if (A.x > B.x) std::swap(A, B);
		for (int j = A.x; j <= B.x; j++)
		{
			image.set(j, t0.y+i, color);
		}
	}
}
