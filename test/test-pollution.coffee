
{pollution, keys} = require '../lib/pollution'

for k of pollution
	global[k] = pollution[k]

parse = (str)->
	modifiers = []
	key = str.replace /(Ctrl|Shift|Alt|Win)\+/g, (match)->
		modifier = match.slice(0, -1) # chop off the +
		modifiers.push modifier
		""
	keycode = keys[key] ? parseInt(key)
	
	{key, keycode, modifiers}

test = (str)->
	# test to see if this shortcut works unquoted in a polluted environment
	console.log "\n"
	console.log "Parsing #{str}..."
	console.log parse str
	console.log "Parsing #{eval(str)}..."
	console.log parse eval(str)

test "Ctrl+Alt+A"
test "Ctrl+Shift+Alt+Enter"
test "Ctrl+Win+F3"
