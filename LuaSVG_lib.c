#include "nanosvg.h"

#if defined __WIN32__ || defined WIN32
  #include <windows.h>
  #define _EXPORT __declspec(dllexport)
#else
  #define _EXPORT
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "nanosvg.h"

int
SVG_eval(lua_State *L);

void
stackdump_g(lua_State* l);

int
SVG_load(lua_State *L)
{
	const char *filename = luaL_checkstring(L,1);

	FILE *file = fopen(filename, "r");
	if(!file)
    return luaL_error(L,"LuaSVG ERROR: \"%s\" file error or file not found!",filename);

  // get the size of the file to alloc enough space in memory
	fseek (file , 0 , SEEK_END);
	size_t sz = ftell (file);
	rewind (file);

	char* buffer = (char*)malloc(sz+1);

	sz = fread (buffer,1,sz,file);
	fclose(file);
	buffer[sz] = 0;
	lua_pushlightuserdata(L, buffer);
	lua_replace(L, 1);
  
  return SVG_eval(L);
}

int
SVG_eval(lua_State *L)
{
  char *str = 0;
  size_t str_size = 0;

  if (lua_isuserdata(L, 1)) {
    str = (char *)lua_touserdata(L, 1);
  }
  else
  {
    const char * sTmp = luaL_checklstring(L, 1, &str_size);
    str = (char *)malloc(str_size + 1);
    memcpy(str, sTmp, str_size);
    str[str_size] = 0;
  }

  struct SVGPath *pList = NULL;
  pList = svgParse(str);

  lua_settop(L, 0); // remove stack elements

  if (pList == NULL)
    return luaL_error(L, "LuaSVG ERROR: Need to change this");
    //return luaL_error(L, "LuaSVG ERROR: \"%s\" file error or file not found!", filename);

  lua_newtable(L); // holds all the paths
  struct SVGPath *it = pList;

  int j = 0;
  for (; it; it = it->next)
  {
    j++;
    int i = 0;
    lua_newtable(L); // holds all the vertices

    for (; i < it->npts; ++i) {

      lua_newtable(L); // array that holds all the vertices

      lua_pushliteral(L, "x");
      lua_pushnumber(L, it->pts[i*2]);
      lua_settable(L, -3);

      lua_pushliteral(L, "y");
      lua_pushnumber(L, it->pts[i*2+1]);
      lua_settable(L, -3);

      lua_pushinteger(L, i + 1); // just to stay consistant with other lua stuff
      lua_insert(L, -2);
      lua_settable(L, -3);
    }

    lua_pushinteger(L, j); // just to stay consistant with other lua stuff
    lua_insert(L, -2);
    lua_settable(L, -3);
  }

  svgDelete(pList);
  free(str);

  return lua_gettop(L);
}


int
_EXPORT luaopen_LuaSVG_lib(lua_State* L)
{
  static const struct luaL_Reg funcs[] = {
    {"load", SVG_load},
    {"eval", SVG_eval},
    {NULL, NULL}
  };

  luaL_register(L, "svg", funcs);

  return 1;
}

#if(0)
void stackdump_g(lua_State* l)
{
    int i;
    int top = lua_gettop(l);
 
    printf("total in stack %d\n",top);
 
    for (i = top; i >= 1; i--)
    {  /* repeat for each level */
        int idx = i - top - 1;
        int t = lua_type(l, idx);
        printf("[%d]%d ", idx, i );
        switch (t) {
            case LUA_TSTRING:  /* strings */
                printf("string: '%s'\n", lua_tostring(l, idx));
                break;
            case LUA_TBOOLEAN:  /* booleans */
                printf("boolean %s\n",lua_toboolean(l, idx) ? "true" : "false");
                break;
            case LUA_TNUMBER:  /* numbers */
                printf("number: %g\n", lua_tonumber(l, idx));
                break;
            default:  /* other values */
                printf("%s\n", lua_typename(l, t));
                break;
        }
        //printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}
#endif
