#include <raylib.h>
#include "MathmaticalOperations.h"
Vector3 scaleVector(Vector3 vec, float scale)
{
	return (Vector3){vec.x * scale, vec.y * scale, vec.z * scale};
}

Vector3 addVectors(Vector3 a, Vector3 b)
{
	return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 multiplyVectors(Vector3 a, Vector3 b)
{
	return (Vector3){a.x * b.x, a.y * b.y, a.z * b.z};
}

Vector3 invertVector(Vector3 a)
{
	return (Vector3){-a.x, -a.y, -a.z};
}

Vector3 findMidPoint(Vector3 a, Vector3 b)
{
	return (Vector3){(a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2};
}

Vector3 clampVector(Vector3 vector, float max, float min)
{
	return (Vector3){clamp(max, min, vector.x), clamp(max, min, vector.y), clamp(max, min, vector.z)};
}
