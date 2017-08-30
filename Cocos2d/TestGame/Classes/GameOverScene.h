#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "MainMenu.h"

class GameOverScene : public cocos2d::Scene
{
private:
	int _retry;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	// Called when retry is selected 
	void activateGameScene(Ref *pSender);
	// Called when main menu is selected 
	void activateMainMenuScene(Ref *pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};

#endif // __HELLOWORLD_SCENE_H__
