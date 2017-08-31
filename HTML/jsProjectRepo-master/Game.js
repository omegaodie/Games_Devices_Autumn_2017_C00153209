var game, cv, lvlLoader, scale_factor_x, scale_factor_y, width, height;
function Game(canvas){
	ctx = canvas.getContext('2d');
	
	this.scnManager = new SceneManager(ctx);
	this.currentScene = "MENU";
	this.scnManager.getScene(this.currentScene);
	window.addEventListener("touchstart", this.gameLoop);
	window.addEventListener("keypress", this.gameLoop);
	window.addEventListener ("mousedown", this.gameLoop);
	canvas.onmousewheel = function(event){
		event.preventDefault();
	};

}

Game.prototype.gameLoop = function(e){
	game.scnManager.update(e, ctx);
    window.setTimeout(window.requestAnimationFrame(game.gameLoop), 1000 / 30);
}


function main()
{
	loaded = false;
	cv = document.getElementById('myCanvas');
	var w = window,
    d = document,
    e = d.documentElement,
    g = d.getElementsByTagName('body')[0],
    x = w.innerWidth || e.clientWidth || g.clientWidth,
    y = w.innerHeight|| e.clientHeight|| g.clientHeight;
	
	setCanvas(x,y);
	ctx = cv.getContext('2d');
	lvlLoader = new levelLoader();
	checkFlag();
};
 

function checkFlag() 
{
    if(loaded == false) 
    {
       window.setTimeout(checkFlag, 100); /* this checks the flag every 100 milliseconds*/
    } 
    else
    {
     	game = new Game(cv); 
		window.requestAnimationFrame(game.gameLoop);
    }
}

function setCanvas(x, y) 
{
    if(x >= 1900) 
    {
	    scale_factor_x = 1900 / 1532;
	    scale_factor_y = 1200 / 721; 
	    document.getElementById('myCanvas').width = 1900;
	    width = 1900;
	    height = 1200;
	    document.getElementById('myCanvas').height = 1200;
	    document.getElementById('myCanvas').style.position = "absolute";
        var vp = document.createElement('style');
        vp.name = "myStyle";
        vp.content = "style='pointer-events: none;'";
        document.getElementsByTagName('head')[0].appendChild( vp );

    } 
    else if(x >= 1280) 
    {
    	scale_factor_x = 1280 / 1532;
    	scale_factor_y = 800 / 721; 
    	width = 1280;
	    height = 800;
    	document.getElementById('myCanvas').width = 1280;
    	document.getElementById('myCanvas').height = 800;
        document.getElementById('myCanvas').style.position = "absolute";
        var vp = document.createElement('style');
        vp.name = "myStyle";
        vp.content = "style='pointer-events: none;'";
        document.getElementsByTagName('head')[0].appendChild( vp );
    }
    else 
    {
    	scale_factor_x = 800 / 1532;
    	scale_factor_y = 480 / 721; 
    	width = 800;
	    height = 480;
    	document.getElementById('myCanvas').width = 800;
    	document.getElementById('myCanvas').height = 480;
        document.getElementById('myCanvas').style.position = "absolute";
        var vp = document.createElement('style');
        vp.name = "myStyle";
        vp.content = "style='pointer-events: none;'";
        document.getElementsByTagName('head')[0].appendChild( vp );
    }
}