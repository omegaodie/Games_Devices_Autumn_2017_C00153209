function SceneManager(ctx){
	this.gmScn = new GameScene(ctx);
	this.mnuScene = new MenuScene(ctx);
	this.gameOVER = new GameOverScene(ctx);
	this.state = "MENU";
	this.menuLoaded = false;
	this.gameLoaded = false;
	this.thing = false;
	this.settings = {"state" : this.state, "difficulty" : 0 };
}


SceneManager.prototype.update = function(e, ctx)
{
	if(this.state == "GAME")
	{
		if(this.gmScn.getLoaded() == false){
			this.gmScn.load(this.settings.difficulty);
		}
		this.gmScn.update(e, ctx);
		if(this.gmScn.getOverL() == true){
			this.state = "GAMEOVER";
		}
		if(this.gmScn.getOverW() == true){
			this.state = "GAMEOVER";
			this.thing = true;
		}
	}else if(this.state == "MENU")
	{
		if(this.menuLoaded == false){
			console.log("menuLoad");
			this.mnuScene.loadResources();
			this.menuLoaded = true;
		}
		this.settings = this.mnuScene.update(e,ctx);
		this.state = this.settings.state;
	}else if(this.state = "GAMEOVER")
	{
		this.gameOVER.loadResources();
		this.settings = this.gameOVER.update(e,ctx,this.thing);
	}
}


SceneManager.prototype.setScene = function(scene){
	this.state = scene;
}

SceneManager.prototype.getScene = function(){
	return this.state;
}