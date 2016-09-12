#pragma once
class Matrix4f
{
public:
	Matrix4f();
	float ToRadian(float Degrees);
	float ToDegrees(float Radians);
	~Matrix4f();
	
	float m[4][4];

	inline Matrix4f operator*(const Matrix4f& Right) const;

	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
	void InitPositionTransform(float x, float y, float z);
	void InitRotationTransform(float RotX, float RotY, float RotZ);
};

