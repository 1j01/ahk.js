
exports.casey = (c)->
	# Make a class somewhat loosely cased
	# The class's properties should be lowerCamelCased
	for key, val of c::
		# UpperCamelCase
		c::[key[0].toUpperCase() + key[1..]] = val
		# lowercase
		c::[key.toLowerCase()] = val
