
ahk = require '..'
ahk.pollute()

____________________________________________________ = ( N )->
	H = "__________________________"
	Print "\n(#{H}#{H}( #{ N } ))\n"


(____________________________________________________( 1 ))

Print "listening for", Ctrl+S
On Ctrl+S, ->
	Print "Save!"

(____________________________________________________( 2 ))

Print "listening for", Ctrl+Shift+Alt+Win+CapsLock
On Ctrl+Shift+Alt+Win+CapsLock, ->
	Print "!!!!!!!!!!!!!!"

(____________________________________________________( 3 ))

Print "listening ONCE for", Ctrl+S
Once Ctrl+S, ->
	Print "!!!!!!!!!!!!!!"

(____________________________________________________( 4 ))

Print "I'm gonna emit a Ctrl+S"
After 1500, =>
	Print "Wait for it..."
	After 1500, =>
		Print "Emitting Ctrl+S"
		ahk.Emit(Ctrl+S)
