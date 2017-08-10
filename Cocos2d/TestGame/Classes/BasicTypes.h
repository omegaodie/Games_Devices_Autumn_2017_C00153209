#pragma once
//THIS CODE IS THE ammended WORK OF GITHUB USER OloinMilsom ///
// ITS SIMPLE EFFECTIVE CODE SO I SAW NO REASON TO CHANGE IT///
//USED without licence ///

#pragma once
#include <math.h>
#include "cocos2d.h"

namespace basic_Types
{
	const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;


	class Vector2 {
	public:
		float x, y;
		Vector2(float _x = 0, float _y = 0);
		Vector2(cocos2d::Vec2 v) : x(v.x), y(v.y) {};
		float length() const;
		Vector2 normalise();
		Vector2 operator+ (const Vector2 & other) const;
		Vector2 operator- (const Vector2 & other) const;
		Vector2 operator* (const float & scalar);
		Vector2 operator/ (const float & scalar);
		void operator+= (const Vector2 & other);
		void operator-= (const Vector2 & other);
		void operator*= (const float & scalar);
		void operator/= (const float & scalar);
		void limit(float max) { if (length() > max) { *this = normalise() * max; } };
		float angleBetween(cocos2d::Vec2 v);
		float angleBetween(Vector2 v);
	};


	class Size {
	public:
		float w, h;
		Size(float _w = 0, float  _h = 0);
		Size(Vector2 v);
	};

	class Colour {
	public:
		int r, g, b, a;
		Colour(int _r = 255, int  _g = 255, int _b = 255, int  _a = 255) :r(_r), g(_g), b(_b), a(_a) {};
		void setAll(int r, int g, int b, int a);
	};

	class Rect {
	public:
		Vector2 pos;
		Size size;
		Rect(cocos2d::Rect r) : pos(r.getMinX(), r.getMinY()), size(r.size.width, r.size.height) {};
		Rect(Vector2 p, Size s) :pos(p), size(s.w, s.h) {};
		Rect(float x = 0, float y = 0, float w = 1, float h = 1) :pos(x, y), size(w, h) {};
		bool Contains(Rect r);
		bool Contains(Vector2 p);
		bool Contains(cocos2d::Vec2 p);
		bool Intersects(Rect r);
		bool IntersectsX(Vector2 p);
		bool IntersectsY(Vector2 p);
	};

	class Tile {
	public:
		Rect _rec;
		int id;
		Tile(Rect v = NULL, int i = 0) : _rec(v), id(i) {};

	};
}
