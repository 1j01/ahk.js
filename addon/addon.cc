
#include "src/stdafx.h"
#include <string>
//#include <tchar.h>

#include <node.h>

using v8::Value;
using v8::Function;
using v8::String;
using v8::Object;
using v8::Undefined;

using v8::FunctionTemplate;
using v8::Handle;
using v8::Arguments;
using v8::HandleScope;
using v8::Local;
using v8::Context;

#include "src/keyboard_mouse.h"

Handle<Value> send(const Arguments& args) {
	HandleScope scope;
	
	// get the param
	v8::String::Utf8Value param1(args[0]->ToString());

	// convert it to string
	std::string keystring = std::string(*param1);
	
	TCHAR c[1000];
	//strncpy(c, keystring.c_str(), 999);
	std::copy(keystring.begin(), keystring.end(), c);
	c[999] = '\0';
	SendKeys(c, false, SM_PLAY, 0);

	return scope.Close(Undefined());
}

void init(Handle<Object> exports, Handle<Object> module) {
	module->Set(
		String::NewSymbol("exports"),
		FunctionTemplate::New(send)->GetFunction()
	);
}

NODE_MODULE(ahk, init);
