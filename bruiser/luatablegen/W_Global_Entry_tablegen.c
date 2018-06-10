
// automatically generated by luatablegen
#include "../lua-5.3.4/src/lua.h"
#include "../lua-5.3.4/src/lauxlib.h"
#include "../lua-5.3.4/src/lualib.h"
#include <inttypes.h>
#include <stdbool.h>
#ifndef _W_Global_Entry_H
#define _W_Global_Entry_H
#ifdef __cplusplus
extern "C" {
#endif
#include "./W_Global_Entry_tablegen.h"

#include "../wasm.h"

static W_Global_Entry* convert_W_Global_Entry (lua_State* __ls, int index) {
	W_Global_Entry* dummy = (W_Global_Entry*)lua_touserdata(__ls, index);
	if (dummy == NULL) printf("W_Global_Entry:bad user data type.\n");
	return dummy;
}

static W_Global_Entry* check_W_Global_Entry(lua_State* __ls, int index) {
	W_Global_Entry* dummy;
	luaL_checktype(__ls, index, LUA_TUSERDATA);
	dummy = (W_Global_Entry*)luaL_checkudata(__ls, index, "W_Global_Entry");
	if (dummy == NULL) printf("W_Global_Entry:bad user data type.\n");
	return dummy;
}

W_Global_Entry* push_W_Global_Entry(lua_State* __ls) {
	lua_checkstack(__ls, 1);
	W_Global_Entry* dummy = lua_newuserdata(__ls, sizeof(W_Global_Entry));
	luaL_getmetatable(__ls, "W_Global_Entry");
	lua_setmetatable(__ls, -2);
	return dummy;
}

int W_Global_Entry_push_args(lua_State* __ls, W_Global_Entry* _st) {
	lua_checkstack(__ls, 2);
	lua_pushlightuserdata(__ls, _st->type);
	lua_pushlightuserdata(__ls, _st->init);
	return 0;
}

int new_W_Global_Entry(lua_State* __ls) {
	lua_checkstack(__ls, 2);
	global_type_t* type = lua_touserdata(__ls,-2);
	init_expr_t* init = lua_touserdata(__ls,-1);
	W_Global_Entry* dummy = push_W_Global_Entry(__ls);
	dummy->type = type;
	dummy->init = init;
	return 1;
}

static int getter_W_Global_Entry_type(lua_State* __ls) {
	W_Global_Entry* dummy = check_W_Global_Entry(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushlightuserdata(__ls, dummy->type);
	return 1;
}
static int getter_W_Global_Entry_init(lua_State* __ls) {
	W_Global_Entry* dummy = check_W_Global_Entry(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushlightuserdata(__ls, dummy->init);
	return 1;
}

static int setter_W_Global_Entry_type(lua_State* __ls) {
	W_Global_Entry* dummy = check_W_Global_Entry(__ls, 1);
	dummy->type = luaL_checkudata(__ls, 2, "W_Global_Entry");
	lua_settop(__ls, 1);
	return 1;
}
static int setter_W_Global_Entry_init(lua_State* __ls) {
	W_Global_Entry* dummy = check_W_Global_Entry(__ls, 1);
	dummy->init = luaL_checkudata(__ls, 2, "W_Global_Entry");
	lua_settop(__ls, 1);
	return 1;
}

static const luaL_Reg W_Global_Entry_methods[] = {
	{"new", new_W_Global_Entry},
	{"set_type", setter_W_Global_Entry_type},
	{"set_init", setter_W_Global_Entry_init},
	{"type", getter_W_Global_Entry_type},
	{"init", getter_W_Global_Entry_init},
	{0,0}
};

static const luaL_Reg W_Global_Entry_meta[] = {
	{0, 0}
};

int W_Global_Entry_register(lua_State* __ls) {
	luaL_openlib(__ls, "W_Global_Entry", W_Global_Entry_methods, 0);
	luaL_newmetatable(__ls, "W_Global_Entry");
	luaL_openlib(__ls, 0, W_Global_Entry_meta, 0);
	lua_pushliteral(__ls, "__index");
	lua_pushvalue(__ls, -3);
	lua_rawset(__ls, -3);
	lua_pushliteral(__ls, "__metatable");
	lua_pushvalue(__ls, -3);
	lua_rawset(__ls, -3);
	lua_pop(__ls, 1);
return 1;
}

#ifdef __cplusplus
}
#endif //end of extern c
#endif //end of inclusion guard


