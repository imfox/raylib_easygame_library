#include "Utils.h"
#include <raymath.h>

void ds::Utils::rotatePointByZero(Vector2& p, float angle)
{
	return rotatePoint({ 0,0 }, p, angle);
}

void ds::Utils::rotatePoint(Vector2 o, Vector2& p, float angle)
{
	auto r = DEG2RAD * angle;
	auto x = ((p.x - o.x) * cos(r) - (p.y - o.y) * sin(r) + o.x);
	auto y = ((p.x - o.x) * sin(r) + (p.y - o.y) * cos(r) + o.y);
	p.x = x;
	p.y = y;
}
