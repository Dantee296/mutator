
// automatically generated by luatablegen
#include "../lua-5.3.4/src/lua.h"
#include "../lua-5.3.4/src/lauxlib.h"
#include "../lua-5.3.4/src/lualib.h"
#include <inttypes.h>
#include <stdbool.h>
#include "./W_Data_Segment_tablegen.h"

#include "../wasm.h"

static W_Data_Segment* convert_W_Data_Segment (lua_State* __ls, int index) {
	W_Data_Segment* dummy = (W_Data_Segment*)lua_touserdata(__ls, index);
	if (dummy == NULL) printf("W_Data_Segment:bad user data type.\n");
	return dummy;
}

static W_Data_Segment* check_W_Data_Segment(lua_State* __ls, int index) {
	W_Data_Segment* dummy;
	luaL_checktype(__ls, index, LUA_TUSERDATA);
	dummy = (W_Data_Segment*)luaL_checkudata(__ls, index, "W_Data_Segment");
	if (dummy == NULL) printf("W_Data_Segment:bad user data type.\n");
	return dummy;
}

W_Data_Segment* push_W_Data_Segment(lua_State* __ls) {
	lua_checkstack(__ls, 1);
	W_Data_Segment* dummy = lua_newuserdata(__ls, sizeof(W_Data_Segment));
	luaL_getmetatable(__ls, "W_Data_Segment");
	lua_setmetatable(__ls, -2);
	return dummy;
}

int W_Data_Segment_push_args(lua_State* __ls, W_Data_Segment* _st) {
	lua_checkstack(__ls, 4);
	lua_pushinteger(__ls, _st->index);
	lua_pushlightuserdata(__ls, _st->offset);
	lua_pushinteger(__ls, _st->size);
	lua_pushstring(__ls, _st->data);
	return 0;
}

int new_W_Data_Segment(lua_State* __ls) {
	lua_checkstack(__ls, 4);
	varuint32 index = luaL_optinteger(__ls,-4,0);
	init_expr_t* offset = lua_touserdata(__ls,-3);
	varuint32 size = luaL_optinteger(__ls,-2,0);
	char* data = lua_tostring(__ls,-1);
	W_Data_Segment* dummy = push_W_Data_Segment(__ls);
	dummy->index = index;
	dummy->offset = offset;
	dummy->size = size;
	dummy->data = data;
	return 1;
}

static int getter_W_Data_Segment_index(lua_State* __ls) {
	W_Data_Segment* dummy = check_W_Data_Segment(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushinteger(__ls, dummy->index);
	return 1;
}
static int getter_W_Data_Segment_offset(lua_State* __ls) {
	W_Data_Segment* dummy = check_W_Data_Segment(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushlightuserdata(__ls, dummy->offset);
	return 1;
}
static int getter_W_Data_Segment_size(lua_State* __ls) {
	W_Data_Segment* dummy = check_W_Data_Segment(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushinteger(__ls, dummy->size);
	return 1;
}
static int getter_W_Data_Segment_data(lua_State* __ls) {
	W_Data_Segment* dummy = check_W_Data_Segment(__ls, 1);
	lua_pop(__ls, -1);
	lua_pushstring(__ls, dummy->data);
	return 1;
}

static int setter_W_Data_Segment_index(lua_State* __ls) {
	W_Data_Segment* dummy = check_W_Data_Segment(__ls, 1);
	dummy->index = luaL_checkinteger(__ls, 2);
	lua_settop(__ls, 1);
	return 1;
}
static int setter_W_Data_Segment_offset(lua_State* __ls) {
	W_Data_Segment* dummy = check_W_Data_Segment(__ls, 1);
	dummy->offset = luaL_checkudata(__ls, 2, "offset_t");
	lua_settop(__ls, 1);
	return 1;
}
static int setter_W_Data_Segment_size(lua_State* __ls) {
	W_Data_Segment* dummy = check_W_Data_Segment(__ls, 1);
	dummy->size = luaL_checkinteger(__ls, 2);
	lua_settop(__ls, 1);
	return 1;
}
static int setter_W_Data_Segment_data(lua_State* __ls) {
	W_Data_Segment* dummy = check_W_Data_Segment(__ls, 1);
	dummy->data = luaL_checkstring(__ls, 2);
	lua_settop(__ls, 1);
	return 1;
}

static const luaL_Reg W_Data_Segment_methods[] = {
	{"new", new_W_Data_Segment},
	{"set_index", setter_W_Data_Segment_index},
	{"set_offset", setter_W_Data_Segment_offset},
	{"set_size", setter_W_Data_Segment_size},
	{"set_data", setter_W_Data_Segment_data},
	{"index", getter_W_Data_Segment_index},
	{"offset", getter_W_Data_Segment_offset},
	{"size", getter_W_Data_Segment_size},
	{"data", getter_W_Data_Segment_data},
	{0,0}
};

static const luaL_Reg W_Data_Segment_meta[] = {
	{0, 0}
};

int W_Data_Segment_register(lua_State* __ls) {
	luaL_openlib(__ls, "W_Data_Segment", W_Data_Segment_methods, 0);
	luaL_newmetatable(__ls, "W_Data_Segment");
	luaL_openlib(__ls, 0, W_Data_Segment_meta, 0);
	lua_pushliteral(__ls, "__index");
	lua_pushvalue(__ls, -3);
	lua_rawset(__ls, -3);
	lua_pushliteral(__ls, "__metatable");
	lua_pushvalue(__ls, -3);
	lua_rawset(__ls, -3);
	lua_pop(__ls, 1);
return 1;
}


