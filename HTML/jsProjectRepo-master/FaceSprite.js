function FaceSprite (options) 
{
  var that = options;
  that.name = options.name;
  that.loop = options.loop;
  that.animDir = false;
  that.img = options.img;
  that.plist = options.plist;
  that.frameIndex = 0;
  that.xPos = options.X;
  that.yPos = options.Y;
  that.numberOfFrames = options.numFrames;
  that.tickCount = 0;
  that.done = false;
  that.ticksPerFrame = options.ticksper;

    that.render = function (ctx) 
    {

        ctx.drawImage( 
          that.img, 
          that.plist[that.frameIndex].frame.x,
           that.plist[that.frameIndex].frame.y, 
           that.plist[that.frameIndex].frame.w, 
          that.plist[that.frameIndex].frame.h,
           that.xPos* scale_factor_x,
            that.yPos* scale_factor_y,
             that.plist[that.frameIndex].frame.w * scale_factor_x,
              that.plist[that.frameIndex].frame.h * scale_factor_y);
    };

    that.getdone = function(){
      return that.done;
    }; 
    that.setdone = function(d){
      that.done = d;
    };    

    that.update = function () {
        
        that.tickCount += 1;
        // If the current frame index is in range
        if(that.tickCount >=  that.ticksPerFrame)
        {
         
          if(that.loop === true)
          {
            if(that.animDir === false)
            {
                    if (that.frameIndex < that.numberOfFrames - 1) 
                    {  
                     // Go to the next frame
                        that.frameIndex += 1;
                     }
                      else 
                     {
                        that.animDir = true;
                    }
                  
            }
            else
            {
                    if (that.frameIndex > 0) 
                    {  
                     // Go to the next frame
                        that.frameIndex -= 1;
                     }
                      else 
                     {
                        that.animDir = false;
                        that.done = true;
                    }
            }
          }
          else
          {
            if (that.frameIndex < that.numberOfFrames - 1) 
            {  
             // Go to the next frame
                that.frameIndex += 1;
             }
              else 
             {
                that.frameIndex = 0;
              }
          
          }
          that.tickCount = 0;
        }
    }; 
	
	
	that.updatePositionImage = function(x, y, id){
		that.theStrip = id;
		that.xPos = x;
		that.yPos = y;
	}

    return that;
}