#include <math.h>
#include "core/vector.h"

Vector3I vectorFloatToInts(Vector3 v) {return (Vector3I){(int)v.x, (int)v.y, (int)v.z}; }
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

Vector3 normalize(Vector3 v) 
{
    float magnitude = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    if (magnitude == 0) return (Vector3){0, 0, 0};
    return (Vector3){v.x / magnitude, v.y / magnitude, v.z / magnitude};
}

Vector3 cross(Vector3 a, Vector3 b)
{
    return (Vector3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}