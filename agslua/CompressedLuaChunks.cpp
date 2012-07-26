
#include <windows.h>

extern "C" {
	#include <zlib.h>
#include <malloc.h>
}

#include "CompressedLuaChunks.h"
#include "AGSLua.h"

int AGSLuaPersistWriter(lua_State *persist_L, const void* p, size_t sz, void* ud) {
	AGSLuaPersistState* pst = (AGSLuaPersistState*)ud;
	pst->z_stream.next_in = (Bytef*)p;
	pst->z_stream.avail_in = (uInt)sz;
	while (pst->z_stream.avail_in > 0) {
		deflate(&pst->z_stream, 0);
		if (pst->z_stream.avail_out == 0) {
			luaL_addsize(&pst->b, LUAL_BUFFERSIZE - pst->z_stream.avail_out);
			pst->z_stream.next_out = (Bytef*)luaL_prepbuffer(&pst->b);
			pst->z_stream.avail_out = LUAL_BUFFERSIZE;
		}
	}
	return 0;
}

const char* AGSLuaPersistReader(lua_State *persist_L, void* data, size_t* size) {
	AGSLuaUnpersistState* pst = (AGSLuaUnpersistState*)data;
	const char* result;
	while (pst->z_stream.avail_out == ZLIB_INFLATE_BUFSIZE) {
		int code = inflate(&pst->z_stream, Z_FINISH);
		if (code == Z_STREAM_END) {
			break;
		}
		else if (code != Z_OK && code != Z_BUF_ERROR) {
			luaL_error(persist_L, "zlib decompression error");
			return NULL;
		}
	}
	*size = (size_t)(ZLIB_INFLATE_BUFSIZE - pst->z_stream.avail_out);
	pst->z_stream.next_out = pst->buf;
	pst->z_stream.avail_out = ZLIB_INFLATE_BUFSIZE;
	result = (const char*)(&pst->buf[0]);
	return result;
}

int aux_loadcompressed(lua_State* L, FILE* f, int offset, int length) {
	AGSLuaUnpersistState state;
	const char* buf;
	int retcode;
	fseek(f, offset, SEEK_SET);
	buf = (const char*)malloc(length);
	fread((void*)buf, 1, length, f);

	state.z_stream.avail_in = (uInt)length;
	state.z_stream.next_in = (Bytef*)buf;
	state.z_stream.avail_out = ZLIB_INFLATE_BUFSIZE;
	state.z_stream.next_out = state.buf;
	state.z_stream.zalloc = Z_NULL;
	state.z_stream.zfree = Z_NULL;
	state.z_stream.opaque = NULL;
	int code = inflateInit(&state.z_stream);
	if (code != Z_OK)
	{
		fclose(f);
		luaL_error(L, "inflateInit returned error code %d", code);
	}
	retcode = lua_load(L, AGSLuaPersistReader, &state, "lscripts.dat");
	inflateEnd(&state.z_stream);
	free((void*)buf);
	return retcode;
}
