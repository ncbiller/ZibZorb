
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
	Matrix4f ScaleTrans, RotateTrans, TranslateTrans;
	ScaleTrans.InitScaleTransform(mScale.X, mScale.Y, mScale.Z);
	RotateTrans.InitRotationTransform(mRotation.X, mRotation.Y, mRotation.Z);
	TranslateTrans.InitPositionTransform(mWorldPos.X, mWorldPos.Y, mWorldPos.Z);
	mTransform = TranslateTrans * RotateTrans * ScaleTrans;

	return &mTransform;
}
