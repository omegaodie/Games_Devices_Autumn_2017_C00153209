#include "PauseScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
    return PauseScene::create();
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 3. add your codes below...

	auto resumeItem =
		MenuItemImage::create("Pause/p_pause_resume_1.png",
			"Pause/p_pause_resume_2.png",
			CC_CALLBACK_1(PauseScene::resume, this));
	auto retryItem =
		MenuItemImage::create("Pause/p_pause_retry_1.png",
			"Pause/p_pause_retry_2.png",
			CC_CALLBACK_1(PauseScene::retry, this));
	auto mainMenuItem =
		MenuItemImage::create("Pause/p_pause_return_1.png",
			"Pause/p_pause_return_2.png",
			CC_CALLBACK_1(PauseScene::activateMainMenuScene, this));
	auto menu = Menu::create(resumeItem, retryItem, mainMenuItem,
		NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 8);
	this->addChild(menu);
    
    return true;
}

void PauseScene::resume(Ref *pSender)
{
	Director::getInstance()->popScene();
}

void PauseScene::activateMainMenuScene(Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseScene::retry(Ref *pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseScene::menuCloseCallback(Ref* pSender)
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
