#ifndef vector_h
#define vector_h

#ifndef M_PI
#define  M_PI  3.1415926535897932384626433
#endif

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    float x;
    float y;
} Vector2;

Vector3 addVector3(Vector3 a, Vector3 b);
Vector3 multVector3(Vector3 v, float scalar);
Vector3 clampVector3(Vector3 v, float min, float max);

#endif