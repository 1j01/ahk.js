
modifiers = ["Ctrl", "Shift", "Alt", "Win"]

keys =
	Backspace: 8
	Tab: 9
	Enter: 13
	
	Shift: 16
	Ctrl: 17
	Alt: 18
	
	"Pause/Break": 19
	PauseBreak: 19
	Pause: 19
	Break: 19
	
	"Caps Lock": 20
	CapsLock: 20
	Caps: 20
	
	Esc: 27
	Escape: 27
	
	Space: 32
	SpaceBar: 32
	
	"Page Up": 33
	"Page Down": 34
	PageUp: 33
	PageDown: 34
	
	End: 35
	Home: 36
	
	Left: 37
	Up: 38
	Right: 39
	Down: 40
	
	Insert: 45
	Delete: 46
	
	Windows: 91
	Win: 91
	"Left Windows": 91
	LeftWindows: 91
	LWindows: 91
	LeftWin: 91
	LWin: 91
	"Right Windows": 92
	RightWindows: 92
	RWindows: 92
	RightWin: 92
	RWin: 92
	
	"Context Menu": 93
	ContextMenu: 93
	"Select Key": 93
	SelectKey: 93
	"Right Click": 93
	RightClick: 93
	
	"Numpad 0": 96
	Numpad0: 96
	"Numpad 1": 97
	Numpad1: 97
	"Numpad 2": 98
	Numpad2: 98
	NumpadDown: 98
	"Numpad 3": 99
	Numpad3: 99
	"Numpad 4": 100
	Numpad4: 100
	NumpadLeft: 100
	"Numpad 5": 101
	Numpad5: 101
	"Numpad 6": 102
	Numpad6: 102
	NumpadRight: 102
	"Numpad 7": 103
	Numpad7: 103
	"Numpad 8": 104
	Numpad8: 104
	NumpadUp: 104
	"Numpad 9": 105
	Numpad9: 105
	"Numpad *": 106
	NumpadMultiply: 106
	NumpadTimes: 106
	"Numpad +": 107
	NumpadAdd: 107
	NumpadPlus: 107
	"Numpad -": 109
	NumpadSubtract: 109
	NumpadMinus: 109
	"Numpad .": 110
	NumpadDecimal: 110
	NumpadDot: 110
	NumpadPeriod: 110
	NumpadFullStop: 110
	"Numpad /": 111
	NumpadDivide: 111
	NumpadDiv: 106
	NumpadSlash: 111
	
	"Num Lock": 144
	NumLock: 144
	"Scroll Lock": 145
	ScrollLock: 145
	"My Computer": 182
	MyComputer: 182
	"My Calculator": 183
	MyCalculator: 183
	
	";": 186
	"=": 187
	",": 188
	"-": 189
	".": 190
	"/": 191
	"`": 192
	"[": 219
	"\\": 220
	"]": 221
	"'": 222

for c in ['A'..'Z']
	keys[c] = c.charCodeAt(0)

for n in [1..12]
	keys["F"+n] = 111 + n

for n in [0..9]
	keys[n] = 48 + n



pollution = {}
for m in modifiers
	pollution[m] = m + "+"

for k of keys
	pollution[k] ?= keys[k]
	#pollution[k] ?= k



module.exports = {pollution, keys, modifiers}
