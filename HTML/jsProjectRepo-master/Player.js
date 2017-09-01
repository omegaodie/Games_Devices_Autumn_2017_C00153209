function Player(ctx){
	this.PlayerSheet = new Image();
	this.PlayerSheet.src = GameData.player_spriteSheet.t;
	this.player_Sprite = new sprite({
    context: ctx,
    width: 32,
    height: 32,
    numberOfFrames: 3,
    ticksPerFrame: 1,
    image: this.PlayerSheet
});
	this.xPos = 250;
	this.yPos = 350;
	this.direcTionX = 0;
	this.direcTionY = 0;
	this.maxSpeed = 5;
	this.maxForce = 0.3;
	this.accelerationX = 0;
	this.accelerationY = 0;
	this.currentanim = "down";
	this.x_d;
	this.y_d;
	this.mTheta = 0;
	this.mPie = 3.14159;
}

Player.prototype.draw = function(ctx){
	if(this.currentanim == "left"){
			this.player_Sprite.updatePositionImage( this.xPos, this.yPos, 1);
	}else if(this.currentanim == "right"){
			this.player_Sprite.updatePositionImage(this.xPos, this.yPos, 2);
	}else if(this.currentanim == "up"){
			this.player_Sprite.updatePositionImage(this.xPos, this.yPos, 3);
	} else{
			this.player_Sprite.updatePositionImage( this.xPos, this.yPos, 0);
	}
	this.player_Sprite.render();
}

Player.prototype.update = function(e){
if(e.type == 'touchstart' || e.type == 'mousedown')
{
	if (e.type == 'touchstart')
	{
		this.x_d = e.touches[0].pageX - this.xPos;
		this.y_d = e.touches[0].pageY - this.yPos;
	}else
	{
		this.x_d = e.pageX - this.xPos;
		this.y_d = e.pageY - this.yPos;
	}

	var _v_p = this.seek({"x" : this.x_d, "y" :  this.y_d});
	_v_p.x *= 0.4;
	_v_p.y *= 0.4;

	this.applyForce(_v_p);


	if(this.accelerationX != 0 || this.accelerationY != 0 )
	{
			// console.log(this.accelerationX);
			// console.log(this.accelerationY);
				this.accelerationX *= 0.6;
				this.accelerationY *= 0.6;

				this.direcTionX = (this.accelerationX);
				this.direcTionY = (this.accelerationY);


				var _v_length = Math.sqrt((this.direcTionX * this.direcTionX) + (this.direcTionY * this.direcTionY));
				this.direcTionX /= _v_length;
				this.direcTionY /= _v_length;


				this.direcTionX *= this.maxSpeed;
				this.direcTionY *= this.maxSpeed;

				// console.log(this.accelerationX);
				// console.log(this.accelerationY);

				this.accelerationX = 0;
				this.accelerationY = 0;
	}

	this.mTheta = Math.atan2(-this.direcTionX, this.direcTionY);
		if (this.mTheta < 0)
		{
			this.mTheta += 2 * this.mPie;
		}
		this.mTheta = this.mTheta * (180 / this.mPie );

		if(this.mTheta >= 45 && this.mTheta <= 135){
			this.currentanim = "left";

		}else if(this.mTheta >= 136 && this.mTheta <= 225){
			this.currentanim = "up";

		}else if(this.mTheta >= 226 && this.mTheta <= 315){
			this.currentanim = "right";

		}else{
			this.currentanim = "down";
		}
	}
	// console.log(this.direcTionX);
	// console.log(this.direcTionY);
	
	this.xPos += this.direcTionX;
	this.yPos += this.direcTionY;

	this.direcTionX -= this.direcTionX / 200;
	this.direcTionY -= this.direcTionY / 200;

	
	// if(this.direcTionX  < 0.01)
	// {
	// 	this.direcTionX = 0;
	// }
	// if(this.direcTionY  < 0.01)
	// {
	// 	this.direcTionY = 0;
	// }

	// console.log(this.direcTionX);

	// console.log(this.direcTionY);

	this.player_Sprite.update();
}
Player.prototype.stop = function(){
	// if(this.currentanim == "left"){
	// 	this.direcTionX = this.xPos + 50;
	// }else if(this.currentanim == "right"){
	// 	this.direcTionX = this.xPos - 50;
	// }else if(this.currentanim == "up"){
	// 	this.direcTionY = this.yPos + 50;
	// } else{
	// 	this.direcTionY = this.yPos - 50;
	// }
	this.direcTionX = 0;
	this.direcTionY = 0;
}

Player.prototype.sendPositionX = function(){
	return this.xPos;
}
Player.prototype.sendPositionY = function(){
	return this.yPos;
}

Player.prototype.checkCollision = function (goal){
        if ((this.xPos < goal.bx + goal.bheight)&&(this.xPos + 75 > goal.bx)&&(this.yPos + 75 > goal.by)&&(this.yPos < goal.by + goal.bheight))
        {                
            this.ReturnBool = true;              
        }
}


Player.prototype.seek = function(e)
{
		var d_length;

		d_length = Math.sqrt((e.x * e.x) + (e.y  * e.y ));

		e.x / d_length;
		e.y / d_length;

		e.x *= (this.maxSpeed);
		e.y  *= (this.maxSpeed);

		e.x  -= (this.direcTionX);
		e.y   -= (this.direcTionY);

		// d_length = Math.sqrt((e.x * e.x) + (e.y * e.y));

		// e.x /= d_length;
		// e.y  /= d_length;


		// e.x *= (this.maxForce);
		// e.y *= (this.maxForce);

		return { "x" : e.x, "y" : e.y };
}


Player.prototype.applyForce = function(e)
{
	this.accelerationX += (e.x);
	this.accelerationY += (e.y);

}
