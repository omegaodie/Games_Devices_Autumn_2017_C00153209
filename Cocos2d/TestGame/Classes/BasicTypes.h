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
	//const basic_Types::Vector2 _wall_hd = basic_Types::Vector2(113, 356);
	//const basic_Types::Vector2 _wall_sd = basic_Types::Vector2(65, 150);
	//const basic_Types::Vector2 _wall_shd = basic_Types::Vector2(140, 400);



	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	const int wall_sd_x = 65;
	const int wall_sd_y = 150;

	const int wall_hd_x = 113;
	const int wall_hd_y = 356;

	const int wall_shd_x = 140;
	const int wall_shd_y = 400;
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	const int back_sd_x = 4420;
	const int back_sd_y = 3984;

	const int back_hd_x = 7089;
	const int back_hd_y = 8000;

	const int back_shd_x = 10675;
	const int back_shd_y = 9960;
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	const int player_sd_x = 118;
	const int player_sd_y = 166;

	const int player_hd_x = 118;
	const int player_hd_y = 166;

	const int player_shd_x = 118;
	const int player_shd_y = 166;
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	const int zombie_sd_x = 118;
	const int zombie_sd_y = 166;

	const int zombie_hd_x = 118;
	const int zombie_hd_y = 166;

	const int zombie_shd_x = 118;
	const int zombie_shd_y = 166;
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	const int box_sd_x = 123;
	const int box_sd_y = 128;

	const int box_hd_x = 123;
	const int box_hd_y = 128;

	const int box_shd_x = 123;
	const int box_shd_y = 128;
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////


	enum Pattern
	{
		SWARM = 0,
		FLEE = 1,
		WANDER = 2, 
		FLOCK = 3, 
		SEEK = 4 
	};

	enum player_state {
		IDLE = 0,
		MOVING = 1,
		FIRING = 2,
		RELOADING = 3
	};

	enum zombie_state {
		WALKING = 0,
		RUNING = 1,
		HIT = 2,
		DEAD = 3,
		ARISE = 4
	};

	enum _Anim_State {
		up = 0,
		down = 1,
		left = 2,
		left_up = 3,
		left_down = 4,
		right = 5,
		right_up = 6,
		right_down = 7,
	};

	enum _graphics_setting {
		SD = 0,
		HD = 1,
		SHD = 2
	};


	enum _Weights
	{
		_PLAYER = 2,
		_ENEMY_1 = 5,
		_ENEMY_3 = 8,
		_ENEMY_4 = 1
	};


	class Vector2 {
	public:
		float x, y;
		Vector2(float _x = 0, float _y = 0);
		Vector2(cocos2d::Vec2 v) : x(v.x), y(v.y) {};
		float length() const;
		Vector2 normalise();
		Vector2 operator+ (const Vector2 & other) const;
		Vector2 operator+ (const cocos2d::Vec2 & other) const;
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
		float dotProduct(Vector2 v);
		float crossProduct(Vector2 v);
		float component(Vector2 v);
		Vector2  getInertia(float x, Vector2 position);
		Vector2  getInertia(float x, cocos2d::Vec2 position);
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
