#include "Player.h"

USING_NS_CC;

Player::Player() : m_touched(false)
{
	
}

Player * Player::create(Vec2 position)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_game_test_sheet);


	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_game_test_plist);		


	Player* pSprite = new Player();
	if (pSprite->initWithSpriteFrameName("down_1.png"))
	//if (pSprite->initWithFile("Game/test_pic.png"))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);

		pSprite->addEvents();
		
		pSprite->createAnimations();

		pSprite->setState(0);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Player::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
	m_hitbox = basic_Types::Rect(basic_Types::Vector2(position), basic_Types::Size(32, 32));
	//m_animates = Animate::create(new Animation());
		//set(Vec3(position.x - (16 / 2), position.y - (16 / 2), 0), Vec3(position.x + (16 / 2), position.y + (16 / 2), 0));
}

void Player::addEvents()
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		//cocos2d::Vec2 pos = touch->getLocation();
		//cocos2d::Rect rect = this->getBoundingBox();

		//if (rect.containsPoint(pos))
		//{
		//	return true; // to indicate that we have consumed it.
		//}
		handleTouchEvent(touch);
		return false; // we did not consume this event, pass through.
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void Player::handleTouchEvent(cocos2d::Touch* touch)
{
	// Change gameState in response to sprite touched
	m_touched = true;
	m_hitbox.pos = basic_Types::Vector2(this->getPosition());
	cocos2d::Vec2 l_temp_tp = touch->getLocation();
	if (m_hitbox.Contains(l_temp_tp)) 
	{
		//fire or whatever
		basic_Types::Vector2 _pp = basic_Types::Vector2(this->getPosition().x, this->getPosition().x);
		basic_Types::Vector2 _touchpos = basic_Types::Vector2(touch->getLocation().x, touch->getLocation().y);
		int i = 0;
	}
	else
	{
		Point origin = Director::getInstance()->getVisibleOrigin();
		basic_Types::Vector2 _pp = basic_Types::Vector2(this->getPosition().x, this->getPosition().y);
		basic_Types::Vector2 _touchpos = basic_Types::Vector2(touch->getLocation().x, touch->getLocation().y);

		float l_theta = _pp.angleBetween(touch->getLocation());
		int i = 0;
		if (l_theta < (basic_Types::PI / 4) && l_theta > (basic_Types::PI / -4.0f))
		{
			//right
			this->setState(3);
		}
		else if (l_theta > (basic_Types::PI / 4) && l_theta < (basic_Types::PI  - (basic_Types::PI / 4)))
		{
			//UP
			this->setState(0);
		}
		else if (l_theta < (basic_Types::PI / -4.0f) && l_theta > (-basic_Types::PI + (basic_Types::PI / 4)))
		{
			//Down
			this->setState(1);
		}
		else
		{
			//LEFT
			this->setState(2);
		}
	}
}

bool Player::isTouched() const
{
	return m_touched;
}

void Player::createAnimations()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_game_test_sheet);
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_game_test_plist);

	// Create the walking animations.           
	for (int i = 0; i < 3; i++)
	{
		// Get a SpriteFrame using a name from the spritesheet .plist file.
		//m_animFrames_up.pushBack(spritecache->getSpriteFrameByName)
		m_animFrames_up.pushBack(spritecache->getSpriteFrameByName("down_" + std::to_string(i + 1) + ".png"));
		m_animFrames_down.pushBack(spritecache->getSpriteFrameByName("up_" + std::to_string(i + 1) + ".png"));
		m_animFrames_left.pushBack(spritecache->getSpriteFrameByName("left_" + std::to_string(i + 1) + ".png"));
		m_animFrames_right.pushBack(spritecache->getSpriteFrameByName("right_" + std::to_string(i + 1) + ".png"));
	}
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_up, 0.05f));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_down, 0.05f));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_left, 0.05f));
	m_animations.pushBack(Animation::createWithSpriteFrames(m_animFrames_right, 0.05f));
	m_animates.pushBack(Animate::create(m_animations.at(0)));
	m_animates.pushBack(Animate::create(m_animations.at(1)));
	m_animates.pushBack(Animate::create(m_animations.at(2)));
	m_animates.pushBack(Animate::create(m_animations.at(3)));

}


void Player::setState(int st) 
{
	if (st == 0) 
	{
		m_state = up;
	}
	else if (st == 1)
	{
		m_state = down;
	}
	else if (st == 2)
	{
		m_state = left;
	}
	else
	{
		m_state = right;
	}
	setAnimation();
}

void Player::setAnimation()
{
	this->stopAllActions();
	switch (m_state)
	{
		case up:
			this->runAction(RepeatForever::create(m_animates.at(0)));
			break;
		 case down:
			this->runAction(RepeatForever::create(m_animates.at(1)));
			break;
		 case left:
			this->runAction(RepeatForever::create(m_animates.at(2)));
			break;
		case right:
			this->runAction(RepeatForever::create(m_animates.at(3)));
			break;
	}
}