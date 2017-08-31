function GameClient(){
	var ws = new WebSocket("ws://localhost:8081/test");
	//var ws = new WebSocket("ws://"+window.location.hostname+":8081/test");
	ws.onopen = function() {
   
	//once a connection is opened, send a request to join the game.
	join();

	};
	ws.onmessage = function (evt) {
	console.log(evt.data);
	};

	//send join message
	function join()
	{
		var message={};
		message.type="join";
		message = JSON.stringify(message);
		ws.send(message);
	}

	function updateState(e)
	{
		var touchPoint={};
		touchPoint.x = e.clientX;
		touchPoint.y = e.clientY;

		var message={};
		message.type="updateState";
		message.data = touchPoint;
		message = JSON.stringify(message);
		ws.send(message);	
	}

	document.addEventListener("click", updateState);
}