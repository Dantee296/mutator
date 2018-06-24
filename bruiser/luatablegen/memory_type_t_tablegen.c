
// automatically generated by luatablegen
#include "../lua-5.3.4/src/lua.h"
#include "../lua-5.3.4/src/lauxlib.h"
#include "../lua-5.3.4/src/lualib.h"
#include <inttypes.h>
#include <stdbool.h>
#include "./memory_type_t_tablegen.h"

#include "../wasm.h"

static memory_type_t* convert_memory_type_t (lua_State* __ls, int index) {
	memory_type_t* dummy = (memory_type_t*)lua_touserdata(__ls, index);
	if (dummy == NULL) printf("memory_type_t:bad user data type.\n");
	return dummy;
}

static memory_type_t* check_memory_type_t(lua_State* __ls, int index) {
	memory_type_t* dummy;
	luaL_checktype(__ls, index, LUA_TUSERDATA);
	dummy = (memory_type_t*)luaL_checkudata(__ls, index, "memory_type_t");
	if (dummy == NULL) printf("memory_type_t:bad user data type.\n");
	return dummy;
}

memory_type_t* push_memory_type_t(lua_State* __ls) {
	lua_checkstack(__ls, 1);
	memory_type_t* dummy = lua_newuserdata(__ls, sizeof(memory_type_t));
	luaL_getmetatable(__ls, "memory_type_t");
	lua_setmetatable(__ls, -2);
	return dummy;
}

int memory_type_t_push_args(lua_State* __ls, memory_type_t* _st) {
	lua_checkstack(__ls, 1);
	lua_pushlightuserdata(__ls, _st->resizable_limit);
	return 0;
}

int new_memory_type_t(lua_State* __ls) {
	lua_checkstack(__ls, 1);
	resizable_limit_t* resizable_limit = lua_touserdata(__ls,-1);
	memory_type_t* dummy = push_memory_type_t(__ls);
	dummy->resizable_limit = resizable_limit;
	return 1;
}

static int getter_memory_type_t_resizable_limit(lua_State* __ls) {
	memory_type_t* dummy = check_memory_type_t(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushlightuserdata(__ls, dummy->resizable_limit);
	return 1;
}

static int setter_memory_type_t_resizable_limit(lua_State* __ls) {
	memory_type_t* dummy = check_memory_type_t(__ls, 1);
	dummy->resizable_limit = luaL_checkudata(__ls, 2, "resizable_limit_t");
	lua_settop(__ls, 1);
	return 1;
}

static const luaL_Reg memory_type_t_methods[] = {
	{"new", new_memory_type_t},
	{"set_resizable_limit", setter_memory_type_t_resizable_limit},
	{"resizable_limit", getter_memory_type_t_resizable_limit},
	{0,0}
};

static const luaL_Reg memory_type_t_meta[] = {
	{0, 0}
};

int memory_type_t_register(lua_State* __ls) {
	luaL_openlib(__ls, "memory_type_t", memory_type_t_methods, 0);
	luaL_newmetatable(__ls, "memory_type_t");
	luaL_openlib(__ls, 0, memory_type_t_meta, 0);
	lua_pushliteral(__ls, "__index");
	lua_pushvalue(__ls, -3);
	lua_rawset(__ls, -3);
	lua_pushliteral(__ls, "__metatable");
	lua_pushvalue(__ls, -3);
	lua_rawset(__ls, -3);
	lua_pop(__ls, 1);
return 1;
}


