function sprite (options) {
    var that = options;
    that.theStrip = 0;
	  that.xPos = 0;
	  that.yPos = 0;
    that.tickCount = 0;

    that.render = function () {
        // Clear the canvas
        //that.context.clearRect(that.xPos, that.yPos, that.width / that.numberOfFrames, that.height);
        // Draw the animation
        that.context.drawImage(
           that.image,
           that.frameIndex * that.width,
           32 * that.theStrip,
           32,
           32,
           that.xPos,
           that.yPos,
           that.width,
           that.height);
    };
    

    that.update = function () {
        
        that.tickCount += 1;
        // If the current frame index is in range
        if (that.frameIndex < that.numberOfFrames - 1) {  
             // Go to the next frame
            that.frameIndex += 1;
          } else {
                that.frameIndex = 0;
          }
    }; 
	
	
	that.updatePositionImage = function(x, y, id){
		that.theStrip = id;
		that.xPos = x;
		that.yPos = y;
	}

    return that;
}