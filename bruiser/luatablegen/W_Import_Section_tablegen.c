
// automatically generated by luatablegen
#include "../lua-5.3.4/src/lua.h"
#include "../lua-5.3.4/src/lauxlib.h"
#include "../lua-5.3.4/src/lualib.h"
#include <inttypes.h>
#include <stdbool.h>
#include "./W_Import_Section_tablegen.h"

#include "../wasm.h"

static W_Import_Section* convert_W_Import_Section (lua_State* __ls, int index) {
	W_Import_Section* dummy = (W_Import_Section*)lua_touserdata(__ls, index);
	if (dummy == NULL) printf("W_Import_Section:bad user data type.\n");
	return dummy;
}

static W_Import_Section* check_W_Import_Section(lua_State* __ls, int index) {
	W_Import_Section* dummy;
	luaL_checktype(__ls, index, LUA_TUSERDATA);
	dummy = (W_Import_Section*)luaL_checkudata(__ls, index, "W_Import_Section");
	if (dummy == NULL) printf("W_Import_Section:bad user data type.\n");
	return dummy;
}

W_Import_Section* push_W_Import_Section(lua_State* __ls) {
	lua_checkstack(__ls, 1);
	W_Import_Section* dummy = lua_newuserdata(__ls, sizeof(W_Import_Section));
	luaL_getmetatable(__ls, "W_Import_Section");
	lua_setmetatable(__ls, -2);
	return dummy;
}

int W_Import_Section_push_args(lua_State* __ls, W_Import_Section* _st) {
	lua_checkstack(__ls, 2);
	lua_pushinteger(__ls, _st->count);
	lua_pushlightuserdata(__ls, _st->entries);
	return 0;
}

int new_W_Import_Section(lua_State* __ls) {
	lua_checkstack(__ls, 2);
	varuint32 count = luaL_optinteger(__ls,-2,0);
	W_Import_Section** entries = lua_touserdata(__ls,-1);
	W_Import_Section* dummy = push_W_Import_Section(__ls);
	dummy->count = count;
	dummy->entries = entries;
	return 1;
}

static int getter_W_Import_Section_count(lua_State* __ls) {
	W_Import_Section* dummy = check_W_Import_Section(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushinteger(__ls, dummy->count);
	return 1;
}
static int getter_W_Import_Section_entries(lua_State* __ls) {
	W_Import_Section* dummy = check_W_Import_Section(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushlightuserdata(__ls, dummy->entries);
	return 1;
}

static int setter_W_Import_Section_count(lua_State* __ls) {
	W_Import_Section* dummy = check_W_Import_Section(__ls, 1);
	dummy->count = luaL_checkinteger(__ls, 2);
	lua_settop(__ls, 1);
	return 1;
}
static int setter_W_Import_Section_entries(lua_State* __ls) {
	W_Import_Section* dummy = check_W_Import_Section(__ls, 1);
	dummy->entries = luaL_checkudata(__ls, 2, "entries_t");
	lua_settop(__ls, 1);
	return 1;
}

static const luaL_Reg W_Import_Section_methods[] = {
	{"new", new_W_Import_Section},
	{"set_count", setter_W_Import_Section_count},
	{"set_entries", setter_W_Import_Section_entries},
	{"count", getter_W_Import_Section_count},
	{"entries", getter_W_Import_Section_entries},
	{0,0}
};

static const luaL_Reg W_Import_Section_meta[] = {
	{0, 0}
};

int W_Import_Section_register(lua_State* __ls) {
	luaL_openlib(__ls, "W_Import_Section", W_Import_Section_methods, 0);
	luaL_newmetatable(__ls, "W_Import_Section");
	luaL_openlib(__ls, 0, W_Import_Section_meta, 0);
	lua_pushliteral(__ls, "__index");
	lua_pushvalue(__ls, -3);
	lua_rawset(__ls, -3);
	lua_pushliteral(__ls, "__metatable");
	lua_pushvalue(__ls, -3);
	lua_rawset(__ls, -3);
	lua_pop(__ls, 1);
return 1;
}


