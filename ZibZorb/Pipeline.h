#pragma once

class Matrix4f;

class Vector3;

//structure to hold projection transformation parameters



class Pipeline
{
public:
	Pipeline();
	~Pipeline();
	void Scale(float ScaleX, float ScaleY, float ScaleZ);

	void WorldPos(float x, float y, float z);

	void Rotate(float RotX, float RotY, float RotZ);

	const Matrix4f * GetTrans();
	


	void SetPerspectiveProj(const PersProjInfo& p)
	{
		m_persProjInfo = p;
	}

private:
	Vector3 mScale;
	Vector3 mWorldPos;
	Vector3 mRotation;
	Matrix4f mTransform;
	PersProjInfo m_persProjInfo;
};

