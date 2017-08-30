#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <random>
USING_NS_CC;



Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto label = Label::createWithTTF("      ", "fonts/youmurdererbb_reg.ttf", 64);
	this->addChild(label, 3, 22);

	ptr->_gameMode = 1;

	//addBackGroundSprite(visibleSize, origin);
	wall_drawer = CCDrawNode::create();
	hp_drawer = CCDrawNode::create();
	this->addChild(hp_drawer, -1);
	this->addChild(wall_drawer, -1);
	_bullet_drawer = CCDrawNode::create();
	this->addChild(_bullet_drawer);
	this->draw_Walls();
	this->drawEnd(0);
	addPlayer(visibleSize, origin);
	addZombies(visibleSize, origin);
	//addWalls(visibleSize, origin);
	_hud_skull_pos = Vec2(visibleSize.width / 6, visibleSize.height - (visibleSize.height / 12));
	_ai_mngr = new AIManager(*_player_one, _zombies);

	for (int i = 0; i < ptr->m_game_num_zombies_in_level[0]; i++) 
	{
		_Boxes.pushBack(Item::create(i % 3, Vec2(ptr->m_game_zombies_start_hd[0][i].x, ptr->m_game_zombies_start_hd[0][i].y)));
		this->addChild(_Boxes.at(i));
	}

	for (int i = 0; i < 6; i++) {
		auto _s = Sprite::create(ptr->m_hud_bullet_sprite);
		this->addChild(_s, 2, 80 + i);
	}
	//Label* label;
	//this->addChild(label, 3, 22);

	_currentFrame = 0;
	_frameLenght = 0.02;
    // 3. add your codes below...

	_pause_screen_pos = Vec2(visibleSize.width / 12, visibleSize.height - (visibleSize.height / 12));
	auto pauseItem =
		MenuItemImage::create(ptr->m_game_blank,
			ptr->m_game_blank,
			CC_CALLBACK_1(GameScene::activatePauseScene, this));

	//pauseItem->setPosition(Vec2(50, 750));
	pauseItem->setPosition(Point(visibleSize.width / 12, visibleSize.height - (visibleSize.height / 12)));


	auto followAction = Follow::create(_player_one, cocos2d::Rect());
	this->runAction(followAction);
	// The Rect you give is the bounds the player can move before 
	// the camera (layer) starts following it. Giving empty rect will make sure the camera
	// follows as soon as your player starts moving.

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->scheduleUpdate();
	this->addChild(menu);

	hud_init(visibleSize);
	

	_cm = new CollisionManager(*_player_one, _zombies, _Boxes, _endRect, _walls_pos);
	//_cm = new CollisionManager(*_player_one, _zombies, _endRect, _walls_pos);
	_cm->initLevel();
    return true;
}

void GameScene::update(float _dt )
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	//auto _p = this->getChildByTag(22);
	if (_player_one->getAlive()) {
		if (_way_clear) {
			if (_endRect.intersectsRect(cocos2d::Rect(_player_one->getPosition(), cocos2d::Size(128, 128)))) {
				//end level
				ptr->win = true;
				activateGameOverScene(this);
			}
		}
		if (_way_clear) 
		{
			_Boxes.clear();
			//_Boxes.
			if (_cm->endPlayer()) {
				//end level
			
				ptr->win = true;
				activateGameOverScene(this);
				//activateMainMenuScene(this);
			}
		}
		hud_update(_dt);
		_currentFrame += _dt;
		_cm->update(_dt);
		_currentFrame = 0;
		_player_one->update(_dt);
		drawBullets();
	}
	else 
	{
		ptr->win = false;
		activateGameOverScene(this);
	}
}

void GameScene::activateGameOverScene(Ref *pSender)
{
	//this->removeFromParentAndCleanup(true);
	//this->removeAllChildrenWithCleanup(true);
	this->getScheduler()->unscheduleUpdateForTarget(this);
	this->getScheduler()->unscheduleUpdateForTarget(_player_one);
	for (int i = 0; i < _zombies.size(); i++) {
		this->getScheduler()->unscheduleUpdateForTarget(_zombies.at(i));
	}
	this->getScheduler()->unscheduleUpdateForTarget(_player_one);

	this->stopActionByTag(1);
	//_player_one->cleanup();
	auto scene = GameOverScene::createScene();
	//Director::getInstance()->replaceScene(TransitionFade::create(0.99f, scene, Color3B(0, 0, 0)));
	Director::getInstance()->replaceScene(scene);
}

void GameScene::draw_Walls()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	//red line from bottom left to top right corner

	Color4F _col = Color4F(1.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < ptr->m_game_num_walls_in_level[0]; i++) 
	{

		if (ptr->_resoloution == 0)
		{

			if (i == 0) 
			{
				wall_drawer->drawSegment(Vec2(ptr->m_game_wall_positions_sd[0][ptr->m_game_num_walls_in_level[0] - 1].x,
					(basic_Types::back_sd_y) - ptr->m_game_wall_positions_sd[0][ptr->m_game_num_walls_in_level[0] - 1].y),
					Vec2(ptr->m_game_wall_positions_sd[0][i].x, ptr->m_game_wall_positions_sd[0][i].y), 10.0f, _col);
			}
			else 
			{
				wall_drawer->drawSegment(Vec2(ptr->m_game_wall_positions_sd[0][i - 1].x,
					(basic_Types::back_sd_y) - ptr->m_game_wall_positions_sd[0][i - 1].y),
					Vec2(ptr->m_game_wall_positions_sd[0][i].x, ptr->m_game_wall_positions_sd[0][i].y), 10.0f, _col);
			}
		}
		else if (ptr->_resoloution == 1)
		{
			if (i == 0)
			{
				wall_drawer->drawSegment(Vec2(ptr->m_game_wall_positions_hd[0][ptr->m_game_num_walls_in_level[0] - 1].x,
					(basic_Types::back_hd_y) - ptr->m_game_wall_positions_hd[0][ptr->m_game_num_walls_in_level[0] - 1].y),
					Vec2(ptr->m_game_wall_positions_hd[0][i].x,
					(basic_Types::back_hd_y) - ptr->m_game_wall_positions_hd[0][i].y), 10.0f, _col);
			}
			else
			{
				wall_drawer->drawSegment(Vec2(ptr->m_game_wall_positions_hd[0][i - 1].x,
					(basic_Types::back_hd_y) - ptr->m_game_wall_positions_hd[0][i - 1].y),
					Vec2(ptr->m_game_wall_positions_hd[0][i].x, 
					(basic_Types::back_hd_y) - ptr->m_game_wall_positions_hd[0][i].y), 10.0f, _col);
			}
		}
		else
		{
			if (i == 0)
			{
				wall_drawer->drawSegment(
					Vec2(ptr->m_game_wall_positions_shd[0][ptr->m_game_num_walls_in_level[0] - 1].x,
					(basic_Types::back_shd_y) - ptr->m_game_wall_positions_shd[0][ptr->m_game_num_walls_in_level[0] - 1].y),
					Vec2(ptr->m_game_wall_positions_shd[0][i].x,
					(basic_Types::back_shd_y) - ptr->m_game_wall_positions_shd[0][i].y), 10.0f, _col);
			}
			else
			{
				wall_drawer->drawSegment(Vec2(ptr->m_game_wall_positions_shd[0][i - 1].x,
					(basic_Types::back_sd_y) - ptr->m_game_wall_positions_shd[0][i - 1].y),
					Vec2(ptr->m_game_wall_positions_shd[0][i].x,
					(basic_Types::back_sd_y) - ptr->m_game_wall_positions_shd[0][i].y), 10.0f, _col);
			}
		}
	}

	for (int i = 0; i < ptr->m_game_num_walls_in_level[0]; i++)
	{
		if (ptr->_resoloution == 0)
		{
			_walls_pos.push_back(Vec2(ptr->m_game_wall_positions_sd[0][i].x, (basic_Types::back_sd_y) - ptr->m_game_wall_positions_sd[0][i].y));
		}
		else if (ptr->_resoloution == 1)
		{
			_walls_pos.push_back(Vec2(ptr->m_game_wall_positions_hd[0][i].x, (basic_Types::back_hd_y) - ptr->m_game_wall_positions_hd[0][i].y));
		}
		else
		{
			_walls_pos.push_back(Vec2(ptr->m_game_wall_positions_shd[0][i].x, (basic_Types::back_shd_y) - ptr->m_game_wall_positions_shd[0][i].y));
		}
	}
}

void GameScene::drawBullets()
{
	if (_player_one->getFiring())
	{
		Color4F _col = Color4F(0.0f, 1.0f, 0.0f, 1.0f);
		float _t = _player_one->getTheta();
		Vec2 bulletS = _player_one->getPosition() + ((Vec2(cos(_t), sin(_t))) * (1500 - rand() % 1500));
		Vec2 bulletE = bulletS + (Vec2(cos(_t), sin(_t)) * 50);
		_bullet_drawer->drawSegment(bulletS, bulletE, 0.1f, _col);

		//_bullet_drawer->scheduleOnce(schedule_selector(&CCDrawNode::clear), 0.2f);
		const float myDelay = 1.0f;
		this->runAction(Sequence::create(
			DelayTime::create(myDelay),
			CallFunc::create(CC_CALLBACK_0(CCDrawNode::clear, _bullet_drawer)),
			nullptr));
	}
}

void GameScene::drawEnd(int l)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	//red line from bottom left to top right corner

	Color4F _col = Color4F(0.0f, 0.0f, 1.0f, 1.0f);
		if (ptr->_resoloution == 0)
		{

			wall_drawer->drawRect(Vec2(ptr->m_game_end_pos_sd[l].x - 180,
				(basic_Types::back_sd_y) - ptr->m_game_end_pos_sd[l].y - 180),
				Vec2(ptr->m_game_end_pos_sd[l].x + 180, (basic_Types::back_sd_y) - ptr->m_game_end_pos_sd[l].y + 180), _col);

			_endRect = cocos2d::Rect(Vec2(ptr->m_game_end_pos_sd[l].x, (basic_Types::back_sd_y) - ptr->m_game_end_pos_sd[l].y), cocos2d::Size(180, 180));
		}
		else if (ptr->_resoloution == 1)
		{
			wall_drawer->drawRect(Vec2(ptr->m_game_end_pos_hd[0].x - 100,
				(basic_Types::back_hd_y) - (ptr->m_game_end_pos_hd[0].y - 100)),
				Vec2(ptr->m_game_end_pos_hd[l].x + 100,
				(basic_Types::back_hd_y) - (ptr->m_game_end_pos_hd[l].y + 100)), _col);

			_endRect = cocos2d::Rect(Vec2(ptr->m_game_end_pos_hd[l].x, (basic_Types::back_hd_y) - ptr->m_game_end_pos_hd[l].y), cocos2d::Size(250, 250));
		}
		else
		{
			wall_drawer->drawRect(Vec2(ptr->m_game_end_pos_shd[l].x - 250,
				(basic_Types::back_shd_y) - ptr->m_game_end_pos_shd[l].y - 250),
				Vec2(ptr->m_game_end_pos_shd[l].x + 250, (basic_Types::back_shd_y) - ptr->m_game_end_pos_shd[l].y + 250), _col);
			_endRect = cocos2d::Rect(Vec2(ptr->m_game_end_pos_shd[l].x, (basic_Types::back_shd_y) - ptr->m_game_end_pos_shd[l].y), cocos2d::Size(250, 250));

		}
}

void GameScene::activatePauseScene(Ref *pSender)
{
	auto scene = PauseMenu::createScene();
	Director::getInstance()->pushScene(scene);
}

void GameScene::addPlayer(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	if (visibleSize.width == 800)
	{
		_player_one = Player::create(Vec2(ptr->m_game_player_start_sd[0].x, basic_Types::back_sd_y - ptr->m_game_player_start_sd[0].y));
	}
	else if (visibleSize.width == 1280)
	{
		_player_one = Player::create(Vec2(ptr->m_game_player_start_hd[0].x, basic_Types::back_hd_y - ptr->m_game_player_start_hd[0].y));
	}
	else
	{
		_player_one = Player::create(Vec2(ptr->m_game_player_start_shd[0].x, basic_Types::back_shd_y - ptr->m_game_player_start_shd[0].y));
	}
	this->addChild(_player_one, 1);
}

void GameScene::addZombies(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	Vec2 _offset = Vec2();
	Vec2 _spawn_centre;
	int rX, rY;
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(-200, 200); // guaranteed unbiased

	_num_zombies_spawn = ptr->m_game_num_zombies_in_level[0];
	int num_z = 0;
	if (visibleSize.width == 800)
	{
		for (int i = 0; i < _num_zombies_spawn; i++) 
		{
			_spawn_centre = Vec2(ptr->m_game_zombies_start_sd[0][i].x,
				basic_Types::back_sd_y - ptr->m_game_zombies_start_sd[0][i].y);
			for (int j = 0; j < 5; j++) 
			{
				rX = uni(rng);
				rY = uni(rng);
				_offset = Vec2(rX, rY);
				_zombies.pushBack(Boid::create(
					Vec2(_spawn_centre + _offset),
					0,
					_zombies,
					*_player_one));
				this->addChild(_zombies.at(num_z));
				num_z++;
			}
		}
	}
	else if (visibleSize.width == 1280)
	{
			for (int i = 0; i < _num_zombies_spawn; i++)
			{
				_spawn_centre = Vec2(ptr->m_game_zombies_start_hd[0][i].x,
					basic_Types::back_hd_y - ptr->m_game_zombies_start_hd[0][i].y);
				for (int j = 0; j < 5; j++) 
				{
					rX = uni(rng);
					rY = uni(rng);
					_offset = Vec2(rX, rY);
					_zombies.pushBack(Boid::create(
						Vec2(_spawn_centre + _offset),
						0,
						_zombies,
						*_player_one));
					this->addChild(_zombies.at(num_z));
					num_z++;
				}
			}
	}
	else
	{
		for (int i = 0; i < _num_zombies_spawn; i++) 
		{
			_spawn_centre = Vec2(ptr->m_game_zombies_start_shd[0][i].x,
				basic_Types::back_shd_y - ptr->m_game_zombies_start_shd[0][i].y);
			for (int j = 0; j < 5; j++) 
			{
				rX = uni(rng);
				rY = uni(rng);
				_offset = Vec2(rX, rY);
				_zombies.pushBack(Boid::create(
					Vec2(_spawn_centre + _offset),
					0,
					_zombies,
					*_player_one));
				this->addChild(_zombies.at(num_z));
				num_z++;
			}
		}
	}
}

void GameScene::menuCloseCallback(Ref* pSender)
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

void GameScene::hud_init(cocos2d::Size const & visibleSize)
{
	drawing_explode_timer = false;
	drawing_deton_Timer = false;
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	_timer_Box = Sprite::create(ptr->m_hud);
	_ammo_box = Sprite::create(ptr->m_hud);
	_health_box = Sprite::create(ptr->m_hud);

	_fake_pause_btn = Sprite::create(ptr->m_game_pause_noclick);
	_hud_skull = Sprite::create(ptr->_hud_skull);
	_hud_skull->setPosition(Vec2(-1000, -1000));
	this->addChild(_hud_skull);

	_fake_pause_btn->setPosition(_pause_screen_pos);
	this->addChild(_fake_pause_btn);

	if (ptr->_resoloution == 0)
	{
		_timer_pos = Vec2(ptr->m_hud_positions_sd[0].x, visibleSize.height - ptr->m_hud_positions_sd[0].y);
		_ammo_pos = Vec2(ptr->m_hud_positions_sd[1].x, visibleSize.height - ptr->m_hud_positions_sd[1].y);
		_health_pos = Vec2(ptr->m_hud_positions_sd[2].x, visibleSize.height - ptr->m_hud_positions_sd[2].y);

		_hud_size = Vec2(210, 46);
		_bullet_size = Vec2(16, 33);
	}
	else if (ptr->_resoloution == 1)
	{
		_timer_pos = Vec2(ptr->m_hud_positions_hd[0].x, visibleSize.height - ptr->m_hud_positions_hd[0].y);
		_ammo_pos = Vec2(ptr->m_hud_positions_hd[1].x, visibleSize.height - ptr->m_hud_positions_hd[1].y);
		_health_pos = Vec2(ptr->m_hud_positions_hd[2].x, visibleSize.height - ptr->m_hud_positions_hd[2].y);

		_hud_size = Vec2(330, 61);
		_bullet_size = Vec2(28, 44);
	}
	else
	{
		_timer_pos = Vec2(ptr->m_hud_positions_shd[0].x, visibleSize.height - ptr->m_hud_positions_shd[0].y);
		_ammo_pos = Vec2(ptr->m_hud_positions_shd[1].x, visibleSize.height - ptr->m_hud_positions_shd[1].y);
		_health_pos = Vec2(ptr->m_hud_positions_shd[2].x, visibleSize.height - ptr->m_hud_positions_shd[2].y);


		_hud_size = Vec2(488, 116);
		_bullet_size = Vec2(39, 81);
	}

	this->addChild(_timer_Box, 2, 5);
	this->addChild(_health_box, 2, 6);
	this->addChild(_ammo_box, 2, 7);

	Vec2 _NODE = this->convertToNodeSpace(_timer_pos);
	_timer_Box->setPosition(_NODE);

	_NODE = this->convertToNodeSpace(_ammo_pos);
	_ammo_box->setPosition(_NODE);


	auto label1 = Label::createWithTTF("AMMO", "fonts/youmurdererbb_reg.ttf", 64);
	label1->setPosition(_NODE);
	label1->setColor(Color3B::GREEN);
	this->addChild(label1, 10, 99);



	_NODE = this->convertToNodeSpace(_health_pos);
	_health_box->setPosition(_NODE);


	auto label2 = Label::createWithTTF("HEALTH", "fonts/youmurdererbb_reg.ttf", 64);
	label2->setPosition(_NODE);
	label2->setColor(Color3B::BLACK);
	this->addChild(label2, 10, 98);


	_max_hp = ptr->_difficulty_option_playerHP;

}

void GameScene::hud_update(float _dt)
{
	auto _scene = Director::getInstance()->getRunningScene();

	_way_clear = true;
	for (int i = 0; i < _Boxes.size(); i++)
	{
		if (_Boxes.at(i)->getAlive()) {
			_way_clear = false;
		}
	}

	Vec2 _pause_pos = this->convertToNodeSpace(_pause_screen_pos);

	_fake_pause_btn->setPosition(_pause_pos);
	if (_player_one->getReadyToFire())
	{
		Vec2 _skull_pos = this->convertToNodeSpace(_hud_skull_pos);
		_hud_skull->setPosition(_skull_pos);
	}
	else {
		_hud_skull->setPosition(Vec2(-1000, -1000));
	}


	Vec2 _NODE = this->convertToNodeSpace(_ammo_pos);
	_ammo_box->setPosition(_NODE);
	this->getChildByTag(80)->setPosition(Vec2(-1000, -1000));
	int _leftInMag = _player_one->getAmmo();
	for (int i = 0; i < _leftInMag; i++)
	{
		this->getChildByTag(80 + i)->setPosition(Vec2(_NODE.x - (_hud_size.x / 2) + ((i * _bullet_size.x) + (_hud_size.x / 10)), _NODE.y));
	}
	for (int i = 5; i > _leftInMag; i--)
	{
		this->getChildByTag(80 + i)->setPosition(Vec2(-1000, -1000));
	}

	this->getChildByTag(99)->setPosition(_NODE);


	float _hppercentage = _player_one->getHealth() / _max_hp;

	_NODE = this->convertToNodeSpace(_health_pos);
	_health_box->setPosition(_NODE);
	this->getChildByTag(98)->setPosition(_NODE);
	hp_drawer->clear();
	hp_drawer->drawSolidRect(
		Vec2(_NODE.x - (_hud_size.x / 2), _NODE.y + (_hud_size.y / 2)),
		Vec2((_NODE.x - (_hud_size.x / 2)) + (_hud_size.x  * _hppercentage), _NODE.y - (_hud_size.y / 2)),
		Color4F::YELLOW);

	_NODE = this->convertToNodeSpace(_timer_pos);
	_timer_Box->setPosition(_NODE);


	float detonation_timer;
	for (int i = 0; i < _Boxes.size(); i++)
	{
		if (_Boxes.at(i)->getPlayerContact() && _Boxes.at(i)->getAlive() && !_Boxes.at(i)->getArmed())
		{
			_Boxes.at(i)->update(_dt);
			Color3B _c = Color3B(0, 128, 0);
			detonation_timer = _Boxes.at(i)->getTimer(true);
			std::ostringstream buff;
			buff << detonation_timer;
			Label *label = dynamic_cast<Label *>(this->getChildByTag(22));
			label->setPosition(_NODE);
			label->setColor(cocos2d::Color3B(0, 128, 0));
			label->setString(buff.str());
			drawing_deton_Timer = true;
		}
		else
		{
			drawing_deton_Timer = false;
			Label *label = dynamic_cast<Label *>(this->getChildByTag(22));
			label->setPosition(_NODE);
			label->setString("   ");
			//delete(label);
		}
		if (_Boxes.at(i)->getArmed())
		{
			_Boxes.at(i)->update(_dt);
			if (_Boxes.at(i)->getAlive())
			{
				Color3B _c = Color3B(128, 32, 32);
				detonation_timer = _Boxes.at(i)->getTimer(false);
				std::ostringstream buff;
				buff << detonation_timer;
				Label *label = dynamic_cast<Label *>(this->getChildByTag(22));
				label->setPosition(_NODE);
				label->setColor(cocos2d::Color3B(128, 0, 0));
				label->setString(buff.str());
				drawing_explode_timer = true;
				//delete(label);

			}
			else
			{
				Label *label = dynamic_cast<Label *>(this->getChildByTag(22));
				label->setPosition(_NODE);
				label->setString("   ");
				//delete(label);
				_Boxes.at(i)->setOpacity(GLubyte(0));
			}
		}
	}






}