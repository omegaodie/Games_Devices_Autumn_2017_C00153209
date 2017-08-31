function MenuScene(currentScene){
	currentScene = "MENU";
	this.menu_atlas = new Image();
	this.Buttons = [];
	this.buttonPos = [];
	this.buttonsize = [128, 32];
	this.back_plist = new Object();
	this.face_plists = [[],[],[],[],[],[],[]];
	this.current_face = 0;
	this.difficulty = 0;
	this.faces = [[],[],[],[],[],[],[]];
	//1532  721
}


MenuScene.prototype.draw_static_simple = function(pos, src, size, ctx)
{

   ctx.drawImage(src, 0, 0, size[0], size[1], pos[0], pos[1], size[0] * scale_factor_x, size[1] * scale_factor_y);
}

MenuScene.prototype.update = function(e, ctx)
{
	var returnState = "MENU";
	//console.log(this.back_plist.frames[0]);
	this.draw_static(this.back_plist.frames[0],  [ 0 , 0], this.menu_atlas.src, ctx);
	for(var i = 0 ; i < 3; i++)
	{
		this.draw_static_simple(this.buttonPos[i], this.Buttons[i], this.buttonsize, ctx);
	}
	//console.log(t);
	if(this.faces[this.current_face].getdone()  == true)
	{
		this.faces[this.current_face].setdone(true);
		this.start_anim(ctx);
	}


	this.faces[this.current_face].update();
	this.faces[this.current_face].render(ctx);


	if(e.type == 'touchstart' || e.type == 'mousedown')
	{
			var x, y;
			if (e.type == 'touchstart')
			{
				x = e.touches[0].pageX;
				y = e.touches[0].pageY;
			}else{
				x = e.pageX;
				y = e.pageY;
			}

			

			if( x  >= 280  && x <= (280 + 128) )
			{
				for(var i = 0 ; i < 5; i++)
				{
					if( (y  >= (160 + (i * 100)) ) && y <= (((160 + (i * 100)) + 32) ))
					{
						if( i === 0)
						{
							returnState = "GAME";
						}
						else if(i === 1)
						{
							this.difficulty = 0;
						}
						else if(i === 2)
						{
							this.difficulty = 1;
						}
					}
				}
			}
	}
	return {"state" : returnState, "difficulty" : this.difficulty};;
}

MenuScene.prototype.loadResources = function () 
{
	this.menu_atlas.src = GameData.GeneralMenu.src_img + ".png";
	this.back_plist = Plists;
	for(var i = 0; i < 7; i++)
	{
		for(var j = 0; j < 7; j++)
		{
			this.face_plists[i][j] = Plists.frames[(7 * i) + j + 1];
		}
	}

	for(var i = 0 ; i < 3; i++)
	{
		var  b = new Image();
		b.src = GameData.MainMenu[i];
		this.Buttons.push(b);
		this.buttonPos.push([280, 160 + (i * 100)]);
	}
	for(var i = 0; i < 7; i++){
		this.faces[i] = FaceSprite(
		{ 
			name : "f" + (i + 1) +"_", 
			img : this.menu_atlas, 
			plist : this.face_plists[i],
			loop : true,
			numFrames : 7, 
			ticksper : 120, 
			X: GameData.GeneralMenu.face_pos[i].x * scale_factor_x, 
			Y : GameData.GeneralMenu.face_pos[i].y * scale_factor_y
		});
	}
}

MenuScene.prototype.start_anim = function(ctx)
{
	var t = Math.floor((Math.random() * 7) + 0);
	this.current_face = t;
}



MenuScene.prototype.draw_static = function(e, src, srcImage, ctx)
{
    var img = new Image();
    img.src = srcImage;
        ctx.drawImage(img,
         e.frame.x,
          e.frame.y,
           e.frame.w,
            e.frame.h,
             src[0],
              src[1],
               width,
                height);
}