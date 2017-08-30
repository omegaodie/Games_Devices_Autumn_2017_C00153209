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
	auto fileUtils = FileUtils::getInstance();


	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	createAssets();

	auto tutorialItem =
		MenuItemImage::create(ptr->m_mainMenu_tutorial_noclick,
			ptr->m_mainMenu_tutorial_click,
			CC_CALLBACK_1(MainMenu::activateTutorial, this));


	auto playItem =
		MenuItemImage::create(ptr->m_mainMenu_play_noclick,
			ptr->m_mainMenu_play_click,
			CC_CALLBACK_1(MainMenu::activateGameScene, this));


	auto optionsItem =
		MenuItemImage::create(ptr->m_mainMenu_options_noclick,
			ptr->m_mainMenu_options_click,
			CC_CALLBACK_1(MainMenu::loadOptionsMenu, this));

	auto exitItem = MenuItemImage::create(ptr->m_mainMenu_exit_noclick,
		ptr->m_mainMenu_exit_click,
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	//auto menu = Menu::create(playItem, loadItem, exitItem, NULL);
	auto menu = Menu::create(tutorialItem, playItem, optionsItem, exitItem, NULL);

	// Returns visible size of OpenGL window in points.
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 30);
	menu->setPosition(Vec2(visibleSize.width / 2 - (_back_Sprite->getTextureRect().size.width / 4),
		visibleSize.height / 2 + (_back_Sprite->getTextureRect().size.height / 16)));

	this->addChild(menu);



	return true;
}

void MainMenu::activateTutorial(Ref *pSender)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	playAnimation(0);
	auto scene = Tutorial::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2.99f, scene, Color3B(0, 0, 0)));
	//HUD* _hud = HUD::createLayer("The Enemy is approaching!");
	//scene->addChild(_hud, 2);
}

void MainMenu::activateGameScene(Ref *pSender)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	playAnimation(0);
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2.99f, scene, Color3B(0, 0, 0)));
}

void MainMenu::loadNetworkMenu(Ref * pSender)
{
	playAnimation(1);
	auto scene = NetworkMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2.99f, scene, Color3B(0, 0, 0)));
}
//
void MainMenu::loadOptionsMenu(Ref * pSender)
{
	playAnimation(2);
	auto scene = OptionsMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2.99f, scene, Color3B(0, 0, 0)));
}
//
void MainMenu::loadGameMenu(Ref * pSender)
{
	playAnimation(3);
	auto scene = LoadGameMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2.99f, scene, Color3B(0, 0, 0)));
}

void MainMenu::playAnimation(int anim)
{
	Sprite* _face = Sprite::create();

	
	_back_Sprite->addChild(_face);
	_face->setPosition(_face_pos[anim]);
	_face->runAction(Repeat::create(_animates.at(anim), 1));
}

void MainMenu::createAssets()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_generalmenu_assets + ".png");
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_generalmenu_assets + ".plist");


	_back_Sprite = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("_back_1.png"));
	_back_Sprite->setPosition(visibleSize / 2);
	this->addChild(_back_Sprite);


          
	for (int i = 0; i < 7; i++)
	{
		_face_1.pushBack(spritecache->getSpriteFrameByName("f1_" + std::to_string(i + 1) + ".png"));
		_face_2.pushBack(spritecache->getSpriteFrameByName("f2_" + std::to_string(i + 1) + ".png"));
		_face_3.pushBack(spritecache->getSpriteFrameByName("f3_" + std::to_string(i + 1) + ".png"));
		_face_4.pushBack(spritecache->getSpriteFrameByName("f4_" + std::to_string(i + 1) + ".png"));
		_face_5.pushBack(spritecache->getSpriteFrameByName("f5_" + std::to_string(i + 1) + ".png"));
		_face_6.pushBack(spritecache->getSpriteFrameByName("f6_" + std::to_string(i + 1) + ".png"));
		_face_7.pushBack(spritecache->getSpriteFrameByName("f7_" + std::to_string(i + 1) + ".png"));
		_face_8.pushBack(spritecache->getSpriteFrameByName("f8_" + std::to_string(i + 1) + ".png"));
		if (ptr->_resoloution == 0) 
		{
			_face_pos.push_back(Vec2(ptr->_menu_face_pos_sd[i].x, _back_Sprite->getTextureRect().size.height - ptr->_menu_face_pos_sd[i].y));
		}
		else if (ptr->_resoloution == 1) 
		{
			_face_pos.push_back(Vec2(ptr->_menu_face_pos_hd[i].x, _back_Sprite->getTextureRect().size.height - ptr->_menu_face_pos_hd[i].y));
		}
		else
		{
			_face_pos.push_back(Vec2(ptr->_menu_face_pos_shd[i].x, _back_Sprite->getTextureRect().size.height - ptr->_menu_face_pos_shd[i].y));
		}
	}

	_animations.pushBack(Animation::createWithSpriteFrames(_face_1, 0.1f));
	_animates.pushBack(Animate::create(_animations.at(0)));
	_animations.pushBack(Animation::createWithSpriteFrames(_face_2, 0.1f));
	_animates.pushBack(Animate::create(_animations.at(1)));
	_animations.pushBack(Animation::createWithSpriteFrames(_face_3, 0.1f));
	_animates.pushBack(Animate::create(_animations.at(2)));
	_animations.pushBack(Animation::createWithSpriteFrames(_face_4, 0.1f));
	_animates.pushBack(Animate::create(_animations.at(3)));
	_animations.pushBack(Animation::createWithSpriteFrames(_face_5, 0.1f));
	_animates.pushBack(Animate::create(_animations.at(4)));
	_animations.pushBack(Animation::createWithSpriteFrames(_face_6, 0.1f));
	_animates.pushBack(Animate::create(_animations.at(5)));
	_animations.pushBack(Animation::createWithSpriteFrames(_face_7, 0.1f));
	_animates.pushBack(Animate::create(_animations.at(6)));
	_animations.pushBack(Animation::createWithSpriteFrames(_face_8, 0.1f));
	_animates.pushBack(Animate::create(_animations.at(7)));



}


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
