#include "Transform.h"

//http://www.chadvernon.com/blog/resources/directx9/transformations/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Default Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Transform::Transform()
{
	Reset();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Reset the matrices to default position.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Transform::Reset()

{
	D3DXMatrixIdentity(&m_translate);
	D3DXMatrixIdentity(&m_rotate);
	D3DXMatrixIdentity(&m_scale);
	D3DXMatrixIdentity(&m_transform);
	m_rotationX = m_rotationY = m_rotationZ = 0.0f;

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Absolute translation
Parameters:
[in] x – X position
[in] y – Y position
[in] z – Z position
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Transform::TranslateAbs(float x, float y, float z) 

{
	m_translate._41 = x;
	m_translate._42 = y;
	m_translate._43 = z;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Relative translation
Parameters:
[in] x – X amount
[in] y – Y amount
[in] z – Z amount
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Transform::TranslateRel(float x, float y, float z)

{
	m_translate._41 += x;
	m_translate._42 += y;
	m_translate._43 += z;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Absolute rotation
Parameters:
[in] x – X radians
[in] y – Y radians
[in] z – Z radians
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Transform::RotateAbs(float x, float y, float z)

{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	D3DXMatrixRotationYawPitchRoll(&m_rotate, y, x, z);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Relative rotation
Parameters:
[in] x – X radians
[in] y – Y radians
[in] z – Z radians
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Transform::RotateRel(float x, float y, float z) 

{
	m_rotationX += x;
	m_rotationY += y;
	m_rotationZ += z;
	D3DXMatrixRotationYawPitchRoll(&m_rotate, m_rotationY, m_rotationX, m_rotationZ);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Absolute scale.
Parameters:
[in] x – X size
[in] y – Y size
[in] z – Z size
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Transform::ScaleAbs(float x, float y, float z) 

{
	m_scale._11 = x;
	m_scale._22 = y;
	m_scale._33 = z;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Relative scale.
Parameters:
[in] x – X size
[in] y – Y size
[in] z – Z size
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Transform::ScaleRel(float x, float y, float z) 

{
	m_scale._11 += x;
	m_scale._22 += y;
	m_scale._33 += z;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Get the transformation matrix
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
D3DXMATRIX* Transform::GetTransform()

{
	m_transform = m_scale * m_rotate * m_translate;
	return &m_transform;
}