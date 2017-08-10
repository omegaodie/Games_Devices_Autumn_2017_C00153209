#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "GameData.h"


class MainMenu : public cocos2d::Scene
{
private:
	cocos2d::Animation*  m_animation;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames;
	cocos2d::Animate* m_animate;

	float faceScaleX, faceScaleY;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void activateGameScene(Ref * pSender);

	void MainMenu::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);

	void MainMenu::loadNetworkMenu(Ref * pSender);

	void MainMenu::loadOptionsMenu(Ref * pSender);

	void MainMenu::loadGameMenu(Ref * pSender);

	void playAnimation(int anim);

	//void change(int sceneTo, int Face);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif // __HELLOWORLD_SCENE_H__
