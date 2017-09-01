function Enemy(watDo){
	this.e_SpriteSheet = new Image();
	this.e_SpriteSheet.src = GameData.Enemy_Image1.t;
	this.xPos = watDo.X;
	this.yPos = watDo.Y;
	this.direcTionX = 0;
	this.direcTionY = 0;
	this.maxSpeed = 2;
	this.maxForce = 0.5;
	this.accelerationX = 0;
	this.accelerationY = 0;
	this.currentanim = "down";
	this.frameIndex = 0,
    this.tickCount = 0,
    this.ticksPerFrame = 1;
    this.numberOfFrames = 3;		
    this.width = 32;
    this.height = 32;
    this.theStrip = 1;
    this.AItimer = 0;
    this.amAlive = true;
    this.keepInGameTimer = 0;
	
}

Enemy.prototype.drawUpdate = function(){
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

Enemy.prototype.draw = function(ctx){
	if(this.amAlive == true){
		ctx.drawImage(
          this.e_SpriteSheet,
           this.frameIndex * this.width,
           32 * this.theStrip,
           32,
           32,
           this.xPos,
           this.yPos,
           this.width,
           this.height);

	if(this.currentanim == "left"){
			updatePositionImage( this.xPos, this.yPos, 1);
	}else if(this.currentanim == "right"){
			updatePositionImage(this.xPos, this.yPos, 2);
	}else if(this.currentanim == "up"){
			updatePositionImage(this.xPos, this.yPos, 3);
	} else{
			updatePositionImage( this.xPos, this.yPos, 0);
		}
	}  

function updatePositionImage(x, y, id){
		this.theStrip = id;
		this.xPos = x;
		this.yPos = y;
	}
}

Enemy.prototype.update = function(){
	if(this.amAlive == true)
	{
		var mPie = 3.14159;
		var mTheta = Math.atan2(-this.direcTionY, this.direcTionX);
		if (mTheta < 0)
		{
			mTheta += 2 * mPie;
		}
		mTheta = mTheta * (180 / mPie);

		if(mTheta >= 45 && mTheta <= 135){
			this.currentanim = "up";

		}else if(mTheta >= 136 && mTheta <= 225){
			this.currentanim = "left";

		}else if(mTheta >= 226 && mTheta <= 315){
			this.currentanim = "down";

		}else{
			this.currentanim = "right";
		}
		this.xPos += this.direcTionX;
		this.yPos += this.direcTionY;
		if(this.keepInGameTimer > 0)
		{
			this.keepInGameTimer -= 1;
		}
	}
}


Enemy.prototype.stop = function(){
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

Enemy.prototype.sendPositionX = function(){
	return this.xPos;
}
Enemy.prototype.sendPositionY = function(){
	return this.yPos;
}
Enemy.prototype.sendDirectX = function(){
	return this.direcTionX;
}
Enemy.prototype.sendDirectY = function(){
	return this.direcTionY;
}

Enemy.prototype.Disperse = function(x,y){
	this.xPos = x;
	this.yPos = y;
}


Enemy.prototype.destroy = function(e){
	this.amAlive = false;
}

Enemy.prototype.seek = function(e)
{
		var d_length;

		d_length = Math.sqrt((e.x * e.x) + (e.y  * e.y ));

		e.x /= d_length;
		e.y /= d_length;

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


Enemy.prototype.applyForce = function(e)
{
	this.accelerationX += (e.x);
	this.accelerationY += (e.y);

}

Enemy.prototype.keepInGame = function(e)
{
	if(this.xPos < 0){
		this.xPos = width;
	}
	if(this.xPos > width){
		this.xPos = 0;
	}
	if(this.yPos < 0){
		this.yPos = height;
	}
	if(this.yPos > height){
		this.yPos = 0;
	}
}


Enemy.prototype.AIalt = function(e, thisI)
{
		var _v_S = {"x" : 0, "y" :  0};
		var _v_A = {"x" : 0, "y" :  0};
		var _v_C = {"x" : 0, "y" :  0};


		var x_d = e.X - this.xPos;
		var y_d = e.Y - this.yPos;

		var _v_p = this.seek({"x" : x_d, "y" :  y_d});

		var playerDist = Math.sqrt((x_d * x_d) + (y_d * y_d));
		if(playerDist > 25)
		{
			x_d = e.bossX - this.xPos;
			y_d = e.bossY - this.yPos;

			var _v_b = this.seek({"x" : x_d, "y" :  y_d});


					// if(d_length > 0)
			// {
			// 	_v_p.x /=  Math.sqrt(d_length);
			// 	_v_p.y /=  Math.sqrt(d_length);
			// }


			x_d = (width / 2) - this.xPos;
			y_d = (height / 2) - this.yPos;
			var _v_cntr = this.seek({"x" : x_d, "y" :  y_d});

			var steerX = 0;
			var steerY = 0;
			var count = 0;
			for (var i = 0; i < e.numAI; i++)
			{
				if(i != thisI)
				{
					// Calculate distance from current boid to boid we're looking at
					x_d = this.xPos - e.AIpos[i].x;
					y_d = this.yPos - e.AIpos[i].y;


					d_length = Math.sqrt((x_d * x_d) + (y_d * y_d));
					if(d_length < 1){
					 	d_length = 1;
					}
					if (d_length < 150)
					{

						steerX += (x_d / d_length) / d_length;
						steerY += (x_d / d_length) / d_length;
						count++;
					}
				}
			}
			if(count > 0)
			{
				steerX /= count;
				steerY /= count;
				_v_S = 	this.seek({"x" : steerX, "y" :  steerY});
			}
			
			steerX = 0;
			steerY = 0;
			count = 0;
			for (var i = 0; i < e.numAI; i++)
			{
				if(i != thisI)
				{
					x_d = this.xPos - e.AIpos[i].x;
					y_d = this.yPos - e.AIpos[i].y;


					d_length = Math.sqrt((x_d * x_d) + (y_d * y_d));
					if(d_length < 350)
					{
						steerX += e.AIdir[i].x;
						steerY += e.AIdir[i].y;
						count++;
					}
				}
			}
			if(count > 0)
			{
				var  mag =  Math.sqrt((steerX * steerX) + (steerY * steerY));
				if(mag > 0)
				{
					steerX /= count;
					steerY /= count;
					_v_A = 	this.seek({"x" : steerX, "y" :  steerY});
				}
			}


			steerX = 0;
			steerY = 0;
			count = 0;
			for (var i = 0; i < e.numAI; i++)
			{
				if(i != thisI)
				{
					x_d = this.xPos - e.AIpos[i].x;
					y_d = this.yPos - e.AIpos[i].y;


					d_length = Math.sqrt((x_d * x_d) + (y_d * y_d));
					if(d_length < 350)
					{
						steerX += e.AIpos[i].x;
						steerY += e.AIpos[i].y;
						count++;
					}
				}
			}
			if(count > 0)
			{
				steerX /= count;
				steerY /= count;
				_v_C = 	this.seek({"x" : steerX, "y" :  steerY});
			}


			_v_p.x *= 1.2;
			_v_p.y *= 1.2;

			_v_b.x *= 1.5;
			_v_b.y *= 1.5;

			_v_cntr.x *= 0.5;
			_v_cntr.y *= 0.5;

			_v_S.x *= 1.75;
			_v_S.y *= 1.75;

			// _v_A.x *= 0.155;
			// _v_A.y *= 0.155;

			// _v_C.x *= 0.155;
			// _v_C.y *= 0.155;


			this.applyForce(_v_cntr);
		// 	this.applyForce(_v_b);
		// 	// this.applyForce(_v_p);
		 	this.applyForce(_v_S);
		 	this.applyForce(_v_A);
		 	this.applyForce(_v_C);
		}else
		{
			this.applyForce(_v_p);
		}

		if(this.accelerationX != 0 || this.accelerationY != 0 )
		{
			// console.log(this.accelerationX);
			// console.log(this.accelerationY);
				this.accelerationX *= 0.6;
				this.accelerationY *= 0.6;

				this.direcTionX += (this.accelerationX);
				this.direcTionY += (this.accelerationY);


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
}
