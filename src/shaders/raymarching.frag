#version 330 core

//variables
uniform vec3 camPos;
uniform vec3 camRot;
uniform vec3 forward;
uniform vec2 resolution;

out vec4 outColor;

float fov = 1;
vec2 uv = gl_FragCoord.xy / resolution * 2.0 - 1.0;
vec3 testLight = vec3(0, 1, 0);
vec3 worldUp = vec3(0, 1, 0);

vec3 rayOrigin = camPos;
vec3 right = normalize(cross(worldUp, forward));
vec3 up = normalize(cross(right, forward));
vec3 rayDirection = normalize(forward * fov + right * uv.x + up * uv.y);
vec3 point;

//methods
float sdf(vec3 point);
float sphereSDF(float radius, vec3 center, vec3 point);
float cubeSDF(vec3 point, vec3 scale);
float repeatSphere(vec3 point, vec3 scale);
vec3 raymarch(vec2 off);

//main
void main()
{
   vec3 p = raymarch(vec2(0));
   float e = 0.001; //epsilon for normal calculation

   vec3 normal = normalize(vec3(
      sdf(p + vec3(e, 0, 0)) - sdf(p - vec3(e, 0, 0)),
      sdf(p + vec3(0, e, 0)) - sdf(p - vec3(0, e, 0)),
      sdf(p + vec3(0, 0, e)) - sdf(p - vec3(0, 0, e))
   ));

   float light = dot(normal, normalize(p - testLight)); //assuming worldUp is already normalized
   outColor = vec4(light, light, light, 1);
}

vec3 raymarch(vec2 off)
{
   vec3 point = vec3(rayOrigin.xy, 0);
   float t = 0;
   vec3 origin = camPos;
   vec3 rayDir = rayDirection;
   float dist = 0;
   for (int i = 0; i < 64; i++)
   {
      point = origin + vec3(rayDir.xy + off, rayDir.z) * t;
      dist = sdf(point);
      t += dist;

      if (dist < 0.001 || t > 100.0) break;
   }

   return point;
}

float sdf(vec3 point)
{
   return min(cubeSDF(point, vec3(1.0)), repeatSphere(point, vec3(1.0)));
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