
{findWindow, findWindows} = ahk = require 'ahk'

findWindow title: /...Kongregate - Google Chrome/, (win)->
	win.minimize()
	win.focus()
	win.maximize()
	win.setStyle(idk)
	{x, y, w, h} = win.position()
	win.position(x, y, [w, h])
	{w, h} = win.size()
	win.size(w, h)
	win.click(x, y)
	win.hide()
	win.close()

findWindow /Skype/, (s)->
	s.kill()


# The "global" ahk.click clicks in absolute screen coordinates

rand = (x)-> Math.random() * x
clickRandomly = ->
	ahk.click rand(ahk.screenWidth), rand(ahk.screenHeight)

ahk.every "0.5s", clickRandomly


# Hotkeys

ahk.on 'Ctrl+Shift+B', ->
	ahk.send "Blub blub blub...."
# or
ahk.hotkey 'Ctrl+Shift+Enter', ->
	ahk.send "lib lub loblab libibl\n"

# or....

# Pollute the global namespace with hundreds of Key Names and Functions
ahk.pollute()

On Ctrl+Shift+B, ->
	Send "Blub blub blub...."
# or
HotKey Ctrl+Shift+Enter, ->
	Send "lib lub loblab libibl\n"
