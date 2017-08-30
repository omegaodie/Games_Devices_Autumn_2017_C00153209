#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "NetworkMenu.h"
#include "LoadGameMenu.h"
#include "OptionsMenu.h"
#include "Tutorial.h"
#include "GameData.h"


class MainMenu : public cocos2d::Scene
{
private:


	cocos2d::Vector<cocos2d::SpriteFrame*> _face_1;
	cocos2d::Vector<cocos2d::SpriteFrame*> _face_2;
	cocos2d::Vector<cocos2d::SpriteFrame*> _face_3;
	cocos2d::Vector<cocos2d::SpriteFrame*> _face_4;
	cocos2d::Vector<cocos2d::SpriteFrame*> _face_5;
	cocos2d::Vector<cocos2d::SpriteFrame*> _face_6;
	cocos2d::Vector<cocos2d::SpriteFrame*> _face_7;
	cocos2d::Vector<cocos2d::SpriteFrame*> _face_8;
	cocos2d::Vector<cocos2d::Animate*> _animates;
	cocos2d::Vector<cocos2d::Animation*>  _animations;

	cocos2d::Sprite* _back_Sprite;


	std::vector<cocos2d::Vec2> _face_pos;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void activateGameScene(Ref * pSender);

	void activateTutorial(Ref * pSender);

	void loadNetworkMenu(Ref * pSender);

	void loadOptionsMenu(Ref * pSender);

	void loadGameMenu(Ref * pSender);

	void playAnimation(int anim);

	void createAssets();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif // __HELLOWORLD_SCENE_H__
