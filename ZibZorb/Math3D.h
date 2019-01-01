#pragma once
class Vector3
{
public:
	Vector3();

	Vector3(float x, float y, float z);

	~Vector3();
	float X;
	float Y;
	float Z;
};



struct PersProjInfo
{
	float FOV;
	float Width;
	float Height;

	float zNear;
	float zFar;

};


class Matrix4f
{
public:
	Matrix4f();
	static float ToRadian(float Degrees);
	static float ToDegrees(float Radians);
	~Matrix4f();

	float m[4][4];

	inline Matrix4f operator*(const Matrix4f& Right) const;

	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
	void InitPositionTransform(float x, float y, float z);
	void InitRotationTransform(float RotX, float RotY, float RotZ);
	void InitPerspectiveProj(const PersProjInfo& p);
};
