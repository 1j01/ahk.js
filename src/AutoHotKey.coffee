
{EventEmitter} = require 'events'
{pollution, parseHotKey, parseInputString, dump} = require './pollution'
{casey} = require './helpers'

casey class AutoHotKey extends EventEmitter
	
	constructor: ->
		@on "newListener", (event, listener)->
			# Ignore EventEmitter's meta listeners
			return if event in ["newListener", "removeListener"]
			
			# @TODO: tell the addon to add a hotkey hook
			console.log "new listener for #{event} (this should add a keyboard hook)"
	
		@on "removeListener", (event, listener)->
			# Ignore EventEmitter's meta listeners
			return if event in ["newListener", "removeListener"]
			
			# @TODO: tell the addon to remove a hotkey hook
			console.log "remove listener for #{event} (this should remove a keyboard hook)"
	
	
	pollute: (namespace = global)->
		# Pollute the namespace with hundreds of Key Names
		dump pollution, namespace
		
		# Pollute the namespace with AutoHotKey methods (tied to this instance)
		for k of AutoHotKey::
			do (k)=>
				global[k] = (args...)=>
					@[k](args...)
		
		@
	
	
	# Include Script Helpers
	
	AutoHotKey::[k] = v for k, v of require './script-helpers'
	
	
	# Methods that act globally
	
	click: (screen_x, screen_y)->
		# Send click in absolute screen coordinates
		screen_x = Number screen_x
		screen_y = Number screen_y
		console.log "Send global click at #{screen_x}, #{screen_y}"
		@
	
	send: (str)->
		#console.log "Send: #{str}"
		str = String str
		console.log parseInputString(str).toString()
		@
	
	


module.exports = new AutoHotKey()
