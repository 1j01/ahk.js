
{pollution, keys, parseHotKey, dump} = require '../lib/pollution'
assert = require 'assert'

dump pollution

test = (str)->
	console.log "\n"
	# assert.equal str, eval(str), 'Shortcut should work "unquoted" in a polluted environment'
	console.log "Parsing #{str}..."
	console.log p1 = parseHotKey str
	console.log p2 = parseHotKey eval(str)
	assert.deepEqual p1, p2, "Shortcut should work \"unquoted\" in a polluted environment (#{str})"

test "CapsLock"
test "Ctrl+S"
test "Ctrl+Alt+A"
test "Ctrl+Shift+Alt+Enter"
test "Ctrl+Win+F3"
test "Win+Alt+Tab"
test Alt+Shift+L
test "Alt+Shift+Ctrl" # Modifier key as main key
