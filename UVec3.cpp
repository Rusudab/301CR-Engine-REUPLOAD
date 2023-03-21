#include "UVec3.h"

UVec3::~UVec3()
{

}

UVec3::UVec3(float xf, float yf, float zf)
{
	x = xf;
	y = yf;
	z = zf;
}

void UVec3::UVec3i(int x, int y, int z)
{
	xi = x;
	yi = y;
	zi = z;
}

// These 4 methods are being used to convert to/from bullet/irrlicht vectors into my own vector 3
UVec3 UVec3::frombtVec3(btVector3 vectorbt)
{
	return UVec3(vectorbt.getX(), vectorbt.getY(), vectorbt.getZ());
}
btVector3 UVec3::tobtVec3(UVec3 uvec)
{
	return btVector3(uvec.x, uvec.y, uvec.z);
}
UVec3 UVec3::fromirrVec3(irr::core::vector3df irrvec)
{
	return UVec3(irrvec.X, irrvec.Y, irrvec.Z);
}
irr::core::vector3df UVec3::toirrVec3(UVec3 uvec)
{
	return irr::core::vector3df(uvec.x, uvec.y, uvec.z);
}
