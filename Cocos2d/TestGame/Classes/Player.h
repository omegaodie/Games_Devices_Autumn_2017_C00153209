#pragma once

#include "cocos2d.h"
#include "BasicTypes.h"
#include "GameData.h"

enum _Anim_State {
	up,
	down, 
	left,
	right
};

class Player : public cocos2d::Sprite
{
private:
	bool m_touched;
	cocos2d::Vector<cocos2d::Animation*>  m_animations;
	
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_up ;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_down;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_left;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_right;
	cocos2d::Vector<cocos2d::Animate*> m_animates;
	basic_Types::Rect m_hitbox;


public:
	Player();

	_Anim_State m_state;

	static Player * create(cocos2d::Vec2 position);

	void initOptions(cocos2d::Vec2 position);

	void addEvents();
	void handleTouchEvent(cocos2d::Touch* touch);

	bool isTouched() const;

	void createAnimations();

	void setState(int i);

	void setAnimation();

};