function Item(posX, posY){
	this.itemImage = new Image();
	this.itemImage.src = GameData.Item_Image1.t
	this.currentmove = 'none';
	this.xPos = posX;
	this.yPos = posY;
	this.MoveToX;
	this.MoveToY;
	this.amAlive = true;
}
Item.prototype.render = function(ctx){
	if(this.amAlive == true){
		ctx.drawImage(this.itemImage,this.xPos,this.yPos);
	}
	
}
Item.prototype.setMove = function(MoToX, MoToY){
	this.MoveToX = MoToX;
	this.MoveToY = MoToY;
}
Item.prototype.setDirect = function(direction){
	this.currentmove = direction;
}
Item.prototype.Stop = function(){
	this.currentmove = 'none';
	this.MoveToX = this.xPos;
	this.MoveToY = this.yPos;
}
Item.prototype.update = function(){	
	if(this.currentmove == "left"){
		if(this.xPos + 128 > this.MoveToX ){
			this.xPos -= 1.2;
		}else{
		this.currentmove = 'none';
	}
	}else if(this.currentmove == "right"){
		if(this.xPos + 128 < this.MoveToX){
			this.xPos += 1.2;
		}else{
		this.currentmove = 'none';
	}	
	}else if(this.currentmove == "up"){
		if(this.yPos + 128 > this.MoveToY){
			this.yPos -= 1.2;
		}	
	} else if(this.currentmove == "down"){
		if(this.yPos + 128 < this.MoveToY){
			this.yPos += 1.2;
		}else{
		this.currentmove = 'none';
		}	
	}else{

	}
	
}
Item.prototype.sendPositionX = function(){
	return this.xPos;
}
Item.prototype.sendPositionY = function(){
	return this.yPos;
}
Item.prototype.sendMove = function(){
	return this.currentmove;
}

Item.prototype.destroy = function(){
	this.amAlive = false;
}