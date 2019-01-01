
#define _USE_MATH_DEFINES

#include "Math3D.h"
#include <cmath>
#include <iostream>


Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z) : X(x), Y(y), Z(z)
{
}


Vector3::~Vector3()
{
}


Matrix4f::Matrix4f()
{
}

inline float Matrix4f::ToRadian(float Degrees) {
	return Degrees * M_PI / 180.0f;
}

inline float Matrix4f::ToDegrees(float Radians) {
	return Radians * 180.0f / M_PI;
}

inline Matrix4f Matrix4f::operator*(const Matrix4f& Right) const
{
	Matrix4f Ret;
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			Ret.m[i][j] = m[i][0] * Right.m[0][j] +
				m[i][1] * Right.m[1][j] +
				m[i][2] * Right.m[2][j] +
				m[i][3] * Right.m[3][j];
		}
	}

	return Ret;
}
void Matrix4f::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ) {

	m[0][0] = ScaleX;	m[0][1] = 0.0f;		m[0][2] = 0.0f;		m[0][3] = 0.0f;
	m[1][0] = 0.0f;     m[1][1] = ScaleY;	m[1][2] = 0.0f;		m[1][3] = 0.0f;
	m[2][0] = 0.0f;		m[2][1] = 0.0f;		m[2][2] = ScaleZ;	m[2][3] = 0.0f;
	m[3][0] = 0.0f;     m[3][1] = 0.0f;		m[3][2] = 0.0f;		m[3][3] = 1.0f;


}
void Matrix4f::InitPositionTransform(float x, float y, float z) {
	m[0][0] = 1.0f;		m[0][1] = 0.0f;		m[0][2] = 0.0f;		m[0][3] = x;
	m[1][0] = 0.0f;     m[1][1] = 1.0f;		m[1][2] = 0.0f;		m[1][3] = y;
	m[2][0] = 0.0f;		m[2][1] = 0.0f;		m[2][2] = 1.0f;		m[2][3] = z;
	m[3][0] = 0.0f;     m[3][1] = 0.0f;		m[3][2] = 0.0f;		m[3][3] = 1.0f;

}
void Matrix4f::InitRotationTransform(float RotX, float RotY, float RotZ) {
	Matrix4f rx, ry, rz;

	const float x = ToRadian(RotX);
	const float y = ToRadian(RotY);
	const float z = ToRadian(RotZ);

	rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f; rx.m[0][2] = 0.0f; rx.m[0][3] = 0.0f;
	rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
	rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x); rx.m[2][3] = 0.0f;
	rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f; rx.m[3][2] = 0.0f; rx.m[3][3] = 1.0f;

	ry.m[0][0] = cosf(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y); ry.m[0][3] = 0.0f;
	ry.m[1][0] = 0.0f; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f; ry.m[1][3] = 0.0f;
	ry.m[2][0] = sinf(y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y); ry.m[2][3] = 0.0f;
	ry.m[3][0] = 0.0f; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f; ry.m[3][3] = 1.0f;

	rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
	rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z); rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
	rz.m[2][0] = 0.0f; rz.m[2][1] = 0.0f; rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
	rz.m[3][0] = 0.0f; rz.m[3][1] = 0.0f; rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

	*this = rz * ry * rx;
}

void Matrix4f::InitPerspectiveProj(const PersProjInfo& p)
{
	const float ar = p.Width / p.Height;
	const float zNear = p.zNear;
	const float zFar = p.zFar;
	const float zRange = zNear - zFar;
	const float tanHalfFOV = tanf(ToRadian(p.FOV / 2.0));

	m[0][0] = 1.0f / (tanHalfFOV * ar);
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f / tanHalfFOV;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = (-zNear - zFar) / zRange;
	m[2][3] = 2.0f * zFar * zNear / zRange;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 1.0f;
	m[3][3] = 0.0f;
}


Matrix4f::~Matrix4f()
{
}
