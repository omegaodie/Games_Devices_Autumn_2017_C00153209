function GameOverScene(currentScene){
	currentScene = "GAMEOVER";
	this.won = false;
	this.overImage = new Image();
	this.victory = new Image();
}


GameOverScene.prototype.update = function(e, ctx, Go){
	this.won = Go;
	if(e.type == 'touchstart' || e.type == 'mousedown'){
		if(e.type == 'touchstart'){
			x = e.touches[0].pageX;
			y = e.touches[0].pageY;
		}else{
			x = e.pageX;
			y = e.pageY;
		}
		location.reload();
	}
	ctx.clearRect(0,0, 1280,1080);
	ctx.clearRect(0,0, 1280,1080);
	if(this.won == true){
		 ctx.drawImage(this.victory,
         0,
          0,
           GameData.mm_GameWonImage.w,
            GameData.mm_GameWonImage.h,
             0,
              0,
               width,
                height);
	}else{
		ctx.drawImage(this.overImage,
         0,
          0,
           GameData.Over_Image.w,
            GameData.Over_Image.h,
             0,
              0,
               width,
                height);
	}
}

GameOverScene.prototype.loadResources = function () {
	this.victory.src = GameData.mm_GameWonImage.t;
	this.overImage.src = GameData.Over_Image.t;
}