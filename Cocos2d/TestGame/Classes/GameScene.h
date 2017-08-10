#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "PauseScene.h"
#include "GameData.h"
#include "GameOverScene.h"
#include "Player.h"


#pragma once
enum class GameStates
{
	frozen,
	slow,
	normal
};

class GameScene : public cocos2d::Scene
{
private:
	Player* m_player;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);

	void addAnimatedSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);

	// Called when user pauses gameplay.
	void activatePauseScene(Ref *pSender);
	// Called at game over 
	void activateGameOverScene(Ref *pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
