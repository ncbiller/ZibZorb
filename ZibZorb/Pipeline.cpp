#include <cmath>
#include "Vector3.h"
#include "Matrix4f.h"
#include "Pipeline.h"

Pipeline::Pipeline()
{
	mScale = Vector3(1.0f, 1.0f, 1.0f);
	mWorldPos = Vector3(0.0f, 0.0f, 0.0f);
	mRotation = Vector3(0.0f, 0.0f, 0.0f);
}


Pipeline::~Pipeline()
{
}

void Pipeline::Scale(float ScaleX, float ScaleY, float ScaleZ)
{
	mScale.X = ScaleX;
	mScale.Y = ScaleY;
	mScale.Z = ScaleZ;
}

void Pipeline::WorldPos(float x, float y, float z)
{
	mWorldPos.X = x;
	mWorldPos.Y = y;
	mWorldPos.Z = z;
}

void Pipeline::Rotate(float RotX, float RotY, float RotZ)
{
	mRotation.X = RotX;
	mRotation.Y = RotY;
	mRotation.Z = RotZ;
}

const Matrix4f * Pipeline::GetTrans()
{
	Matrix4f ScaleTrans, RotateTrans, TranslateTrans, PerspProjTrans;
	ScaleTrans.InitScaleTransform(mScale.X, mScale.Y, mScale.Z);
	RotateTrans.InitRotationTransform(mRotation.X, mRotation.Y, mRotation.Z);
	TranslateTrans.InitPositionTransform(mWorldPos.X, mWorldPos.Y, mWorldPos.Z);

	InitPerspectiveProj(PerspProjTrans);

	mTransform = TranslateTrans * RotateTrans * ScaleTrans;

	return &mTransform;
}

void Pipeline::InitPerspectiveProj(Matrix4f & m) const
{
	const float ar = m_persProj.Width / m_persProj.Height;
	const float zNear = m_persProj.zNear;
	const float zFar = m_persProj.zFar;
	const float zRange = zNear - zFar;
	const float tanHalfFOV = tanf(Matrix4f::ToRadian(m_persProj.FOV / 2.0));

	m.m[0][0] = 1.0f / (tanHalfFOV * ar);
	m.m[0][1] = 0.0f;
	m.m[0][2] = 0.0f;
	m.m[0][3] = 0.0f;

	m.m[1][0] = 0.0f;
	m.m[1][1] = 1.0f / tanHalfFOV;
	m.m[1][2] = 0.0f;
	m.m[1][3] = 0.0f;

	m.m[2][0] = 0.0f;
	m.m[2][1] = 0.0f;
	m.m[2][2] = (-zNear - zFar) / zRange;
	m.m[2][3] = 2.0f * zFar * zNear / zRange;

	m.m[3][0] = 0.0f;
	m.m[3][1] = 0.0f;
	m.m[3][2] = 1.0f;
	m.m[3][3] = 0.0f;
}
