
#ifndef COMPRESSEDLUACHUNKS_DOT_H
#define COMPRESSEDLUACHUNKS_DOT_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <zlib.h>
}

#define ZLIB_DEFLATE_LEVEL		9
#define ZLIB_INFLATE_BUFSIZE	1024

typedef struct AGSLuaPersistState {
	int handle;
	luaL_Buffer b;
	z_stream_s z_stream;

	unsigned int count;
	int finished;
	char c;
} AGSLuaPersistState;

typedef struct AGSLuaUnpersistState {
	z_stream_s z_stream;
	Bytef buf[ZLIB_INFLATE_BUFSIZE];
} AGSLuaUnpersistState;

int AGSLuaPersistWriter(lua_State *persist_L, const void* p, size_t sz, void* ud);
const char* AGSLuaPersistReader(lua_State *persist_L, void* data, size_t* size);
int aux_loadcompressed(lua_State* L, FILE* f, int offset, int length);

#endif // COMPRESSEDLUACHUNKS_DOT_H
