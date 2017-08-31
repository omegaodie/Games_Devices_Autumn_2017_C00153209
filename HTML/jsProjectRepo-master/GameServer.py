import tornado
from tornado import websocket, web, ioloop, httpserver
#To print stack trace to find errors
import traceback
import json

#A dictionary, keys = ip address, value = websocket associated with the ip
#(techincally the websockethandler associated with the ip, but it's easier)
#to imagine as just the websocket.
connections={}

#States
WAITING_FOR_PLAYERS=0
STARTING_GAME=1
gameState=WAITING_FOR_PLAYERS

class WSHandler(tornado.websocket.WebSocketHandler):

	def check_origin(self, origin):
		return True
		
	def open(self):
		print ("WebSocket opened")
		print('Client IP:' + self.request.remote_ip)
		#To check what type this is...
		#print(type(self))
			
		  
	def on_message(self, message):
		print ('message received %s' % message)
		messageHandler.handleIncomingMsg(message,self)
		#self.sendToAllButPlayer(self.request.remote_ip, message)
			
 
	def on_close(self):
	    print ("WebSocket closed")

	def sendToAll(self, message):
		#key is ip and value is the websockethandler
		for key, value in connections.items():
			value.write_message(message)

	def sendToAllButPlayer(self, player_ip, message):
		for key, value in connections.items():
			if(key != player_ip):
				value.write_message(message)


class MessageHandler:
	def __init__(self):
		pass

	def handleIncomingMsg(self, data, socket):
		type=""
		#first, turn the json message into a dict
		try:
			#print ('message received %s' %data)
			
			#converts the unicode data that arrives into a dict
			#data = ast.literal_eval(data)
			data = json.loads(data)
			print(data)

			type = data['type']

		except :
			tb = traceback.format_exc()
			print(tb)
			print ("Unexpected error:" +  str(tb))
			
					

		if type == "join":									
			#reply with a message
			success = self.addPlayer(data, socket)
						
			if success:
				self.sendMessage(socket, "gameState", gameState )
			else:
				self.sendMessage(socket, "error", "No available space: Two players already in the game!")  
		   
		elif type == "updateState":
			self.update_state(socket,data)
		else:
			msg = 'Error reading game request. Please make sure message type is either join, updateState, or...'
			message={'type':'error', "data":msg}
			print ('Error reading game request.')
	
	
	def update_state(self,socket, data):
		socket.sendToAllButPlayer(socket.request.remote_ip,data)

	def addPlayer(self, data, socket):
		
		#needed to change the value of gameState
		global gameState

		result = True;
		#first check is there room
		if len(connections)<2:
			#add to connection list
			#add the new player to the list of connections
			connections[socket.request.remote_ip] = socket
			print("Number of connections "+ str(len(connections)))

			for key, value in connections.items():
				print(key)

			#if there are now 2 players
			if(len(connections) == 2):
				gameState=STARTING_GAME
						
		elif(len(connections) >= 2):			
			result = False;
		
		return result;
		

	#add in types 
	def sendMessage(self,socket,type,data):
		try:
			msg=dict()
			msg["type"]=type;
			msg["data"]=data;
			msg=json.dumps(msg)
			socket.write_message(msg)
		except KeyError:
			print("Player " + str(pid) + " isn't connected")
	

#needs to be after the class def
messageHandler = MessageHandler();


app= tornado.web.Application([
	#map the handler to the URI named "test"
	(r'/test', WSHandler),
])
 
if __name__ == '__main__':
	app.listen(8081)
	tornado.ioloop.IOLoop.instance().start()