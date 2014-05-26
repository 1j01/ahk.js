
ahk = require 'ahk'

hidden = []

ahk.on "Ctrl+Shift+Win+H", ->
	window_to_hide = ahk.activeWindow
	if window_to_hide
		hidden_window = window_to_hide.hide()
		hidden.push(hidden_window)

ahk.on "Ctrl+Win+H", ->
	hidden.pop()?.show()

# if tray functionality is a thing
ahk.tray ->
	hidden.map (win)->
		name: win.getName()
		click: ->
			win.show()
			hidden.splice(hidden.indexOf(win))
