
// automatically generated by luatablegen
#include "../lua-5.3.4/src/lua.h"
#include "../lua-5.3.4/src/lauxlib.h"
#include "../lua-5.3.4/src/lualib.h"
#include <inttypes.h>
#include <stdbool.h>
#ifndef _W_Table_Section_H
#define _W_Table_Section_H
#ifdef __cplusplus
extern "C" {
#endif

#include "../wasm.h"

static W_Table_Section* convert_W_Table_Section (lua_State* __ls, int index);
static W_Table_Section* check_W_Table_Section(lua_State* __ls, int index);
W_Table_Section* push_W_Table_Section(lua_State* __ls);
int W_Table_Section_push_args(lua_State* __ls, W_Table_Section* _st);
int new_W_Table_Section(lua_State* __ls);
static int getter_W_Table_Section_count(lua_State* __ls);
static int getter_W_Table_Section_entries(lua_State* __ls);
static int setter_W_Table_Section_count(lua_State* __ls);
static int setter_W_Table_Section_entries(lua_State* __ls);
int W_Table_Section_register(lua_State* __ls);

#ifdef __cplusplus
}
#endif //end of extern c
#endif //end of inclusion guard


