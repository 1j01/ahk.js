
{EventEmitter} = require 'events'

class AutoHotKey extends EventEmitter
	
	Pollute: (obj = global)->
		# Pollute the global namespace (or another) with hundreds of Key Names and Functions
		{pollution} = require 'pollution.coffee'
		
		for k of pollution
			global[k] = pollution[k]
	
	Click: (screen_x, screen_y)->
		console.log "Send global click at #{screen_x}, #{screen_y}"
	
	Send: (str)->
		console.log "Send global input ", str
	
	for key, val of AutoHotKey::
		# camelCase
		AutoHotKey::[key[0].toLowerCase() + key.slice(1)] = val
		# lowercase
		AutoHotKey::[key.toLowerCase()] = val

module.exports = new AutoHotKey()
