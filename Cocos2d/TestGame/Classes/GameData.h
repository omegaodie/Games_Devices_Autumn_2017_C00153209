#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <memory>
#include "BasicTypes.h"
////////////////////////////////////////////////////////////
/// \brief A class that stores gameplay data
/// 
////////////////////////////////////////////////////////////

using namespace basic_Types;

class GameData {
private:
	//Constructor
	GameData();

	static std::weak_ptr<GameData> m_instance;

	friend std::weak_ptr < GameData >;
	friend std::shared_ptr < GameData >;
public:

	int _resoloution;

	bool win =  false;

	int _gameMode = 0; // 0 = Tutorial, 1 = Game

	float _difficulty_option_playerHP = 5;
	float _difficulty_option_zombieHP = 3;
	float _difficulty_option_zombieMAXSpeed = 30;

	int difficulty = 0; // 0 = easy, 1 = medium, 2 =  hard
	//Get instance of singleton
	static std::shared_ptr<GameData> sharedGameData();


	//////////////////////////////////////////
	//////////TUTORIAL ASSETS ////////////
	//////////////////////////////////////////


	Vector2 m_tutorial_player_start_sd;
	Vector2 m_tutorial_player_start_hd;
	Vector2 m_tutorial_player_start_shd;

	Vector2 m_tutorial_zombie_start_sd;
	Vector2 m_tutorial_zombie_start_hd;
	Vector2 m_tutorial_zombie_start_shd;


	Vector2 m_tutorial_box_start_sd;
	Vector2 m_tutorial_box_start_hd;
	Vector2 m_tutorial_box_start_shd;


	Vector2 m_tutorial_end_start_sd;
	Vector2 m_tutorial_end_start_hd;
	Vector2 m_tutorial_end_start_shd;

	std::string m_tutorial_text_plist_src;
	std::string m_tutorial_text_img_src;


	//////////////////////////////////////////
	//////////////////////////////////////////


	//////////////////////////////////////////
	//////////GAME ASSETS ////////////
	//////////////////////////////////////////




	///HUD


	std::string _hud_skull;

	std::string m_game_pause_noclick;
	std::string m_game_pause_click;

	std::string m_game_blank;


	std::string m_game_slow_noclick;
	std::string m_game_slow_click;


	//std::string m_game_slow_noclick;
	//std::string m_game_slow_click;


	std::string m_hud;
	std::string m_hud_bullet_sprite;


	std::vector<Vector2> m_hud_positions_sd;
	std::vector<Vector2> m_hud_positions_hd;
	std::vector<Vector2> m_hud_positions_shd;


	std::string m_game_explosion_plist;
	std::string m_game_explosion_img;

	///HUD

	int m_game_num_levels;
	std::vector<int> m_game_num_walls_in_level;
	std::vector<std::vector<Vector2>> m_game_wall_positions_sd;
	std::vector<std::vector<Vector2>> m_game_wall_positions_hd;
	std::vector<std::vector<Vector2>> m_game_wall_positions_shd;

	int _num_female_files;
	std::string _female_file_name;

	int _num_player_files;
	std::string _player_file_name;

	int _num_box_files;
	std::string _box_file_name;

	std::vector<Vector2> m_game_player_start_sd;
	std::vector<Vector2> m_game_player_start_hd;
	std::vector<Vector2> m_game_player_start_shd;

	std::vector<std::vector<Vector2>> m_game_zombies_start_sd;
	std::vector<std::vector<Vector2>> m_game_zombies_start_hd;
	std::vector<std::vector<Vector2>> m_game_zombies_start_shd;

	std::vector<int> m_game_num_zombies_in_level;

	std::vector<Vector2> m_game_end_pos_sd;
	std::vector<Vector2> m_game_end_pos_hd;
	std::vector<Vector2> m_game_end_pos_shd;



	//////////////////////////////////////////
	//////////GENERAL MENU ASSETS ////////////
	//////////////////////////////////////////
	std::string m_generalmenu_assets;
	std::vector<Vector2> _menu_face_pos_sd;
	std::vector<Vector2> _menu_face_pos_hd;
	std::vector<Vector2> _menu_face_pos_shd;

	//////////////////////////////////////////
	//////////////////////////////////////////


	//////////////////////////////////////////
	//////////MAIN MENU ASSETS ////////////
	//////////////////////////////////////////
	std::string m_mainMenu_play_noclick;
	std::string m_mainMenu_play_click;

	std::string m_mainMenu_tutorial_noclick;
	std::string m_mainMenu_tutorial_click;

	std::string m_mainMenu_options_noclick;
	std::string m_mainMenu_options_click;

	std::string m_mainMenu_load_noclick;
	std::string m_mainMenu_load_click;

	std::string m_mainMenu_network_noclick;
	std::string m_mainMenu_network_click;

	std::string m_mainMenu_exit_click;
	std::string m_mainMenu_exit_noclick;
	//////////////////////////////////////////
	//////////////////////////////////////////


	//////////////////////////////////////////
	//////////PAUSE MENU ASSETS ////////////
	//////////////////////////////////////////
	std::string m_pauseMenu_resume_noclick;
	std::string m_pauseMenu_resume_click;

	std::string m_pauseMenu_retry_noclick;
	std::string m_pauseMenu_retry_click;

	std::string m_pauseMenu_save_noclick;
	std::string m_pauseMenu_save_click;

	//std::string m_pauseMenu_load_noclick;
	//std::string m_pauseMenu_load_click;

	std::string m_pauseMenu_exittomenu_noclick;
	std::string m_pauseMenu_exittomenu_click;
	//////////////////////////////////////////
	//////////////////////////////////////////


	//////////////////////////////////////////
	//////////NETWORK MENU ASSETS ////////////
	//////////////////////////////////////////
	std::string m_networkMenu_exittomenu_noclick;
	std::string m_networkMenu_exittomenu_click;
	//////////////////////////////////////////
	//////////////////////////////////////////


	//////////////////////////////////////////
	//////////LOAD MENU ASSETS ////////////
	//////////////////////////////////////////
	std::string m_loadGameMenu_exittomenu_noclick;
	std::string m_loadGameMenu_exittomenu_click;
	//////////////////////////////////////////
	//////////////////////////////////////////


	//////////////////////////////////////////
	//////////OPTION MENU ASSETS ////////////
	//////////////////////////////////////////
	std::string m_optionMenu_exittomenu_noclick;
	std::string m_optionMenu_exittomenu_click;

	std::string m_optionMenu_increase_noclick;
	std::string m_optionMenu_increase_click;

	std::string m_optionMenu_decrease_noclick;
	std::string m_optionMenu_decrease_click;
	//////////////////////////////////////////
	//////////////////////////////////////////


	//////////////////////////////////////////
	//////////GAME OVER ASSETS ////////////
	//////////////////////////////////////////

	std::string m_over_loss;
	std::string m_over_win;

	//////////////////////////////////////////
	//////////////////////////////////////////
};

#endif