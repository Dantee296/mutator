
// automatically generated by luatablegen
#include "../lua-5.3.4/src/lua.h"
#include "../lua-5.3.4/src/lauxlib.h"
#include "../lua-5.3.4/src/lualib.h"
#include <inttypes.h>
#include <stdbool.h>
#include "./table_type_t_tablegen.h"

#include "../wasm.h"

static table_type_t* convert_table_type_t (lua_State* __ls, int index) {
	table_type_t* dummy = (table_type_t*)lua_touserdata(__ls, index);
	if (dummy == NULL) printf("table_type_t:bad user data type.\n");
	return dummy;
}

static table_type_t* check_table_type_t(lua_State* __ls, int index) {
	table_type_t* dummy;
	luaL_checktype(__ls, index, LUA_TUSERDATA);
	dummy = (table_type_t*)luaL_checkudata(__ls, index, "table_type_t");
	if (dummy == NULL) printf("table_type_t:bad user data type.\n");
	return dummy;
}

table_type_t* push_table_type_t(lua_State* __ls) {
	lua_checkstack(__ls, 1);
	table_type_t* dummy = lua_newuserdata(__ls, sizeof(table_type_t));
	luaL_getmetatable(__ls, "table_type_t");
	lua_setmetatable(__ls, -2);
	return dummy;
}

int table_type_t_push_args(lua_State* __ls, table_type_t* _st) {
	lua_checkstack(__ls, 2);
	lua_pushinteger(__ls, _st->element_type);
	lua_pushlightuserdata(__ls, _st->resizable_limit);
	return 0;
}

int new_table_type_t(lua_State* __ls) {
	lua_checkstack(__ls, 2);
	varint7 element_type = luaL_optinteger(__ls,-2,0);
	resizable_limit_t* resizable_limit = lua_touserdata(__ls,-1);
	table_type_t* dummy = push_table_type_t(__ls);
	dummy->element_type = element_type;
	dummy->resizable_limit = resizable_limit;
	return 1;
}

static int getter_table_type_t_element_type(lua_State* __ls) {
	table_type_t* dummy = check_table_type_t(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushinteger(__ls, dummy->element_type);
	return 1;
}
static int getter_table_type_t_resizable_limit(lua_State* __ls) {
	table_type_t* dummy = check_table_type_t(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushlightuserdata(__ls, dummy->resizable_limit);
	return 1;
}

static int setter_table_type_t_element_type(lua_State* __ls) {
	table_type_t* dummy = check_table_type_t(__ls, 1);
	dummy->element_type = luaL_checkinteger(__ls, 2);
	lua_settop(__ls, 1);
	return 1;
}
static int setter_table_type_t_resizable_limit(lua_State* __ls) {
	table_type_t* dummy = check_table_type_t(__ls, 1);
	dummy->resizable_limit = luaL_checkudata(__ls, 2, "resizable_limit_t");
	lua_settop(__ls, 1);
	return 1;
}

static const luaL_Reg table_type_t_methods[] = {
	{"new", new_table_type_t},
	{"set_element_type", setter_table_type_t_element_type},
	{"set_resizable_limit", setter_table_type_t_resizable_limit},
	{"element_type", getter_table_type_t_element_type},
	{"resizable_limit", getter_table_type_t_resizable_limit},
	{0,0}
};

static const luaL_Reg table_type_t_meta[] = {
	{0, 0}
};

int table_type_t_register(lua_State* __ls) {
	luaL_openlib(__ls, "table_type_t", table_type_t_methods, 0);
	luaL_newmetatable(__ls, "table_type_t");
	luaL_openlib(__ls, 0, table_type_t_meta, 0);
	lua_pushliteral(__ls, "__index");
	lua_pushvalue(__ls, -3);
	lua_rawset(__ls, -3);
	lua_pushliteral(__ls, "__metatable");
	lua_pushvalue(__ls, -3);
	lua_rawset(__ls, -3);
	lua_pop(__ls, 1);
return 1;
}


