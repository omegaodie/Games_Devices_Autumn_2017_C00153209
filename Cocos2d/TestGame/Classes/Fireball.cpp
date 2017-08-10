#include "Fireball.h"

USING_NS_CC;

Fireball::Fireball() : m_touched(false)
{
	
}

Fireball * Fireball::create(Vec2 position, int dir)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_game_fireball_sheet);


	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_game_fireball_plist);		


	Fireball* pSprite = new Fireball();
	if (pSprite->initWithSpriteFrameName("fireball_1.png"))
	//if (pSprite->initWithFile("Game/test_pic.png"))
	{
		pSprite->m_dir = _Direction(dir);

		pSprite->autorelease();

		pSprite->initOptions(position);

		pSprite->addEvents();
		
		pSprite->createAnimations();


		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Fireball::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
	m_hitbox = basic_Types::Rect(basic_Types::Vector2(position), basic_Types::Size(32, 32));
	//m_animates = Animate::create(new Animation());
		//set(Vec3(position.x - (16 / 2), position.y - (16 / 2), 0), Vec3(position.x + (16 / 2), position.y + (16 / 2), 0));
}

void Fireball::addEvents()
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
		return false; // we did not consume this event, pass through.
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void Fireball::createAnimations()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_game_fireball_sheet);
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_game_fireball_plist);

	// Create the walking animations.           
	for (int i = 0; i < 8; i++)
	{
		// Get a SpriteFrame using a name from the spritesheet .plist file.
		//m_animFrames_up.pushBack(spritecache->getSpriteFrameByName)
		m_animFrames.pushBack(spritecache->getSpriteFrameByName("fireball_" + std::to_string(i + 1) + ".png"));
	}
	m_animation = Animation::createWithSpriteFrames(m_animFrames, 0.05f);
	m_animate = Animate::create(m_animation);

	this->runAction(RepeatForever::create(m_animate));
}
