
ahk = require '..'

__times = 1
do __loop = ->
	ahk.send("blablabla 4x?")
	if __times++ < 4
		setTimeout __loop, 1000

_times = 1
ahk.every 1000, (stop)->
	ahk.send "blablabla 10x??"
	if _times++ >= 10
		stop()

ahk.pollute()

times = 1
Every '1000ms', (Stop)->
	Send 'blablabla 7x!'
	if times++ >= 7
		Stop()

Every '100ms', '3 times', ->
	Send 'blablabla!!!! every 100ms, 3 times'

Every '2.4s', '3 times', ->
	Send 'blablabla!!!!!!!111!11!1 every 2.4s, 3 times'

After '5s', ->
	Send '(five seconds have passed)'
