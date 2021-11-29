#ifndef ROTATION
#define ROTATION

#include "raylib.h"
Vector2 rotatePointVector2(Vector2 center, float angle, float base_x, float base_y)
{
	Vector2 point = (Vector2){base_x, base_y};
	float s = sin(angle);
	float c = cos(angle);

	float temp_x = (point.x), temp_y = (point.y);

	// translate point back to origin:
	temp_x -= center.x;
	temp_y -= center.y;

	// rotate point
	float xnew = temp_x * c - temp_y * s;
	float ynew = temp_x * s + temp_y * c;

	// translate point back:
	(point.x) = xnew + center.x;
	(point.y) = ynew + center.y;
	return point;
}

Vector2 rotate2PointVector3(float center_x, float center_y, float angle, float base_x, float base_y)
{
	Vector2 point = (Vector2){base_x, base_y};
	float s = sin(angle);
	float c = cos(angle);

	float temp_x = (point.x), temp_y = (point.y);

	// translate point back to origin:
	temp_x -= center_x;
	temp_y -= center_y;

	// rotate point
	//NEW X = xcos(theta) - ysin(theta)
	float xnew = temp_x * c - temp_y * s;
	float ynew = temp_x * s + temp_y * c;

	// translate point back:
	(point.x) = xnew + center_x;
	(point.y) = ynew + center_y;
	return point;
}

//roll pitch yaw
Vector3 rotate3DPoint(Vector3 center, Vector3 point, Vector3 rotation)
{
    float cosa = cos(rotation.y);
    float sina = sin(rotation.y);

    float cosb = cos(rotation.x);
    float sinb = sin(rotation.x);

    float cosc = cos(rotation.z);
    float sinc = sin(rotation.z);

    float Axx = cosa*cosb;
    float Axy = cosa*sinb*sinc - sina*cosc;
    float Axz = cosa*sinb*cosc + sina*sinc;

    float Ayx = sina*cosb;
    float Ayy = sina*sinb*sinc + cosa*cosc;
    float Ayz = sina*sinb*cosc - cosa*sinc;

    float Azx = -sinb;
    float Azy = cosb*sinc;
    float Azz = cosb*cosc;

	Vector3 ret;

    float px = point.x - center.x;
    float py = point.y - center.y;
    float pz = point.z - center.z;

        ret.x = Axx*px + Axy*py + Axz*pz;
        ret.y = Ayx*px + Ayy*py + Ayz*pz;
        ret.z = Azx*px + Azy*py + Azz*pz;
	return ret;
}

//roll pitch yaw
Vector3 rotate3DPointClamp(Vector3 center, Vector3 rotation, Vector3 point, float min, float max)
{
    float cosa = cos(rotation.y);
    float sina = sin(rotation.y);

    float cosb = cos(rotation.x);
    float sinb = sin(rotation.x);

    float cosc = cos(rotation.z);
    float sinc = sin(rotation.z);

    float Axx = cosa*cosb;
    float Axy = cosa*sinb*sinc - sina*cosc;
    float Axz = cosa*sinb*cosc + sina*sinc;

    float Ayx = sina*cosb;
    float Ayy = sina*sinb*sinc + cosa*cosc;
    float Ayz = sina*sinb*cosc - cosa*sinc;

    float Azx = -sinb;
    float Azy = cosb*sinc;
    float Azz = cosb*cosc;

	Vector3 ret;

    float px = point.x - center.x;
    float py = point.y - center.y;
    float pz = point.z - center.z;

        ret.x = Axx*px + Axy*py + Axz*pz;
        ret.y = Ayx*px + Ayy*py + Ayz*pz;
        ret.z = Azx*px + Azy*py + Azz*pz;
		ret.x = clamp(max, min, ret.x);
		ret.y = clamp(max, min, ret.y);
		ret.z = clamp(max, min, ret.z);
	return ret;
}
/*
This is the approximation of 1 degree
*/
#define APPROX_DEGREE_MULT (1.57 / 90)
//THE CURRENT APROXIMATE VALUE IS: [90 = 1.57f], 1.57 / 90 = ~0.0174
Vector3 rotatePointVector3Degrees(Vector3 center, Vector3 rotation, Vector3 points)
{
	Vector3 ret = rotate3DPoint(center, points, scaleVector(rotation, APPROX_DEGREE_MULT));
	// ret = scaleVector(ret, 0.0174);
	return ret;

}

Vector3 rotatePointVector3(Vector3 center, Vector3 rotation_in_degrees, Vector3 points)
{

	Vector3 ret = rotate3DPoint(center, points, rotation_in_degrees);
	return ret;

}
#endif