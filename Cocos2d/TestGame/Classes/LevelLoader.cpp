#include "LevelLoader.h"


using namespace basic_Types;
////////////////////////////////////////////////////////////
LevelLoader::LevelLoader(std::string const & filename) 
{
	loadJSONData(filename);
	m_document.Parse<0>(m_JSONData.c_str());	
	loadGameData();
}

////////////////////////////////////////////////////////////
void LevelLoader::loadJSONData(std::string const & filename)
{
	m_JSONData.clear();

	auto fileUtils = cocos2d::FileUtils::getInstance();
	// Loads all the data in the file into a std::string.
	m_JSONData = fileUtils->getStringFromFile(filename);
}


////////////////////////////////////////////////////////////
void LevelLoader::loadGameData()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	Value::ConstMemberIterator it1 = m_document["Resources"].MemberBegin();

	Value const & GeneralMenu = it1->value;
	assert(GeneralMenu.IsObject());

	ptr->m_generalmenu_assets = GeneralMenu["src"].GetString();

	for (int i = 0; i < 8; i++) 
	{
		ptr->_menu_face_pos_sd.push_back(Vector2(GeneralMenu["face_pos"]["sd"][i]["x"].GetInt(), GeneralMenu["face_pos"]["sd"][i]["y"].GetInt()));
		ptr->_menu_face_pos_hd.push_back(Vector2(GeneralMenu["face_pos"]["hd"][i]["x"].GetInt(), GeneralMenu["face_pos"]["hd"][i]["y"].GetInt()));
		ptr->_menu_face_pos_sd.push_back(Vector2(GeneralMenu["face_pos"]["shd"][i]["x"].GetInt(), GeneralMenu["face_pos"]["shd"][i]["y"].GetInt()));
	}

	it1++;

	Value const & MainMenu = it1->value;
	assert(MainMenu.IsObject());

	ptr->m_mainMenu_play_noclick = MainMenu["button_play_1"].GetString();
	ptr->m_mainMenu_play_click = MainMenu["button_play_2"].GetString();

	ptr->m_mainMenu_tutorial_noclick = MainMenu["button_tutorial_1"].GetString();
	ptr->m_mainMenu_tutorial_click = MainMenu["button_tutorial_2"].GetString();

	ptr->m_mainMenu_network_noclick = MainMenu["button_network_1"].GetString();
	ptr->m_mainMenu_network_click = MainMenu["button_network_2"].GetString();

	ptr->m_mainMenu_options_noclick = MainMenu["button_options_1"].GetString();
	ptr->m_mainMenu_options_click = MainMenu["button_options_2"].GetString();

	ptr->m_mainMenu_load_noclick = MainMenu["button_load_1"].GetString();
	ptr->m_mainMenu_load_click = MainMenu["button_load_2"].GetString();

	ptr->m_mainMenu_exit_noclick = MainMenu["button_exit_1"].GetString();
	ptr->m_mainMenu_exit_click = MainMenu["button_exit_2"].GetString();

	it1++;

	Value const & PauseMenu = it1->value;
	assert(PauseMenu.IsObject());
	ptr->m_pauseMenu_resume_noclick = PauseMenu["button_resume_1"].GetString();
	ptr->m_pauseMenu_resume_click = PauseMenu["button_resume_2"].GetString();

	ptr->m_pauseMenu_retry_noclick = PauseMenu["button_restart_1"].GetString();
	ptr->m_pauseMenu_retry_click = PauseMenu["button_restart_2"].GetString();

	ptr->m_pauseMenu_exittomenu_noclick = PauseMenu["button_menu_1"].GetString();
	ptr->m_pauseMenu_exittomenu_click = PauseMenu["button_menu_2"].GetString();

	it1++;

	

	Value const & NetWorkMenu = it1->value;
	assert(NetWorkMenu.IsObject());
	ptr->m_networkMenu_exittomenu_noclick = NetWorkMenu["return_button_1"].GetString();
	ptr->m_networkMenu_exittomenu_click = NetWorkMenu["return_button_2"].GetString();

	it1++;


	Value const & LoadGameMenu = it1->value;
	assert(LoadGameMenu.IsObject());
	ptr->m_loadGameMenu_exittomenu_noclick = LoadGameMenu["return_button_1"].GetString();
	ptr->m_loadGameMenu_exittomenu_click = LoadGameMenu["return_button_2"].GetString();

	it1++;

	Value const & GameOverMenu = it1->value;
	assert(LoadGameMenu.IsObject());
	ptr->m_over_loss = GameOverMenu["game_over_loss"].GetString();
	ptr->m_over_win = GameOverMenu["game_over_win"].GetString();

	it1++;


	Value const & OptionsMenu = it1->value;
	assert(OptionsMenu.IsObject());
	ptr->m_optionMenu_exittomenu_noclick = OptionsMenu["return_button_1"].GetString();
	ptr->m_optionMenu_exittomenu_click = OptionsMenu["return_button_2"].GetString();

	ptr->m_optionMenu_increase_noclick = OptionsMenu["increase_button_1"].GetString();
	ptr->m_optionMenu_increase_click = OptionsMenu["increase_button_2"].GetString();

	ptr->m_optionMenu_decrease_noclick = OptionsMenu["decrease_button_1"].GetString();
	ptr->m_optionMenu_decrease_click = OptionsMenu["decrease_button_2"].GetString();

	it1++;




	Value const & Game = it1->value;
	assert(Game.IsObject());
	ptr->m_game_pause_noclick = Game["button_pause_1"].GetString();
	ptr->m_game_pause_click = Game["button_pause_2"].GetString();


	ptr->m_game_blank = Game["_blank"].GetString();

	ptr->_num_box_files = Game["Boxes"]["num_files"].GetInt();
	ptr->_box_file_name = Game["Boxes"]["src"].GetString();

	ptr->_num_female_files = Game["_character_assets"]["female_zombie"]["num_file"].GetInt();
	ptr->_female_file_name = Game["_character_assets"]["female_zombie"]["file_name"].GetString();


	ptr->_num_player_files = Game["_character_assets"]["_player"]["num_file"].GetInt();
	ptr->_player_file_name = Game["_character_assets"]["_player"]["file_name"].GetString();


	ptr->m_hud = Game["HUD"]["HUd_src"].GetString();
	ptr->_hud_skull = Game["HUD"]["Hud_skull"].GetString();
	ptr->m_hud_bullet_sprite = Game["HUD"]["Bullet_src"].GetString();

	ptr->m_game_explosion_plist = Game["Boom"]["src_plist"].GetString();
	ptr->m_game_explosion_img = Game["Boom"]["src_img"].GetString();

	ptr->m_hud_positions_sd.push_back(Vector2(Game["HUD"]["sd"]["timer_box_pos"]["x"].GetInt(), Game["HUD"]["sd"]["timer_box_pos"]["y"].GetInt()));
	ptr->m_hud_positions_sd.push_back(Vector2(Game["HUD"]["sd"]["ammo_box_pos"]["x"].GetInt(), Game["HUD"]["sd"]["ammo_box_pos"]["y"].GetInt()));
	ptr->m_hud_positions_sd.push_back(Vector2(Game["HUD"]["sd"]["health_box_pos"]["x"].GetInt(), Game["HUD"]["sd"]["health_box_pos"]["y"].GetInt()));

	ptr->m_hud_positions_hd.push_back(Vector2(Game["HUD"]["hd"]["timer_box_pos"]["x"].GetInt(), Game["HUD"]["hd"]["timer_box_pos"]["y"].GetInt()));
	ptr->m_hud_positions_hd.push_back(Vector2(Game["HUD"]["hd"]["ammo_box_pos"]["x"].GetInt(), Game["HUD"]["hd"]["ammo_box_pos"]["y"].GetInt()));
	ptr->m_hud_positions_hd.push_back(Vector2(Game["HUD"]["hd"]["health_box_pos"]["x"].GetInt(), Game["HUD"]["hd"]["health_box_pos"]["y"].GetInt()));

	ptr->m_hud_positions_shd.push_back(Vector2(Game["HUD"]["shd"]["timer_box_pos"]["x"].GetInt(), Game["HUD"]["shd"]["timer_box_pos"]["y"].GetInt()));
	ptr->m_hud_positions_shd.push_back(Vector2(Game["HUD"]["shd"]["ammo_box_pos"]["x"].GetInt(), Game["HUD"]["shd"]["ammo_box_pos"]["y"].GetInt()));
	ptr->m_hud_positions_shd.push_back(Vector2(Game["HUD"]["shd"]["health_box_pos"]["x"].GetInt(), Game["HUD"]["shd"]["health_box_pos"]["y"].GetInt()));


	

	ptr->m_tutorial_text_img_src = Game["tutorial"]["tutorial_text"]["src_img"].GetString();
	ptr->m_tutorial_text_plist_src = Game["tutorial"]["tutorial_text"]["src_plist"].GetString();


	ptr->m_tutorial_player_start_sd = Vector2(Game["tutorial"]["sd"]["player_spawn"]["X"].GetInt(), Game["tutorial"]["sd"]["player_spawn"]["Y"].GetInt() );
	ptr->m_tutorial_player_start_hd = Vector2(Game["tutorial"]["hd"]["player_spawn"]["X"].GetInt(), Game["tutorial"]["hd"]["player_spawn"]["Y"].GetInt());
	ptr->m_tutorial_player_start_shd = Vector2(Game["tutorial"]["shd"]["player_spawn"]["X"].GetInt(), Game["tutorial"]["shd"]["player_spawn"]["Y"].GetInt());


	ptr->m_tutorial_zombie_start_sd = Vector2(Game["tutorial"]["sd"]["Zombie_spawn"]["X"].GetInt(), Game["tutorial"]["sd"]["Zombie_spawn"]["Y"].GetInt());
	ptr->m_tutorial_zombie_start_hd = Vector2(Game["tutorial"]["hd"]["Zombie_spawn"]["X"].GetInt(), Game["tutorial"]["hd"]["Zombie_spawn"]["Y"].GetInt());
	ptr->m_tutorial_zombie_start_shd = Vector2(Game["tutorial"]["shd"]["Zombie_spawn"]["X"].GetInt(), Game["tutorial"]["shd"]["Zombie_spawn"]["Y"].GetInt());


	ptr->m_tutorial_box_start_sd = Vector2(Game["tutorial"]["sd"]["Box_spawn"]["X"].GetInt(), Game["tutorial"]["sd"]["Box_spawn"]["Y"].GetInt());
	ptr->m_tutorial_box_start_hd = Vector2(Game["tutorial"]["hd"]["Box_spawn"]["X"].GetInt(), Game["tutorial"]["hd"]["Box_spawn"]["Y"].GetInt());
	ptr->m_tutorial_box_start_shd = Vector2(Game["tutorial"]["shd"]["Box_spawn"]["X"].GetInt(), Game["tutorial"]["shd"]["Box_spawn"]["Y"].GetInt());


	ptr->m_tutorial_end_start_sd = Vector2(Game["tutorial"]["sd"]["Exit_spawn"]["X"].GetInt(), Game["tutorial"]["sd"]["Exit_spawn"]["Y"].GetInt());
	ptr->m_tutorial_end_start_hd = Vector2(Game["tutorial"]["hd"]["Exit_spawn"]["X"].GetInt(), Game["tutorial"]["hd"]["Exit_spawn"]["Y"].GetInt());
	ptr->m_tutorial_end_start_shd = Vector2(Game["tutorial"]["shd"]["Exit_spawn"]["X"].GetInt(), Game["tutorial"]["shd"]["Exit_spawn"]["Y"].GetInt());
		

	ptr->m_game_num_levels = Game["num_levels"].GetInt();

	for (int i = 0; i < ptr->m_game_num_levels; i++) 
	{
		ptr->m_game_end_pos_sd.push_back(Vector2(Game["Levels"][i]["end"]["sd"]["sX"].GetInt(), Game["Levels"][i]["end"]["sd"]["sY"].GetInt()));
		ptr->m_game_end_pos_hd.push_back(Vector2(Game["Levels"][i]["end"]["hd"]["sX"].GetInt(), Game["Levels"][i]["end"]["hd"]["sY"].GetInt()));
		ptr->m_game_end_pos_shd.push_back(Vector2(Game["Levels"][i]["end"]["shd"]["sX"].GetInt(), Game["Levels"][i]["end"]["shd"]["sY"].GetInt()));

		ptr->m_game_player_start_sd.push_back(Vector2(Game["Levels"][i]["player_start"]["sd"]["sX"].GetInt(), Game["Levels"][i]["player_start"]["sd"]["sY"].GetInt()));
		ptr->m_game_player_start_hd.push_back(Vector2(Game["Levels"][i]["player_start"]["hd"]["sX"].GetInt(), Game["Levels"][i]["player_start"]["hd"]["sY"].GetInt()));
		ptr->m_game_player_start_shd.push_back(Vector2(Game["Levels"][i]["player_start"]["shd"]["sX"].GetInt(), Game["Levels"][i]["player_start"]["shd"]["sY"].GetInt()));
		ptr->m_game_num_zombies_in_level.push_back(Game["Levels"][i]["_num_zombies"].GetInt());
		ptr->m_game_zombies_start_sd.push_back(std::vector<Vector2>());
		ptr->m_game_zombies_start_hd.push_back(std::vector<Vector2>());
		ptr->m_game_zombies_start_shd.push_back(std::vector<Vector2>());
		for (int j = 0; j < ptr->m_game_num_zombies_in_level[i]; j++) 
		{

			ptr->m_game_zombies_start_sd[i].push_back(Vector2(Game["Levels"][i]["zombie_start"]["sd"][j]["sX"].GetInt(),
				Game["Levels"][i]["zombie_start"]["sd"][j]["sY"].GetInt()));

			ptr->m_game_zombies_start_hd[i].push_back(Vector2(Game["Levels"][i]["zombie_start"]["hd"][j]["sX"].GetInt(),
				Game["Levels"][i]["zombie_start"]["hd"][j]["sY"].GetInt()));

			ptr->m_game_zombies_start_shd[i].push_back(Vector2(Game["Levels"][i]["zombie_start"]["shd"][j]["sX"].GetInt(),
				Game["Levels"][i]["zombie_start"]["shd"][j]["sY"].GetInt()));
		}



		ptr->m_game_wall_positions_sd.push_back(std::vector<basic_Types::Vector2>());
		ptr->m_game_wall_positions_hd.push_back(std::vector<basic_Types::Vector2>());
		ptr->m_game_wall_positions_shd.push_back(std::vector<basic_Types::Vector2>());

		ptr->m_game_num_walls_in_level.push_back(Game["Levels"][i]["_num_walls"].GetInt());
		for (int k = 0; k < ptr->m_game_num_walls_in_level[i]; k++)
		{
			ptr->m_game_wall_positions_sd[i].push_back(basic_Types::Vector2(Game["Levels"][i]["walls"]["sd"][k]["X"].GetInt(), Game["Levels"][i]["walls"]["sd"][k]["Y"].GetInt()));
			ptr->m_game_wall_positions_hd[i].push_back(basic_Types::Vector2(Game["Levels"][i]["walls"]["hd"][k]["X"].GetInt(), Game["Levels"][i]["walls"]["hd"][k]["Y"].GetInt()));
			ptr->m_game_wall_positions_shd[i].push_back(basic_Types::Vector2(Game["Levels"][i]["walls"]["shd"][k]["X"].GetInt(), Game["Levels"][i]["walls"]["shd"][k]["Y"].GetInt()));

		}
	}
}
