#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
	return GameOverScene::create();
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	_retry = ptr->_gameMode;

	Sprite* _back;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (ptr->win) {
		_back = Sprite::create(ptr->m_over_win);
		_back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(_back);
	}
	else {
		_back = Sprite::create(ptr->m_over_loss);
		_back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(_back);
	}

	ptr->win = false;


	auto retryItem =
		MenuItemImage::create(ptr->m_pauseMenu_retry_noclick,
			ptr->m_pauseMenu_retry_click,
			CC_CALLBACK_1(GameOverScene::activateGameScene, this));

	auto mainMenuItem =
		MenuItemImage::create(ptr->m_pauseMenu_exittomenu_noclick,
			ptr->m_pauseMenu_exittomenu_click,
			CC_CALLBACK_1(GameOverScene::activateMainMenuScene, this));

	auto menu = Menu::create(retryItem, mainMenuItem, NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 8);



	this->addChild(menu);

	return true;
}

void GameOverScene::activateGameScene(cocos2d::Ref *pSender)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	if (_retry == 0) 
	{
		auto scene = Tutorial::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	else {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}

void GameOverScene::activateMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOverScene::menuCloseCallback(Ref* pSender)
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
