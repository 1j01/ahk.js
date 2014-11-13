
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
			when 'ms'
				n*1
			when 's', 'sec'
				n*1000
			when 'min'
				n*1000*60
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
			throw new Error "Wrong number of arguments to Every (too many!)"
	
	return stop

exports.print = console.log
