function GameScene(ctx){
	this.Levels = [];
	this.loaded = false;
}
GameScene.prototype.load = function(diff)
{
		this.lvlBoxes = [
		{
			0 : {
				boxName : 'Item_Image1', //can add more here i.e box type e.g explosive/imovable etc;
				boxPosX : 800,
				bosPosY : 190
			},
			1 : {
				boxName : 'Item_Image1',
				boxPosX : 200,
				bosPosY : 130
			},
			2 : {
				boxName : 'Item_Image1',
				boxPosX : 375,
				bosPosY : 630
			},
			3 : {
				boxName : 'Item_Image1',
				boxPosX : 140,
				bosPosY : 500
			},
		},
		{
			0 : {
				boxName : 'Item_Image1', //can add more here i.e box type e.g explosive/imovable etc;
				boxPosX : 800,
				bosPosY : 190
			},
			1 : {
				boxName : 'Item_Image1',
				boxPosX : 200,
				bosPosY : 130
			},
			2 : {
				boxName : 'Item_Image1',
				boxPosX : 375,
				bosPosY : 630
			},
			3 : {
				boxName : 'Item_Image1',
				boxPosX : 140,
				bosPosY : 500
			},
		},
		{ 
			0 : {
				boxName : 'Item_Image1', //can add more here i.e box type e.g explosive/imovable etc;
				boxPosX : 800,
				bosPosY : 190
			},
			1 : {
				boxName : 'Item_Image1',
				boxPosX : 200,
				bosPosY : 130
			},
			2 : {
				boxName : 'Item_Image1',
				boxPosX : 375,
				bosPosY : 630
			},
			3 : {
				boxName : 'Item_Image1',
				boxPosX : 140,
				bosPosY : 500
			},
		},
	];
	this.Modes = [
		{
			"num_ai" : [
				5,
				6,
				7
			],
			"num_boxes" : [
				1,
				2,
				3
			]
		},
		{
			"num_ai" : [
				15,
				26,
				17
			],
			"num_boxes" : [
				4,
				3,
				4
			]
		}
	];
	this.scenes = [
		{
			map : GameData.first_room.t,
			numEnemy : this.Modes[diff].num_ai[0],
			typeEnemy : GameData.Enemy_Image1,
			num_boxes : this.Modes[diff].num_boxes[0],
			dimensionX : 2747,
			dimensionY : 719
		},
		{
			map : GameData.second_room.t,
			numEnemy : this.Modes[diff].num_ai[1],
			typeEnemy : GameData.Enemy_Image2,
			num_boxes : this.Modes[diff].num_boxes[0],
			dimensionX : 1400,
			dimensionY : 3680
		},
		{
			map : GameData.third_room.t,
			numEnemy : this.Modes[diff].num_ai[2],
			typeEnemy : GameData.Enemy_Image2,
			num_boxes : this.Modes[diff].num_boxes[0],
			dimensionX : 1219,
			dimensionY : 1763
		}
	];


	this.portals = [
		{
			X : 1140,
			Y : 420,
			S : 128,
			C : "#FF0000"
		},
		{
			X : 1150,
			Y : 450,
			S : 128,
			C : "#00FFFF"
		},
		{
			X : 90,
			Y : 65,
			S : 128,
			C : "#FF0000"
		},
		{
			X : 500,
			Y : 65,
			S : 128,
			C : "#000000"
		}
	];
	
	for(var i = 0; i < 3; i++){
		if(i == 2){
			this.Levels[i] = new Level(ctx, this.lvlBoxes[i], this.scenes[i], this.portals[i], i, this.portals[i+1]);
		}
		else{
			this.Levels[i] = new Level(ctx, this.lvlBoxes[i], this.scenes[i], this.portals[i], i);
		}
	}
	
	this.currentLevel  = 0;
	this.lastUpdate  = 0;
	this.thenRender = 0;
	this.upDateAi = 0;
	this.overLost = false;
	this.overWon = false;
	this.loaded = true;
}
GameScene.prototype.getLoaded = function()
{
	return this.loaded;
}
GameScene.prototype.update = function(e, ctx)
{

	if(this.thenRender < 10){
		this.Levels[this.currentLevel].render(ctx);
		this.thenRender = 0;
	}else{
		this.thenRender += 1;
	}
	if(this.lastUpdate < 40){
		this.Levels[this.currentLevel].Plyrupdate(e);
		this.Levels[this.currentLevel].update(e);
		this.Levels[this.currentLevel].Collisions();
		this.Levels[this.currentLevel].checkWalls(ctx);
		this.Levels[this.currentLevel].openDoors();
		this.Levels[this.currentLevel].EnemyCollisions();
		this.Levels[this.currentLevel].enemyKill();
		this.overLost = this.Levels[this.currentLevel].ifAnyofYouDotDotDot();
		this.Levels[this.currentLevel].AIUpdate();
		this.lastUpdate  = 0;
	}else{
		this.lastUpdate += 1;
	}
	if(this.Levels[this.currentLevel].portalTo() == true){
		if(this.currentLevel == 2){
			this.overWon = true;
		}
			this.currentLevel++;
	}



	// if (this.lastUpdate + 90 < Date.now())
	// {
	// 	// this.Levels[this.currentLevel].UpdateFrameData();
	// 	this.Levels[this.currentLevel].Plyrupdate(e);
	// 	this.Levels[this.currentLevel].update(e);
	// 	this.Levels[this.currentLevel].Collisions();
	// 	this.Levels[this.currentLevel].checkWalls(ctx);
	// 	this.Levels[this.currentLevel].openDoors();
	// 	this.Levels[this.currentLevel].EnemyCollisions();
	// 	this.Levels[this.currentLevel].enemyKill();
	// 	this.overLost = this.Levels[this.currentLevel].ifAnyofYouDotDotDot();
	// 	this.Levels[this.currentLevel].render(ctx);
	// 	this.Levels[this.currentLevel].AIUpdate();
	// 	this.lastUpdate = Date.now();
	// 	console.log("Update");

	// }
	// if(this.Levels[this.currentLevel].portalTo() == true){
	// 	if(this.currentLevel == 2){
	// 		this.overWon = true;
	// 	}
	// 		this.currentLevel++;
	// }
}

GameScene.prototype.getOverL = function(){
	return this.overLost;
}
GameScene.prototype.getOverW = function(){
	return this.overWon;
}