function Boss(watDo){
	this.e_SpriteSheet = new Image();
	this.e_SpriteSheet.src =  GameData.Boss_SpriteSheet.t;
	this.xPos = 200;
	this.yPos = 200;
	this.direcTionX = 0;
	this.direcTionY = 0;
	this.maxSpeed = 0.02;
	this.maxForce = 0.01;
	this.accelerationX = 0;
	this.accelerationY = 0;
	this.currentanim = "down";
	this.frameIndex = 0,
    this.tickCount = 0,
    this.ticksPerFrame = 1;
    this.numberOfFrames = 3;		
    this.width = 96;
    this.height = 48;
    this.theStrip = 1;
    this.AItimer = 0;
    this.accelerationX = 0;
	this.accelerationY = 0;
    this.amAlive = true;
	
}

Boss.prototype.drawUpdate = function(){
if(this.amAlive == true){
	this.tickCount += 1;
        // If the current frame index is in range
        if (this.frameIndex < this.numberOfFrames - 1) {  
             // Go to the next frame
            this.frameIndex += 1;
    	}else {
            this.frameIndex = 0;
    	}
	}  
        
}

Boss.prototype.draw = function(ctx){
	// console.log("Boss Code Running");
	if(this.amAlive == true){
		ctx.drawImage(
          this.e_SpriteSheet,
           this.frameIndex * this.width,
           48 * this.theStrip,
           96,
           48,
           this.xPos,
           this.yPos,
           this.width,
           this.height);

	if(this.currentanim == "left"){
			this.updatePositionImage( this.xPos, this.yPos, 1);
		}
	else if(this.currentanim == "right"){
			this.updatePositionImage(this.xPos, this.yPos, 2);
		}
	else if(this.currentanim == "up"){
			this.updatePositionImage(this.xPos, this.yPos, 3);
		}
	else{
			this.updatePositionImage( this.xPos, this.yPos, 0);
		} 
	}
}

Boss.prototype.updatePositionImage = function(x, y, id)
{
		this.theStrip = id;
		this.xPos = x;
		this.yPos = y;
}

Boss.prototype.update = function(){
	if(this.amAlive == true){
	var px =  this.direcTionX - this.xPos;
	var py =  this.direcTionY - this.yPos;
	var mPie = 3.14159;
	var mTheta = Math.atan2(-py, px);
	if (mTheta < 0){
		mTheta += 2 * mPie;
	}
	mTheta = mTheta * (180 / mPie);

		if(mTheta >= 45 && mTheta <= 135){
			this.currentanim = "up";

		}else if(mTheta >= 136 && mTheta <= 225){
			this.currentanim = "left";
			// console.log(this.currentanim);

		}else if(mTheta >= 226 && mTheta <= 315){
			this.currentanim = "down";
			// console.log(this.currentanim);

		}else{
			this.currentanim = "right";
			// console.log(this.currentanim);
		}
	}
}


Boss.prototype.stop = function(){
	if(this.currentanim == "left"){
		this.direcTionX = this.xPos + 50;
	}else if(this.currentanim == "right"){
		this.direcTionX = this.xPos - 50;
	}else if(this.currentanim == "up"){
		this.direcTionY = this.yPos + 50;
	} else{
		this.direcTionY = this.yPos - 50;
	}
}

Boss.prototype.sendPositionX = function(){
	return this.xPos;
}
Boss.prototype.sendPositionY = function(){
	return this.yPos;
}
Boss.prototype.sendDirectX = function(){
	return this.direcTionX;
}
Boss.prototype.sendDirectY = function(){
	return this.direcTionY;
}


Boss.prototype.AI = function(playerPos)
{
	var x_d = playerPos.X - this.xPos;
	var y_d = playerPos.Y - this.yPos;


	var _v = this.seek({"x" : x_d, "y" :  y_d});
	this.applyForce(_v);
	this.accelerationX *= 0.3;
	this.accelerationY *= 0.3;
	this.direcTionX += (this.accelerationX);
	this.direcTionY += (this.accelerationY);


	var _v_length = Math.sqrt((this.direcTionX * this.direcTionX) + (this.direcTionY * this.direcTionY));
	this.direcTionX /= _v_length;
	this.direcTionY /= _v_length;


	this.direcTionX *= this.maxSpeed;
	this.direcTionY *= this.maxSpeed;

	this.accelerationX = 0.0;
	this.accelerationY = 0.0;

	this.xPos += this.direcTionX;
	this.yPos += this.direcTionY;
}

Boss.prototype.destroy = function(){
	this.amAlive = false;
}


Boss.prototype.seek = function(e)
{
		var d_length;

		d_length = Math.sqrt((e.x * e.x) + (e.y  * e.y ));

		e.x / d_length;
		e.y / d_length;

		e.x *= (this.maxSpeed);
		e.y *= (this.maxSpeed);

		e.x  -= (this.direcTionX);
		e.y  -= (this.direcTionY);

		d_length = Math.sqrt((e.x * e.x) + (e.y * e.y));

		e.x /= d_length;
		e.y  /= d_length;


		e.x *= (this.maxForce);
		e.y *= (this.maxForce);

		return { "x" : e.x, "y" : e.y };
}

Boss.prototype.applyForce = function(e)
{
	this.accelerationX += (e.x);
	this.accelerationY += (e.y);

}