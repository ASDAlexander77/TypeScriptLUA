#include <GL/glut.h>

#ifdef __cplusplus
#include "lua.hpp"
#else
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#endif

#ifdef _WIN32
#define LIBRARY_API extern __declspec(dllexport)
#elif
#define LIBRARY_API static
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    // === public
    static lua_State *global_L = NULL;

    static int initGLUT(lua_State *L)
    {
        int argc = 0;
        glutInit(&argc, NULL);
        return 0;
    }

    static int initWindowSizeGLUT(lua_State *L)
    {
        const GLint width = (GLint) luaL_checkinteger(L, 1);
        const GLint height = (GLint) luaL_checkinteger(L, 2);

        glutInitWindowSize(width, height);

        return 0;
    }

    static int initWindowPositionGLUT(lua_State *L)
    {
        const GLint top = (GLint) luaL_checkinteger(L, 1);
        const GLint left = (GLint) luaL_checkinteger(L, 2);

        glutInitWindowPosition(top, left);

        return 0;
    }    

    static int initDisplayModeGLUT(lua_State *L)
    {
        int arg = 1;
        GLint val = 0;
        while(!lua_isnoneornil(L, arg)) 
        {
            val |= luaL_checkinteger(L, arg++);
        }

        glutInitDisplayMode(val);

        return 0;
    }    

    static int createWindowGLUT(lua_State *L)
    {
        const char *name = luaL_checkstring(L, 1);

        int windowId = glutCreateWindow(name ? name : "GLUT Window");

        lua_pushinteger(L, windowId);

        return 1;
    }

    // Display
    static int luaDisplayFunctionReference = LUA_NOREF;
    static void displayCallback(void)
    {
        if (luaDisplayFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaDisplayFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_call(global_L, 0, 0);
    }

    static int displayFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaDisplayFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaDisplayFunctionReference);
        }

        luaDisplayFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        glutDisplayFunc(displayCallback);

        return 0;
    }

    // PassiveMotion
    static int luaPassiveMotionFunctionReference = LUA_NOREF;
    static void passiveMotionCallback(GLint x, GLint y)
    {
        if (luaPassiveMotionFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaPassiveMotionFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_pushinteger(global_L, x);
        lua_pushinteger(global_L, y);
        lua_call(global_L, 2, 0);        
    }

    static int passiveMotionFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaPassiveMotionFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaPassiveMotionFunctionReference);
        }

        luaPassiveMotionFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        glutPassiveMotionFunc(passiveMotionCallback);

        return 0;
    }

    // Mouse
    static int luaMouseFunctionReference = LUA_NOREF;
    static void mouseCallback(GLint button, GLint state, GLint x, GLint y)
    {
        if (luaMouseFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaMouseFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_pushinteger(global_L, button);
        lua_pushinteger(global_L, state);
        lua_pushinteger(global_L, x);
        lua_pushinteger(global_L, y);
        lua_call(global_L, 4, 0);       
    }

    static int mouseFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaMouseFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaMouseFunctionReference);
        }

        luaMouseFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        glutMouseFunc(mouseCallback);

        return 0;
    }    

    // MouseWheel
    static int luaMouseWheelFunctionReference = LUA_NOREF;
    static void mouseWheelCallback(GLint button, GLint state, GLint x, GLint y)
    {
        if (luaMouseWheelFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaMouseWheelFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_pushinteger(global_L, button);
        lua_pushinteger(global_L, state);
        lua_pushinteger(global_L, x);
        lua_pushinteger(global_L, y);
        lua_call(global_L, 4, 0);       
    }

    static int mouseWheelFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaMouseWheelFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaMouseWheelFunctionReference);
        }

        luaMouseWheelFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        // glutMouseWheelFunc(mouseWheelCallback);

        return 0;
    }    

    // Motion
    static int luaMotionFunctionReference = LUA_NOREF;
    static void motionCallback(GLint x, GLint y)
    {
        if (luaMotionFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaMotionFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_pushinteger(global_L, x);
        lua_pushinteger(global_L, y);
        lua_call(global_L, 2, 0); 
    }

    static int motionFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaMotionFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaMotionFunctionReference);
        }

        luaMotionFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        glutMotionFunc(motionCallback);

        return 0;
    }      

    // Idle
    static int luaIdleFunctionReference = LUA_NOREF;
    static void idleCallback(void)
    {
        if (luaIdleFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaIdleFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_call(global_L, 0, 0);
    }

    static int idleFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaIdleFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaIdleFunctionReference);
        }

        luaIdleFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        glutIdleFunc(idleCallback);

        return 0;
    }

    // Keyboard
    static int luaKeyboardFunctionReference = LUA_NOREF;
    static void keyboardCallback(unsigned char k, GLint x, GLint y)
    {
        if (luaKeyboardFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaKeyboardFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_pushinteger(global_L, k);
        lua_pushinteger(global_L, x);
        lua_pushinteger(global_L, y);
        lua_call(global_L, 3, 0); 
    } 

    static int keyboardFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaKeyboardFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaKeyboardFunctionReference);
        }

        luaKeyboardFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        glutKeyboardFunc(keyboardCallback);

        return 0;
    }    

    // KeyboardUp
    static int luaKeyboardUpFunctionReference = LUA_NOREF;
    static void keyboardUpCallback(unsigned char k, GLint x, GLint y)
    {
        if (luaKeyboardUpFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaKeyboardUpFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_pushinteger(global_L, k);
        lua_pushinteger(global_L, x);
        lua_pushinteger(global_L, y);
        lua_call(global_L, 3, 0); 
    }

    static int keyboardUpFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaKeyboardUpFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaKeyboardUpFunctionReference);
        }

        luaKeyboardUpFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        glutKeyboardUpFunc(keyboardUpCallback);

        return 0;
    }    

    // Special
    static int luaSpecialFunctionReference = LUA_NOREF;
    static void specialCallback(GLint k, GLint x, GLint y)
    {
        if (luaSpecialFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaSpecialFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_pushinteger(global_L, k);
        lua_pushinteger(global_L, x);
        lua_pushinteger(global_L, y);
        lua_call(global_L, 3, 0); 
    }

    static int specialFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaSpecialFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaSpecialFunctionReference);
        }

        luaSpecialFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        glutSpecialFunc(specialCallback);

        return 0;
    }    

    // SpecialUp
    static int luaSpecialUpFunctionReference = LUA_NOREF;
    static void specialUpCallback(GLint k, GLint x, GLint y)
    {
        if (luaSpecialUpFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaSpecialUpFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_pushinteger(global_L, k);
        lua_pushinteger(global_L, x);
        lua_pushinteger(global_L, y);
        lua_call(global_L, 3, 0); 
    }

    static int specialUpFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaSpecialUpFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaSpecialUpFunctionReference);
        }

        luaSpecialUpFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        glutSpecialUpFunc(specialUpCallback);

        return 0;
    } 

    // Reshape
    static int luaReshapeFunctionReference = LUA_NOREF;
    static void reshapeCallback(GLint w, GLint h)
    {
        if (luaReshapeFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaReshapeFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_pushinteger(global_L, w);
        lua_pushinteger(global_L, h);
        lua_call(global_L, 2, 0); 
    }

    static int reshapeFuncGLUT(lua_State *L)
    {
        if (!lua_isfunction(L, 1))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 1);
        }

        if (luaReshapeFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaReshapeFunctionReference);
        }

        luaReshapeFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        glutReshapeFunc(reshapeCallback);

        return 0;
    }      

    // Timer
    static int luaTimerFunctionReference = LUA_NOREF;
    static void timerCallback(GLint value)
    {
        if (luaTimerFunctionReference != LUA_NOREF)
        {
            if (lua_rawgeti(global_L, LUA_REGISTRYINDEX, luaTimerFunctionReference) != LUA_TFUNCTION)
            {
                luaL_error(global_L, "bad argument #%d (function expected) in callback", 1);
                return;
            }
        }

        lua_pushinteger(global_L, value);
        lua_call(global_L, 1, 0);
    }

    static int timerFuncGLUT(lua_State *L)
    {
        GLint msecs = (GLint) luaL_checkinteger(L, 1);
        if (!lua_isfunction(L, 2))
        {
            return luaL_error(L, "bad argument #%d (function expected)", 2);
        }

        if (luaTimerFunctionReference != LUA_NOREF)
        {
            luaL_unref(L, LUA_REGISTRYINDEX, luaTimerFunctionReference);
        }

        lua_pushvalue(L, 2);
        luaTimerFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);

        // 3)
        GLint value = (GLint) luaL_checkinteger(L, 3);

        glutTimerFunc(msecs, timerCallback, value);

        return 0;
    }    

    static postRedisplayGLUT(lua_State *L)
    {
        glutPostRedisplay();
        return 0;
    }

    static int mainLoopGLUT(lua_State *L)
    {
        glutMainLoop();
        return 0;
    }

    static int swapBuffersGLUT(lua_State *L)
    {
        glutSwapBuffers();
        return 0;
    }

    static int setKeyRepeatGLUT(lua_State *L)
    {
        GLint value = (GLint) luaL_checkinteger(L, 1);
        glutSetKeyRepeat(value);
        return 0;
    }

    static int ignoreKeyRepeatGLUT(lua_State *L)
    {
        const GLboolean value = lua_toboolean(L, 1);
        glutIgnoreKeyRepeat(value ? 1 : 0);
        return 0;
    }    

    typedef struct ConstPair {
        const char *name;
        GLint val;
    } ConstPairs;

    static const struct ConstPair consts[] = {
        {"DOUBLE", GLUT_DOUBLE},
        {"DEPTH", GLUT_DEPTH},
        {"RGB", GLUT_RGB},
        {"RGBA", GLUT_RGBA},
        {"KEY_REPEAT_OFF", GLUT_KEY_REPEAT_OFF}
    };

    static void AddConstsGLUT(lua_State *L)
    {
        const int count = sizeof(consts) / sizeof(consts[0]);
        for (int i = 0; i < count; i++) 
        {
            const struct ConstPair val = consts[i];
            lua_pushstring(L, val.name);
            lua_pushinteger(L, val.val);
            lua_settable(L, -3);
        }
    }

    static const struct luaL_Reg glut[] = {
        {"init", initGLUT},
        {"initWindowSize", initWindowSizeGLUT},
        {"initWindowPosition", initWindowPositionGLUT},
        {"initDisplayMode", initDisplayModeGLUT},
        {"createWindow", createWindowGLUT},
        {"display", displayFuncGLUT},
        {"passiveMotion", passiveMotionFuncGLUT},
        {"mouse", mouseFuncGLUT},
        {"mouseWheel", mouseWheelFuncGLUT},
        {"motion", motionFuncGLUT},
        {"idle", idleFuncGLUT},
        {"keyboard", keyboardFuncGLUT},
        {"keyboardUp", keyboardUpFuncGLUT},
        {"special", specialFuncGLUT},
        {"specialUp", specialUpFuncGLUT},
        {"reshape", reshapeFuncGLUT},
        {"timer", timerFuncGLUT},
        {"mainLoop", mainLoopGLUT},
        {"postRedisplay", postRedisplayGLUT},
        {"swapBuffers", swapBuffersGLUT},
        {"setKeyRepeat", setKeyRepeatGLUT},
        {"ignoreKeyRepeat", ignoreKeyRepeatGLUT},
        {NULL, NULL} /* sentinel */
    };

    //name of this function is not flexible
    LIBRARY_API int luaopen_glut(lua_State *L)
    {
        global_L = L;
        luaL_newlib(L, glut);
        AddConstsGLUT(L);
        return 1;
    }

#ifdef __cplusplus
}
#endif
