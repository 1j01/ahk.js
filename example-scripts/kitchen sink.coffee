
ahk = require 'ahk' # AutoHotKey
$ = require 'ahq' # AutoHotQuery

# Pollute the global namespace with hundreds of key names and functions
ahk.pollute()


$(/Kongregate - Google Chrome/).each (win)->
	win.minimize()
	win.focus()
	win.maximize()
	win.setStyle(idk)
	{x, y} = win.position()
	win.position(x, y)
	{w, h} = win.size()
	win.size(w, h)
	win.click(x, y)
	win.hide()
	win.close()

$(/Skype/).each (s)->
	s.kill()



ClickRandomly = ->
	# The global click function clicks in absolute screen coordinates
	Click Random(ScreenWidth), Random(ScreenHeight)
	# The above is equivalent to using methods and properties of the screen
	Screen.Click Random(Screen.Width), Random(Screen.Height)
	# Maybe

Every "0.5s", ClickRandomly


# Hotkeys

ahk.on 'Ctrl+Shift+B', ->
	ahk.send "Blub blub blub...."
# or
ahk.hotkey 'Ctrl+Shift+Enter', ->
	ahk.send "lib lub loblab libibl\n"

# or....

On Ctrl+Shift+B, ->
	Send "Blub blub blub...."
# or
HotKey Ctrl+Shift+Enter, ->
	Send "lib lub loblab libibl\n"
