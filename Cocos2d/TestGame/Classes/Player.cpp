#include "Player.h"

USING_NS_CC;

void Player::changeAim(cocos2d::Vec2 v)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 _p = this->getPosition();
	Vec2 aim = v;
	Vec2 _steer = aim - _p;
	_Theta = _steer.getAngle();
	this->justAnimPlease();
}

void Player::stop(float _a)
{

	_Theta = _a;
	this->_velocity *= -1;
	this->setPosition(this->getPosition() + (_velocity.getNormalized() * 50));
}

int Player::getAmmo()
{
	return _in_magazine;
}

Player::Player() : m_touched(false)
{
}

bool  Player::getFiring()
{
	return _firing;
}

bool Player::getReadyToFire()
{
	return _ready_to_shoot;
}

basic_Types::player_state Player::getState()
{
	return m_state;
}

void  Player::shootShit()
{
		if (_total_ammo > 0)
		{
			if (_in_magazine > 0)
			{
				_firing = true;	
			}
			else
			{
				setState(RELOADING);
				_firing = false;
				reload_timer = 29 * 0.05f;
				_in_magazine = _magazine_capacity;
				_total_ammo--;
			}
		}
		else {
			setState(IDLE);
			_firing = false;

		}
}

float Player::getTheta()
{
	return _Theta;
}

void Player::reduceHealth()
{
	if (hp > 0) {
		hp -= 0.51;
	}
	else {
		m_alive = false;
	}
	
}

float Player::getHealth()
{
	return hp;
}

Player * Player::create(Vec2 position)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	
	Player* pSprite = new Player();
	if (pSprite->init())
	{
		pSprite->autorelease();

		pSprite->initOptions(position);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool Player::getAlive() {
	return m_alive;
};

void Player::initOptions(Vec2 p)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	this->createAnimations();
	this->addEvents();
	_firing_timer = 12 * 0.05;
	_firewait_timer = 5 * 0.05;
	_firewait_timer_2 = 8 * 0.05;
	_firing = false;
	_ready_to_shoot = false;
	m_alive = true;
	this->setState(IDLE);
	max_hp = ptr->_difficulty_option_playerHP;
	hp = max_hp;
	_player_rect = cocos2d::Rect(p, cocos2d::Size(basic_Types::player_hd_x, basic_Types::player_hd_y));
	maxForce = 250;
	maxSpeed = 350;
	_total_ammo = 20;
	_magazine_capacity = 6;
	_in_magazine = _magazine_capacity;
	this->setPosition(p);
	_Theta = (45 / (180 / PI));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_screen = Vec2(visibleSize.width, visibleSize.height);

}

void Player::addEvents()
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 pos = touch->getLocation();

		switch (m_state) {
		case MOVING:
			pos += Vec2(this->getPosition() - (_screen / 2));
			if (_player_rect.containsPoint(pos))
			{
				setState(IDLE);
				return true; // to indicate that we have consumed it.
			}
			changeDirection(pos);
			return true; // to indicate that we have consumed it.
			break;
		case FIRING:
	
			return false;
			break;
		case RELOADING:
			changeDirection(pos);
			_ready_to_shoot = false;
			return true; // to indicate that we have consumed it.
			break;
		case IDLE:
			pos += Vec2(this->getPosition() - (_screen / 2));
			if (_player_rect.containsPoint(pos))
			{
				if (_ready_to_shoot) {
					_ready_to_shoot = false;
				}
				else {
					_ready_to_shoot = true;
				}
				
				//setState(MOVING);
				return true; // to indicate that we have consumed it.
			}
			if (_ready_to_shoot) {
				changeAim(pos);
				_firing_timer = 12 * 0.05;
				_firewait_timer = 5 * 0.05;
				_firewait_timer_2 = 8 * 0.05;
				setState(FIRING);
				return true; // to indicate that we have consumed it.
			}
			else {
				changeDirection(pos);
				return true; // to indicate that we have consumed it.
			}

			return false; // we did not consume this event, pass through.
			break;

		}

	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 pos = touch->getLocation();
		//cocos2d::Rect rect = this->getBoundingBox();

		if (_player_rect.containsPoint(pos))
		{
			this->m_state = IDLE;
			return true; // to indicate that we have consumed it.
		}


		return false; // we did not consume this event, pass through.
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void Player::update(float dt)
{
	Vec2 _steer, _vdest;
	switch (m_state) {
	case MOVING:
		_firing = false;
			_new_pos = this->getPosition();
			_vdest = _destination - _new_pos;
			_steer = _vdest - _velocity;
			if (_steer.length() > maxForce) {
				_steer.normalize();
				_steer *= maxForce;
			}
			_velocity += _steer;
			if (_velocity.length() > maxSpeed) {
				_velocity.normalize();
				_velocity *= maxForce;
			}
			if (_vdest.length() >= 10)
			{
				float l = _vdest.length();
				_velocity.normalize();
				_velocity *= (maxSpeed - (maxSpeed / l ));
				if (this->getBoundingBox().containsPoint(_destination)) 
				{
					setState(IDLE);
				}
			}
			_new_pos += (_velocity * dt);
			this->setPosition(_new_pos);
			_player_rect.origin = _new_pos;
		break;
	case FIRING:
		if (_firewait_timer > 0) {
			_firewait_timer -= dt;
		}
		else {
			if (_firing_timer > 0)
			{
				_firing_timer -= dt;
				_ready_to_shoot = true;
				shootShit();
			}
			else 
			{
				_firing = false;

				if (_firewait_timer_2 < 0) {
					setState(IDLE);
					_in_magazine -= 1;
				}
				else {
					_firewait_timer_2 -= dt;
				}
			}
		}
		break;
	case IDLE:
		_firing = false;
		break;
	case RELOADING:
		reload_timer -= dt;
		if (reload_timer < 0) {
			setState(IDLE);
		}
		break;

	}
}

void Player::changeDirection(Vec2 _tp)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 _p = this->getPosition();
	_destination = _tp;
	Vec2 _steer = _tp - _p;
	_steer.normalize();
	_steer *= maxForce;
	_velocity += _steer;
	_Theta = _velocity.getAngle();
	if (m_state != MOVING) {
		this->setState(MOVING);
	}
	else {
		this->justAnimPlease();
	}
}

bool Player::isTouched() const
{
	return m_touched;
}

void Player::setState(basic_Types::player_state m_s)
{
	m_state = m_s;
	if (m_s == IDLE) {
		//_ready_to_shoot = false;
	}
	float _theta_in_degrees = _Theta * (180 / PI);
	if (_theta_in_degrees >= -67 && _theta_in_degrees <= -15)
	{
		m_direction = right_down; //fine
	}
	else if (_theta_in_degrees >= -15 && _theta_in_degrees <= 37)
	{
		m_direction = right; //fine
	}
	else if (_theta_in_degrees >= 37 && _theta_in_degrees <= 67)
	{
		m_direction = right_up; //fine
	}
	else if (_theta_in_degrees > 67 && _theta_in_degrees < 110)
	{
		m_direction = up; //fine
	}
	else if (_theta_in_degrees > 110 && _theta_in_degrees < 155)
	{
		m_direction = left_up; //fine
	}
	else if (_theta_in_degrees < -67 && _theta_in_degrees > -110)
	{
		m_direction = down;
	}
	else if (_theta_in_degrees < -110 && _theta_in_degrees > -155)
	{
		m_direction = left_down;
	}
	else
	{
		m_direction = left;
	}
	setAnimation();
}

void Player::justAnimPlease()
{
	float _theta_in_degrees = _Theta * (180 / PI);
	if (_theta_in_degrees >= -67 && _theta_in_degrees <= -15)
	{
		if (m_direction != right_down) {
			m_direction = right_down; //fine
			setAnimation();
		}
	}
	else if (_theta_in_degrees >= -15 && _theta_in_degrees <= 37)
	{
		if (m_direction != right) {
			m_direction = right; //fine
			setAnimation();
		}
	}
	else if (_theta_in_degrees >= 37 && _theta_in_degrees <= 67)
	{
		if (m_direction != right_up) {
			m_direction = right_up; //fine
			setAnimation();
		}
	}
	else if (_theta_in_degrees > 67 && _theta_in_degrees < 110)
	{
		if (m_direction != up) {
			m_direction = up; //fine
			setAnimation();
		}
	}
	else if (_theta_in_degrees > 110 && _theta_in_degrees < 155)
	{
		if (m_direction != left_up) {
			m_direction = left_up; //fine
			setAnimation();
		}
	}
	else if (_theta_in_degrees < -67 && _theta_in_degrees > -110)
	{
		if (m_direction != down) {
			m_direction = down; //fine
			setAnimation();
		}
	}
	else if (_theta_in_degrees < -110 && _theta_in_degrees > -155)
	{
		if (m_direction != left_down) {
			m_direction = left_down; //fine
			setAnimation();
		}
	}
	else
	{
		if (m_direction != left) {
			m_direction = left; //fine
			setAnimation();
		}
	}
}

void Player::setAnimation()
{
	this->stopAllActions();
	switch (m_state) {
	case IDLE :
		switch (m_direction)
		{
		case  basic_Types::_Anim_State::left_down:
			this->runAction(RepeatForever::create(m_animates.at(0)));
			break;
		case  basic_Types::_Anim_State::left:
			this->runAction(RepeatForever::create(m_animates.at(1))); //fine
			break;
		case  basic_Types::_Anim_State::left_up:
			this->runAction(RepeatForever::create(m_animates.at(2)));
			break;
		case  basic_Types::_Anim_State::up:
			this->runAction(RepeatForever::create(m_animates.at(3)));
			break;
		case  basic_Types::_Anim_State::right:
			this->runAction(RepeatForever::create(m_animates.at(4)));
			break;
		case  basic_Types::_Anim_State::right_up:
			this->runAction(RepeatForever::create(m_animates.at(5)));
			break;
		case  basic_Types::_Anim_State::right_down:
			this->runAction(RepeatForever::create(m_animates.at(6)));
			break;
		case  basic_Types::_Anim_State::down:
			this->runAction(RepeatForever::create(m_animates.at(7))); //fine
			break;
		}
		break;
	case RELOADING:
		switch (m_direction)
		{
		case  basic_Types::_Anim_State::left_down:
			this->runAction((m_animates.at(8)));
			break;
		case  basic_Types::_Anim_State::left:
			this->runAction((m_animates.at(9))); //fine
			break;
		case  basic_Types::_Anim_State::left_up:
			this->runAction((m_animates.at(10)));
			break;
		case  basic_Types::_Anim_State::up:
			this->runAction((m_animates.at(11)));
			break;
		case  basic_Types::_Anim_State::right:
			this->runAction((m_animates.at(12)));
			break;
		case  basic_Types::_Anim_State::right_up:
			this->runAction((m_animates.at(13)));
			break;
		case  basic_Types::_Anim_State::right_down:
			this->runAction((m_animates.at(14)));
			break;
		case  basic_Types::_Anim_State::down:
			this->runAction((m_animates.at(15))); //fine
			break;
		}
		break;
	case MOVING:
		switch (m_direction)
		{
		case  basic_Types::_Anim_State::left_down:
			this->runAction(RepeatForever::create(m_animates.at(16)));
			break;
		case  basic_Types::_Anim_State::left:
			this->runAction(RepeatForever::create(m_animates.at(17))); //fine
			break;
		case  basic_Types::_Anim_State::left_up:
			this->runAction(RepeatForever::create(m_animates.at(18)));
			break;
		case  basic_Types::_Anim_State::up:
			this->runAction(RepeatForever::create(m_animates.at(19)));
			break;
		case  basic_Types::_Anim_State::right:
			this->runAction(RepeatForever::create(m_animates.at(20)));
			break;
		case  basic_Types::_Anim_State::right_up:
			this->runAction(RepeatForever::create(m_animates.at(21)));
			break;
		case  basic_Types::_Anim_State::right_down:
			this->runAction(RepeatForever::create(m_animates.at(22)));
			break;
		case  basic_Types::_Anim_State::down:
			this->runAction(RepeatForever::create(m_animates.at(23))); //fine
			break;
		}
		break;
	case FIRING : 
		switch (m_direction)
		{
		case  basic_Types::_Anim_State::left_down:
			this->runAction(m_animates.at(24));  //RepeatForever::create(m_animates.at(24)));
			break;
		case  basic_Types::_Anim_State::left:
			//this->runAction(RepeatForever::create(m_animates.at(25))); //fine
			this->runAction(m_animates.at(25));
			break;
		case  basic_Types::_Anim_State::left_up:
			//this->runAction(RepeatForever::create(m_animates.at(26)));
			this->runAction(m_animates.at(26));
			break;
		case  basic_Types::_Anim_State::up:
			//this->runAction(RepeatForever::create(m_animates.at(27)));
			this->runAction(m_animates.at(27));
			break;
		case  basic_Types::_Anim_State::right:
			//this->runAction(RepeatForever::create(m_animates.at(28)));
			this->runAction(m_animates.at(28));
			break;
		case  basic_Types::_Anim_State::right_up:
			//this->runAction(RepeatForever::create(m_animates.at(29)));
			this->runAction(m_animates.at(29));
			break;
		case  basic_Types::_Anim_State::right_down:
			//this->runAction(RepeatForever::create(m_animates.at(30)));
			this->runAction(m_animates.at(30));
			break;
		case  basic_Types::_Anim_State::down:
			//this->runAction(RepeatForever::create(m_animates.at(31))); //fine
			this->runAction(m_animates.at(31));
			break;
		}
		break;
		}
}

void Player::createAnimations()
{
	////LEFTDOWN

	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	cocos2d::Vector<SpriteBatchNode*> spritebatch;
	auto spritecache = SpriteFrameCache::getInstance();

	for (int i = 0; i < ptr->_num_player_files; i++)
	{
		spritebatch.pushBack(SpriteBatchNode::create(ptr->_player_file_name + std::to_string(i) + ".png"));
		spritecache->addSpriteFramesWithFile(ptr->_player_file_name + std::to_string(i) + ".plist");
	}


	/////////RELoad/////////////////////////////////
	for (int i = 0; i < 29; i++)
	{
		if (i < 9)
		{
			m_animFrames_reload_left_down.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v01_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_left.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v02_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_left_up.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v03_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_up.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v04_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_right.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v06_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_right_up.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v05_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_right_down.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v07_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_down.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v08_0" + std::to_string(i + 1) + ".png"));
		}
		else
		{
			m_animFrames_reload_left_down.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v01_" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_left.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v02_" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_left_up.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v03_" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_up.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v04_" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_right.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v06_" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_right_up.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v05_" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_right_down.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v07_" + std::to_string(i + 1) + ".png"));
			m_animFrames_reload_down.pushBack(spritecache->getSpriteFrameByName("swat_recharge_v08_" + std::to_string(i + 1) + ".png"));
		}
	}
	/////////WALK/////////////////////////////////
	for (int i = 0; i < 24; i++)
	{
		if (i < 9)
		{
			m_animFrames_move_left_down.pushBack(spritecache->getSpriteFrameByName("swat_walk_v01_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_left.pushBack(spritecache->getSpriteFrameByName("swat_walk_v02_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_left_up.pushBack(spritecache->getSpriteFrameByName("swat_walk_v03_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_up.pushBack(spritecache->getSpriteFrameByName("swat_walk_v04_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_right.pushBack(spritecache->getSpriteFrameByName("swat_walk_v06_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_right_up.pushBack(spritecache->getSpriteFrameByName("swat_walk_v05_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_right_down.pushBack(spritecache->getSpriteFrameByName("swat_walk_v07_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_down.pushBack(spritecache->getSpriteFrameByName("swat_walk_v08_0" + std::to_string(i + 1) + ".png"));
		}
		else
		{
			m_animFrames_move_left_down.pushBack(spritecache->getSpriteFrameByName("swat_walk_v01_" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_left.pushBack(spritecache->getSpriteFrameByName("swat_walk_v02_" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_left_up.pushBack(spritecache->getSpriteFrameByName("swat_walk_v03_" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_up.pushBack(spritecache->getSpriteFrameByName("swat_walk_v04_" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_right.pushBack(spritecache->getSpriteFrameByName("swat_walk_v06_" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_right_up.pushBack(spritecache->getSpriteFrameByName("swat_walk_v05_" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_right_down.pushBack(spritecache->getSpriteFrameByName("swat_walk_v07_" + std::to_string(i + 1) + ".png"));
			m_animFrames_move_down.pushBack(spritecache->getSpriteFrameByName("swat_walk_v08_" + std::to_string(i + 1) + ".png"));
		}
	}
	/////////SHOOTING/////////////////////////////////
	for (int i = 0; i < 35; i++)
	{



		if (i < 9)
		{
			m_animFrames_fire_left_down.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v01_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_left.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v02_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_left_up.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v03_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_up.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v04_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_right.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v06_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_right_up.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v05_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_right_down.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v07_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_down.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v08_0" + std::to_string(i + 1) + ".png"));
		}
		else
		{
			m_animFrames_fire_left_down.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v01_" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_left.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v02_" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_left_up.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v03_" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_up.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v04_" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_right.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v06_" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_right_up.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v05_" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_right_down.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v07_" + std::to_string(i + 1) + ".png"));
			m_animFrames_fire_down.pushBack(spritecache->getSpriteFrameByName("swat_shooting_v08_" + std::to_string(i + 1) + ".png"));
		}
	}
	/////////IDLE/////////////////////////////////       
	for (int i = 0; i < 74; i++)
	{
		if (i < 9)
		{
			m_animFrames_idle_left_down.pushBack(spritecache->getSpriteFrameByName("swat_idle_v01_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_left.pushBack(spritecache->getSpriteFrameByName("swat_idle_v02_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_left_up.pushBack(spritecache->getSpriteFrameByName("swat_idle_v03_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_up.pushBack(spritecache->getSpriteFrameByName("swat_idle_v04_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_right.pushBack(spritecache->getSpriteFrameByName("swat_idle_v06_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_right_up.pushBack(spritecache->getSpriteFrameByName("swat_idle_v05_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_right_down.pushBack(spritecache->getSpriteFrameByName("swat_idle_v07_0" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_down.pushBack(spritecache->getSpriteFrameByName("swat_idle_v08_0" + std::to_string(i + 1) + ".png"));
		}
		else
		{
			m_animFrames_idle_left_down.pushBack(spritecache->getSpriteFrameByName("swat_idle_v01_" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_left.pushBack(spritecache->getSpriteFrameByName("swat_idle_v02_" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_left_up.pushBack(spritecache->getSpriteFrameByName("swat_idle_v03_" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_up.pushBack(spritecache->getSpriteFrameByName("swat_idle_v04_" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_right.pushBack(spritecache->getSpriteFrameByName("swat_idle_v06_" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_right_up.pushBack(spritecache->getSpriteFrameByName("swat_idle_v05_" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_right_down.pushBack(spritecache->getSpriteFrameByName("swat_idle_v07_" + std::to_string(i + 1) + ".png"));
			m_animFrames_idle_down.pushBack(spritecache->getSpriteFrameByName("swat_idle_v08_" + std::to_string(i + 1) + ".png"));
		}
	}





	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_idle_left_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(0)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_idle_left, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(1)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_idle_left_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(2)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_idle_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(3)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_idle_right, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(4)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_idle_right_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(5)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_idle_right_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(6)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_idle_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(7)));


	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_reload_left_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(8)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_reload_left, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(9)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_reload_left_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(10)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_reload_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(11)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_reload_right, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(12)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_reload_right_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(13)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_reload_right_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(14)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_reload_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(15)));

	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_move_left_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(16)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_move_left, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(17)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_move_left_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(18)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_move_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(19)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_move_right, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(20)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_move_right_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(21)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_move_right_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(22)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_move_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(23)));


	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_fire_left_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(24)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_fire_left, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(25)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_fire_left_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(26)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_fire_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(27)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_fire_right, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(28)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_fire_right_up, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(29)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_fire_right_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(30)));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_fire_down, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(31)));

}