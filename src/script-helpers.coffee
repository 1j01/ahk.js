
## Misc ##

exports.print = console.log


## Timing ##

# test_parse_timespan = (timespan)->
# 	console.log "parse timespan #{JSON.stringify(timespan)}"
# 	console.log "=> #{parse_timespan(timespan) (milliseconds)}"

parse_timespan = (timespan)->
	if typeof timespan is "number"
		ms = timespan
	else
		n = parseFloat timespan
		
		match = /\d\s*([a-z]+)$/i.exec(timespan)
		unit = match?[1]
		
		ms = switch unit
			when 'ms', 'milliseconds'
				n
			when 's', 'sec', 'seconds'
				n * 1000
			when 'min', 'minutes'
				n * 1000 * 60
			else
				if unit
					if unit is unit.toLowerCase()
						throw new Error "Unsupported timespan format: '#{unit}'"
					else
						throw new Error "Unsupported timespan format: '#{unit}' (unit must be lowercase)"
				else
					throw new Error "Invalid timespan format: '#{timespan}'"
	return ms

exports.after = (timespan, callback)->
	ms = parse_timespan(timespan)
	stop = -> clearTimeout(tid)
	fn = -> callback(stop)
	tid = setTimeout(fn, ms)
	return stop

exports.every = (timespan, more_args...)->
	ms = parse_timespan(timespan)
	
	switch more_args.length
		when 1
			callback = more_args[0]
			stop = -> clearInterval(iid)
			fn = -> callback(stop)
			iid = setInterval(fn, ms)
		when 2
			times_done = 0
			times = more_args[0]
			if typeof times isnt "number"
				if /^\d+\s*times$/.test(times)
					times = parseInt(times)
				else
					throw new Error "Invalid argument to every"
			
			callback = more_args[1]
			stop = -> clearInterval(iid)
			fn = ->
				if times_done >= times
					stop()
				else
					callback(stop)
					times_done += 1
			
			iid = setInterval(fn, ms)
		else
			throw new Error "Wrong number of arguments to every (too many!)"
	
	return stop


## Randomness ##

exports.random = (args...)->
	switch args.length
		when 0
			min = 0
			max = 1
		when 1
			min = 0
			max = args[0]
		when 2
			min = args[0]
			max = args[1]
		else
			throw new Error "Wrong number of arguments to random (too many!)"
	
	return (Math.random() * (max - min)) + min

exports.choose = (args...)->
	arr =
		if args.length is [[]].length
			args[0]
		else
			args
	
	return arr[Math.floor(arr.length * Math.random())]

exports.chance = (arg)->
	if typeof arg is "string"
		if arg.match /%$/
			percent = parseFloat arg
			if isNaN percent
				throw new Error "Percent value is NaN"
			chance = 100 * percent
		else
			throw new Error "String value for chance must be n%"
	else
		if 0 <= arg <= 1
			chance = arg
		else
			throw new Error "Number value for chance must be between 0 and 1, inclusive. Use a fraction like chance(1/2)"
	
	return Math.random() < chance
