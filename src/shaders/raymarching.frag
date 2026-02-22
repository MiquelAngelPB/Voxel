#version 330 core

//variables
uniform vec3 camPos;
uniform vec3 camRot;
uniform vec3 forward;
uniform vec2 resolution;

out vec4 outColor;

float fov = 1;
vec2 uv = gl_FragCoord.xy / resolution * 2.0 - 1.0;
vec3 worldUp = vec3(0, 1, 0);

vec3 rayOrigin = camPos;
vec3 right = normalize(cross(worldUp, forward));
vec3 up = normalize(cross(right, forward));
vec3 rayDirection = normalize(forward * fov + right * uv.x + up * uv.y);
vec3 point;

//methods
float sphereSDF(float radius, vec3 center, vec3 point);
float cubeSDF(vec3 point, vec3 scale);
float repeatSphere(vec3 point, vec3 scale);
vec3 raymarch(vec2 off);

//main
void main()
{
   vec3 p1 = raymarch(vec2(0));
   vec3 p2 = raymarch(vec2(0.001, 0));
   vec3 p3 = raymarch(vec2(0, 0.001));

   vec3 surfaceP1 = p1 - p2;
   vec3 surfaceP2 = p1 - p3;

   vec3 normal = normalize(cross(surfaceP1, surfaceP2));

   float light = dot(worldUp, normal); //assuming worldUp is already normalized
   //
   outColor = vec4(light, light, light, 1);
}

vec3 raymarch(vec2 off)
{
   point = vec3(rayOrigin.xy, 0);
   float t = 0;
   rayOrigin = camPos;
   float dist = 0.0;
   for (int i = 0; i < 100; i++)
   {
      point = rayOrigin + vec3(rayDirection.xy + off, rayDirection.z) * t;

      float sphere = sphereSDF(1.0, vec3(0, 0, 1), point);
      float cube = cubeSDF(point, vec3(1, 1, 1));
      dist = min(cubeSDF(point, vec3(1.0)), repeatSphere(point, vec3(1.0))); //min(sphere, cube);
      t += dist;

      if (dist < 0.001 || t > 100.0) break;
   }

   return point;
}

float sphereSDF(float radius, vec3 center, vec3 point)
{
   return length(point - center) - radius;
}

float cubeSDF(vec3 point, vec3 scale)
{
  return length(max(abs(point) - scale, 0.0));
}

float repeatSphere(vec3 point, vec3 scale)
{
   vec3 q = point - scale * round(point / scale);
   return sphereSDF(0.1, vec3(0, 0, 0), q);
}