
ahk = require '..'
ahk.pollute()


every 10, (stop)->
	print "foo/bar/baz, a random number of times: #{choose("foo", "bar", "baz")}"
	if chance 1/12
		stop()

times = 1
Every 'second', (Stop)->
	Print 'print this 7x!'
	if times++ >= 7
		Stop()

Every '100ms', '3 times', ->
	Print 'bla bla bla!!!! every 100ms, 3 times'

Every '2.4s', '3 times', ->
	Print 'blablabla!!!!!!!111!11!1 every 2.4s, 3 times'

After '5 seconds', ->
	Print '(five seconds have passed)'
