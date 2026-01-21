#version 330 core

//variables
vec2 uv = gl_FragCoord.xy / vec2(800, 400) * 2.0 - 1.0;
uniform vec3 camPos;
uniform vec2 camRot;
vec3 rayOrigin = camPos;
vec3 rayDirection = normalize(vec3(uv, 1));
vec3 point = vec3(rayOrigin.xy, 0);
out vec4 outColor;

//methods
void rotateCamY(float angle);
float sphereSDF(float radius, vec3 center, vec3 point);
float cubeSDF(vec3 point, vec3 scale);

//main
void main()
{
   rotateCamY(camRot.x);

   float t = 0;
   rayOrigin = camPos;
   float dist = 0.0;
   for (int i = 0; i < 100; i++)
   {
      point = rayOrigin + rayDirection * t;

      float sphere = sphereSDF(1.0, vec3(0, 0, 1), point);
      float cube = cubeSDF(point, vec3(1, 1, 1));
      dist = min(sphere, cube);
      t += dist;

      if (dist < 0.001 || t > 100.0) break;
   }

   outColor = vec4(dist, dist, dist, 1);
}

void rotateCamY(float angle)
{
   rayDirection.x =  rayDirection.x * cos(angle) + rayDirection.z * sin(angle);
   rayDirection.y = rayDirection.y;
   rayDirection.z = -rayDirection.x * sin(angle) + rayDirection.z * cos(angle);
}

float sphereSDF(float radius, vec3 center, vec3 point)
{
   return length(point - center) - radius;
}

float cubeSDF(vec3 point, vec3 scale)
{
  return length(max(abs(point) - scale, 0.0));
}