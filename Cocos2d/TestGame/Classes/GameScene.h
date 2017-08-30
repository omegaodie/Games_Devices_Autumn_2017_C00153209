#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "PauseMenu.h"
#include "GameData.h"
#include "GameOverScene.h"
#include "MainMenu.h"
#include "Item.h"
#include "Player.h"
#include "CollisionManager.h"
#include "AIManager.h"


#pragma once
enum class GameStates
{
	running,
	over,
	nextLevel
};

class GameScene : public cocos2d::Scene
{
private:
	Player* _player_one;

	AIManager* _ai_mngr;

	cocos2d::CCDrawNode* wall_drawer;
	cocos2d::CCDrawNode* hp_drawer;

	cocos2d::CCDrawNode* _bullet_drawer;

	cocos2d::Vector<Boid*> _zombies;

	cocos2d::Vector<Item*> _Boxes;

	cocos2d::Rect _endRect;

	float _lastFrame, _currentFrame , _frameLenght;

	bool drawing_deton_Timer, drawing_explode_timer;

	int _num_zombies_spawn;

	CollisionManager* _cm;

	cocos2d::Sprite* _fake_pause_btn;
	cocos2d::Vec2 _pause_screen_pos;

	cocos2d::Vec2 _hud_skull_pos;
	cocos2d::Sprite* _hud_skull;

	cocos2d::Vec2 _timer_pos;
	cocos2d::Vec2 _ammo_pos;
	cocos2d::Vec2 _health_pos;
	bool _way_clear;

	cocos2d::Sprite* _timer_Box;
	cocos2d::Sprite* _ammo_box;
	cocos2d::Sprite* _health_box;

	cocos2d::Vector<cocos2d::Sprite*> _bullets;
	std::vector<cocos2d::Vec2> _walls_pos;

	std::random_device rd;

	cocos2d::Vec2 _hud_size;
	cocos2d::Vec2 _bullet_size;

	float _max_hp;


public:
    static cocos2d::Scene* createScene();
	static cocos2d::Scene* createScene(bool restart);

    virtual bool init();

	void update(float) override;

	virtual void draw_Walls();

	void drawBullets();

	void drawEnd(int l);

	void hud_init(cocos2d::Size const & visibleSize);

	void hud_update(float _dt);
	
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void addPlayer(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);

	void addZombies(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);

	// Called when user pauses gameplay.
	void activatePauseScene(Ref *pSender);
	// Called at game over 

	void activateGameOverScene(Ref *pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
