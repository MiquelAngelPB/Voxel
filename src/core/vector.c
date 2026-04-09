#include "core/vector.h"

Vector3 addVector3(Vector3 a, Vector3 b) { return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z}; }
Vector3 multVector3(Vector3 v, float scalar) { return (Vector3){v.x * scalar, v.y * scalar, v.z * scalar}; }
Vector3 clampVector3(Vector3 v, float min, float max) 
{
    Vector3 clamped;
    clamped.x = (v.x < min) ? min : (v.x > max) ? max : v.x;
    clamped.y = (v.y < min) ? min : (v.y > max) ? max : v.y;
    clamped.z = (v.z < min) ? min : (v.z > max) ? max : v.z;
    return clamped;
}