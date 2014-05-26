
{findWindow, findWindows} = ahk = require 'ahk'

findWindow title: /...Kongregate - Google Chrome/, (win)->
	win.focus()
	win.maximize()
	win.setStyle(idk)
	win.move(x, y, [w, h])
	win.click(x, y)

findWindows title: /.* - Google Chrome/, (win)->
	win.hide()
	win.close()

findWindow /Sublime Text/, (s)->
	s.kill()


# The "global" ahk.click clicks in absolute screen coordinates

rand = ()
clickRandomly = ->
	ahk.click rand(ahk.screenWidth), rand(ahk.screenHeight)

setInterval clickRandomly, 500


# Hotkeys

ahk.on 'Ctrl+Shift+B', ->
	ahk.send("Blub blub blub....")
# or
ahk.hotkey 'Ctrl+Shift+Enter', ->
	ahk.send("lib lub loblab libibl\n")
# or....

# Pollute the global namespace with hundreds of Key Names and Functions
ahk.pollute()

On Ctrl+Shift+B, ->
	Send("Blub blub blub....")
# or
HotKey Ctrl+Shift+Enter, ->
	Send("lib lub loblab libibl\n")
# or
HotKey [Ctrl+Shift+Enter], ->
	Send("lib lub loblab libibl\n")
# or
On [Ctrl+Shift+Enter], ->
	Send("lib lub loblab libibl\n")
