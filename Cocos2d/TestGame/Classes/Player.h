#pragma once

#include "cocos2d.h"
#include "BasicTypes.h"
#include "GameData.h"
#include<time.h>

class Player : public cocos2d::Sprite
{
private:
	bool m_touched, m_alive;
	cocos2d::Vector<cocos2d::Animation*>  m_animations;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_move_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_move_down;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_move_left;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_move_left_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_move_left_down;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_move_right;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_move_right_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_move_right_down;


	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_fire_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_fire_down;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_fire_left;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_fire_left_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_fire_left_down;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_fire_right;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_fire_right_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_fire_right_down;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_reload_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_reload_down;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_reload_left;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_reload_left_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_reload_left_down;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_reload_right;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_reload_right_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_reload_right_down;


	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_idle_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_idle_down;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_idle_left;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_idle_left_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_idle_left_down;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_idle_right;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_idle_right_up;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames_idle_right_down;



	cocos2d::Vector<cocos2d::Animate*> m_animates;

	cocos2d::Vec2 _steer;
	cocos2d::Vec2 _velocity;
	cocos2d::Vec2 _acceleration;
	cocos2d::Vec2 _destination;
	cocos2d::Vec2 _new_pos;

	cocos2d::Vec2 _screen;

	cocos2d::Rect _player_rect;

	float maxSpeed;
	float maxForce;
	float hp, max_hp;
	float _Theta, _firing_timer, _firewait_timer, _firewait_timer_2, reload_timer;
	int _total_ammo, _in_magazine, _magazine_capacity;
	bool _ready_to_shoot;

	basic_Types::_Anim_State m_direction;
	basic_Types::player_state m_state;
	std::vector<bool> _bullet_check;

public:

	bool _firing;

	bool getAlive();

	void changeAim(cocos2d::Vec2 v);

	void stop(float _angle);

	int getAmmo();

	Player();

	bool getFiring();

	bool getReadyToFire();

	basic_Types::player_state getState();

	void shootShit();

	float getTheta();

	void reduceHealth();

	float getHealth();


	static Player * create(cocos2d::Vec2 position);

	void initOptions(cocos2d::Vec2 position);

	void addEvents();

	void update(float dt);

	void changeDirection(cocos2d::Vec2 touch);

	bool isTouched() const;

	void createAnimations();

	void setState(basic_Types::player_state m_s);

	void justAnimPlease();

	void setAnimation();

};