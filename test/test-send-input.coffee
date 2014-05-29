
ahk = require '..'

__times = 0
do __loop = ->
	ahk.send("blablabla 4x?")
	if __times++ < 4
		setTimeout __loop, 1000

_times = 0
_loop = ahk.every 1000, ->
	ahk.send "blablabla 10x??"
	if _times++ >= 10
		clearInterval _loop

ahk.pollute()

times = 0
iid = Every '1000ms', ->
	Send 'blablabla 7x!'
	if times++ >= 7
		clearInterval iid

Every '100ms', '3 times', ->
	Send 'blablabla!!!! every 100ms, 3 times'

Every '2.4s', '3 times', ->
	Send 'blablabla!!!!!!!111!11!1 every 2.4s, 3 times'
