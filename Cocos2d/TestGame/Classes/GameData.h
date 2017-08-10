#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <memory>
////////////////////////////////////////////////////////////
/// \brief A class that stores gameplay data
/// 
////////////////////////////////////////////////////////////


class GameData {
private:
	//Constructor
	GameData();

	static std::weak_ptr<GameData> m_instance;

	friend std::weak_ptr < GameData >;
	friend std::shared_ptr < GameData >;
public:
	//Get instance of singleton
	static std::shared_ptr<GameData> sharedGameData();

	std::string m_mainMenu_Back;
	std::string m_mainMenu_btn1_plist;
	std::string m_mainMenu_btn1_ss;
	std::string m_mainMenu_play_noclick;
	std::string m_mainMenu_play_click;
	std::string m_mainMenu_options_noclick;
	std::string m_mainMenu_options_click;
	std::string m_mainMenu_load_noclick;
	std::string m_mainMenu_load_click;
	std::string m_mainMenu_network_noclick;
	std::string m_mainMenu_network_click;
	std::string m_mainMenu_exit_click;
	std::string m_mainMenu_exit_noclick;

	std::string m_game_Back;
	std::string m_game_pause_noclick;
	std::string m_game_pause_click;
	std::string m_game_test_sheet;
	std::string m_game_test_plist;
	std::string m_game_fireball_sheet;
	std::string m_game_fireball_plist;

	std::string m_pauseMenu_Back;
	std::string m_pauseMenu_resume_noclick;
	std::string m_pauseMenu_resume_click;
	std::string m_pauseMenu_retry_noclick;
	std::string m_pauseMenu_retry_click;
	std::string m_pauseMenu_save_noclick;
	std::string m_pauseMenu_save_click;
	std::string m_pauseMenu_load_noclick;
	std::string m_pauseMenu_load_click;
	std::string m_pauseMenu_exittomenu_noclick;
	std::string m_pauseMenu_exittomenu_click;
	
};

#endif