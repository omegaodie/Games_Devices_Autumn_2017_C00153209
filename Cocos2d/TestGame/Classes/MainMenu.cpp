#include "MainMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	addBackGroundSprite(visibleSize, origin);

	auto playItem =
		MenuItemImage::create(ptr->m_mainMenu_play_noclick,
			ptr->m_mainMenu_play_click,
			CC_CALLBACK_1(MainMenu::activateGameScene, this));

	auto loadItem =
		MenuItemImage::create(ptr->m_mainMenu_load_noclick,
			ptr->m_mainMenu_load_click,
			CC_CALLBACK_1(MainMenu::loadGameMenu, this));

	auto networkGameItem =
		MenuItemImage::create(ptr->m_mainMenu_network_noclick,
			ptr->m_mainMenu_network_click,
			CC_CALLBACK_1(MainMenu::loadNetworkMenu, this));

	auto optionsItem =
		MenuItemImage::create(ptr->m_mainMenu_options_noclick,
			ptr->m_mainMenu_options_click,
			CC_CALLBACK_1(MainMenu::loadOptionsMenu, this));

	auto exitItem = MenuItemImage::create(ptr->m_mainMenu_exit_noclick,
		ptr->m_mainMenu_exit_click,
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	//auto menu = Menu::create(playItem, loadItem, exitItem, NULL);
	auto menu = Menu::create(playItem, loadItem, networkGameItem, optionsItem, exitItem, NULL);

	// Returns visible size of OpenGL window in points.
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 12);
	menu->setPosition(Vec2(180, visibleSize.height - 230));

	this->addChild(menu);

	return true;
}


void MainMenu::activateGameScene(Ref *pSender)
{
	playAnimation(1);
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}


void MainMenu::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto backgroundSprite = Sprite::create
	(ptr->m_mainMenu_Back);
	faceScaleX = visibleSize.width / backgroundSprite->getContentSize().width;
	faceScaleY = visibleSize.height / backgroundSprite->getContentSize().height;
	backgroundSprite->setScaleX(faceScaleX);
	backgroundSprite->setScaleY(faceScaleY);
	backgroundSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(backgroundSprite, -1);
}

void MainMenu::loadNetworkMenu(Ref * pSender)
{
	playAnimation(1);
}
//
void MainMenu::loadOptionsMenu(Ref * pSender)
{
	playAnimation(1);
}
//
void MainMenu::loadGameMenu(Ref * pSender)
{
	playAnimation(1);
}

void MainMenu::playAnimation(int anim)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_mainMenu_btn1_ss);
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_mainMenu_btn1_plist);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Create the walking animations.           
	for (int i = 0; i < 7; i++)
	{
		// Get a SpriteFrame using a name from the spritesheet .plist file.
		//m_animFrames_up.pushBack(spritecache->getSpriteFrameByName)
		m_animFrames.pushBack(spritecache->getSpriteFrameByName("m_face" + std::to_string(anim) +"_" + std::to_string(i + 1) + ".png"));
	}
	m_animation = Animation::createWithSpriteFrames(m_animFrames, 0.15f);
	m_animate = Animate::create(m_animation);
	auto faceSprite = Sprite::create();
	faceSprite->initWithSpriteFrame(spritecache->getSpriteFrameByName("m_face" + std::to_string(anim) + "_1.png"));
	faceSprite->setScaleX(faceScaleX);
	faceSprite->setScaleY(faceScaleY);
	faceSprite->setPosition(260*faceScaleX, visibleSize.height - (72 * faceScaleY));
	faceSprite->runAction(Repeat::create(m_animate, 1));
	this->addChild(faceSprite, 1);
}

//void MainMenu::change(int sceneTo, int Face)
//{
//	playAnimation(Face);
//	if (sceneTo == 0) 
//	{
//		//this->schedule(     //(MainMenu::activateGameScene), 0, 0, 0.8f);
//		//Director::getInstance()->getScheduler()->schedule(schedule_selector(MainMenu::activateGameScene), this, 0.8f, 0, 0, false);
//	}
//	else if (sceneTo == 1) 
//	{
//	//	this->schedule(Director::getInstance()->getScheduler()->schedule(co ,MainMenu::activateGameScene), 2.0f);
//
//	}
//	else if (sceneTo == 2)
//	{
//		/*auto action = Sequence::create(DelayTime::create(10), CallFunc::create(this, callfunc_selector(MainMenu::transitionToGameScene)), NULL);
//		this->runAction(action);*/
//	}
//	else if (sceneTo == 3)
//	{
//		//auto action = Sequence::create(DelayTime::create(10), CallFunc::create(this, callfunc_selector(MainMenu::transitionToGameScene)), NULL);
//		//this->runAction(action);
//	}
//	else 
//	{
//		//auto action = Sequence::create(DelayTime::create(10), CallFunc::create(this, callfunc_selector(MainMenu::transitionToGameScene)), NULL);
//		//this->runAction(action);
//	}
//}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
