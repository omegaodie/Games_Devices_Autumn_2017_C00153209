#include "BasicTypes.h"
//THIS CODE IS THE ammended WORK OF GITHUB USER OloinMilsom ///
// ITS SIMPLE EFFECTIVE CODE SO I SAW NO REASON TO CHANGE IT///
//USED without licence ///

using namespace basic_Types;
#pragma region Vector

Vector2::Vector2(float _x, float _y)
	:x(_x),
	y(_y) {
};

float Vector2::length() const {
	return (float)sqrt((x*x) + (y*y));
};

Vector2 Vector2::normalise() {
	float l = length();
	float xn = x / l;
	float yn = y / l;
	return Vector2(xn, yn);
}

Vector2 Vector2::operator+ (const Vector2 & other) const {
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator- (const Vector2 & other) const {
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator* (const float &scalar) {
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/ (const float &scalar) {
	return Vector2(x / scalar, y / scalar);
}

void Vector2::operator+= (const Vector2 & other) {
	x += other.x;
	y += other.y;
}

void Vector2::operator-= (const Vector2 & other) {
	x -= other.x;
	y -= other.y;
}

void Vector2::operator*= (const float & scalar) {
	x *= scalar;
	y *= scalar;
}

void Vector2::operator/= (const float & scalar) {
	x /= scalar;
	y /= scalar;
}

float Vector2::angleBetween(cocos2d::Vec2 v)
{
	float angle_rads = atan2(v.y - y, v.x - x);
	return angle_rads;
}

float Vector2::angleBetween(Vector2 v)
{
	float angle_rads = atan2(v.y - y, v.x - x);
	return angle_rads;
}

#pragma endregion Vector

#pragma region Size

Size::Size(float _w, float  _h)
	:w(_w),
	h(_h) {
};

Size::Size(Vector2 v)
	:w(v.x),
	h(v.y) {
};

#pragma endregion Size


#pragma region Rect

bool Rect::Contains(Rect r) {
	if ((r.pos.x >= pos.x) && (r.pos.x + r.size.w < pos.x + size.w)) {
		if ((r.pos.y >= pos.y) && (r.pos.y + r.size.h < pos.y + size.h)) {
			return true;
		}
	}
	return false;
};

bool Rect::Contains(Vector2 p) {
	if ((p.x >= pos.x) && (p.x <= pos.x + size.w)) {
		if ((p.y >= pos.y) && (p.y <= pos.y + size.h)) {
			return true;
		}
	}
	return false;
}
bool basic_Types::Rect::Contains(cocos2d::Vec2 p)
{
	if ((p.x >= pos.x) && (p.x <= pos.x + size.w)) {
		if ((p.y >= pos.y) && (p.y <= pos.y + size.h)) {
			return true;
		}
	}
	return false;
};

bool Rect::Intersects(Rect r) {
	if ((r.pos.x + r.size.w >= pos.x) && (r.pos.x < pos.x + size.w)) {
		if ((r.pos.y + r.size.h >= pos.y) && (r.pos.y < pos.y + size.h)) {
			return true;
		}
	}
	return false;
};

bool Rect::IntersectsX(Vector2 p) {
	if ((p.x >= pos.x) && (p.x <= pos.x + size.w)) {
		return true;
	}
	return false;
};

bool Rect::IntersectsY(Vector2 p) {
	if ((p.y >= pos.y) && (p.y <= pos.y + size.h)) {
		return true;
	}
	return false;
};

#pragma endregion Rect

#pragma region Colour

void Colour::setAll(int ir, int ig, int ib, int ia) {
	r = ir;
	b = ib;
	g = ig;
	a = ia;
};



#pragma endregion Rect