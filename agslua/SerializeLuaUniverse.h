
#ifndef SERIALIZELUAUNIVERSE_DOT_H
#define SERIALIZELUAUNIVERSE_DOT_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

int autopersist(lua_State *L);

#endif
