
{EventEmitter} = require 'events'
{pollution, parseHotKey, casey, dump} = require './pollution'

casey class AutoHotKey extends EventEmitter
	
	constructor: ->
		@on "newListener", (event, listener)->
			return if event is "newListener" or event is "removeListener"
			# tell the addon to add a hotkey hook
			console.log "new listener for #{event}, (this should add keyboard hook)"
	
		@on "removeListener", (event, listener)->
			return if event is "newListener" or event is "removeListener"
			# tell the addon to remove a hotkey hook
			console.log "remove listener for #{event}, (this should remove keyboard hook)"

	
	pollute: (namespace = global)->
		# Pollute the global namespace (or another) with hundreds of Key Names and Functions
		
		dump pollution, namespace
		
		for k of AutoHotKey::
			do (k)=>
				global[k] = (args...)=>
					@[k](args...)
			
		# the above as a legit one-liner:
		# (global[k] = do (k)=> (args...)=> @[k](args...)) for k of AutoHotKey::
		
		# extra-legit one-liner:
		# (global[k]=do(k)=>(a...)=>@[k](a...))for k of @::
	
	click: (screen_x, screen_y)->
		# Send click in absolute screen coordinates
		screen_x = Number screen_x
		screen_y = Number screen_y
		console.log "Send global click at #{screen_x}, #{screen_y}"
	
	send: (str)->
		str = String str
		console.log "Send global input", '['+str+']'
	
	# Script Helpers
	
	print: console.log
	require: require
	
	after: (ms, cb)-> setTimeout(cb, ms)
	
	every: (args...)->
		t = parseFloat args[0]
		if typeof args[0] is "number"
			ms = t
		else
			unit = /^[\.\d]+\s*(\w*)$/.exec(args[0])?[1]
			ms = switch unit
				when 'ms', ''
					t*1
				when 's', 'sec'
					t*1000
				when 'min'
					t*1000*60
				else
					if unit
						throw new Error "Unsupported timespan format: '#{unit}'"
					else
						throw new Error "Invalid timespan format: '#{args[0]}'"
			
		cb = args[args.length-1]
		
		if args.length is 3
			
			if /^\d+\s*times$/.test(args[1])
				times = parseInt(args[1])
			else
				throw new Error "Invalid argument to ahk.every (Every)"
			
			fn = ->
				if --times < 0
					clearInterval(iid)
				else
					cb()
			
			iid = setInterval(fn, ms)
			
		else if args.length is 2
			
			setInterval(cb, ms)
			
		else
			throw new Error 'Wrong number of arguments to ahk.every (Every)'


module.exports = new AutoHotKey()
