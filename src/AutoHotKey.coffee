
{EventEmitter} = require 'events'
{pollution, parseHotKey, parseInputString, casey, dump} = require './pollution'
{parse_timespan} = require './helpers'

casey class AutoHotKey extends EventEmitter
	
	constructor: ->
		@on "newListener", (event, listener)->
			# Ignore EventEmitter's meta listeners
			return if event in ["newListener", "removeListener"]
			
			# @TODO: tell the addon to add a hotkey hook
			console.log "new listener for #{event}, (this should add keyboard hook)"
	
		@on "removeListener", (event, listener)->
			# Ignore EventEmitter's meta listeners
			return if event in ["newListener", "removeListener"]
			
			# @TODO: tell the addon to remove a hotkey hook
			console.log "remove listener for #{event}, (this should remove keyboard hook)"

	
	pollute: (namespace = global)->
		# Pollute the namespace with hundreds of Key Names
		dump pollution, namespace
		
		# Pollute the namespace with AutoHotKey methods (tied to this instance)
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
		console.log "Send: #{str}"
		#str = String str
		#console.log parseInputString(str).toString()
	
	# Script Helpers
	
	print: console.log
	#require: require # this doesn't work, it just breaks require
	
	after: (timespan, callback)->
		ms = parse_timespan(timespan)
		stop = -> clearTimeout(tid)
		fn = -> callback(stop)
		tid = setTimeout(fn, ms)
		return stop
	
	every: (timespan, more_args...)->
		ms = parse_timespan(timespan)
		
		switch more_args.length
			when 1
				callback = more_args[0]
				stop = -> clearInterval(iid)
				fn = -> callback(stop)
				iid = setInterval(fn, ms)
			when 2
				times = more_args[0]
				if typeof times isnt "number"
					if /^\d+\s*times$/.test(more_args[0])
						times = parseInt(more_args[0])
					else
						throw new Error "Invalid argument to Every"
				
				callback = more_args[1]
				stop = -> clearInterval(iid)
				fn = ->
					if --times < 0
						stop()
					else
						callback(stop)
				
				iid = setInterval(fn, ms)
			else
				throw new Error "Wrong number of arguments to Every"
		
		return stop


module.exports = new AutoHotKey()
