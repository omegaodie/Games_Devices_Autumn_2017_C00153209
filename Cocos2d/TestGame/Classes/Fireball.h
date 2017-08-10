#pragma once

#include "cocos2d.h"
#include "BasicTypes.h"
#include "GameData.h"

enum _Direction {
	up = 1,
	down = 2, 
	left = 3,
	right = 4
};

class Fireball : public cocos2d::Sprite
{
private:
	bool m_touched;
	cocos2d::Animation*  m_animation;
	
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames ;
	cocos2d::Animate* m_animate;
	basic_Types::Rect m_hitbox;


public:
	Fireball();

	_Direction m_dir;

	static Fireball * create(cocos2d::Vec2 position, int _dir);

	void initOptions(cocos2d::Vec2 position);

	void addEvents();

	void createAnimations();

};