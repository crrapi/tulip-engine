// src/subsystems/scripting/scripting.cc
#include "scripting.h"
#include "src/core/logging.h"
#include <fstream>
#include <sstream>

namespace Scripting
{

    static ScriptingSystem gScriptingSystem;

    ScriptingSystem::ScriptingSystem()
        : mInitialized(false), mLuaState(nullptr)
    {
    }

    ScriptingSystem::~ScriptingSystem()
    {
        if (mInitialized)
        {
            Shutdown();
        }
    }

    bool ScriptingSystem::Initialize()
    {
        Core::Logging::Log("[Scripting] Initializing Lua Scripting System...");

        mLuaState = luaL_newstate();
        if (!mLuaState)
        {
            Core::Logging::Log("[Scripting] Failed to create Lua state.", Core::LogLevel::ERROR);
            return false;
        }

        luaL_openlibs(mLuaState); // Open standard libraries

        mInitialized = true;
        Core::Logging::Log("[Scripting] Lua Scripting System initialized successfully.");
        return true;
    }

    void ScriptingSystem::Update(float deltaTime)
    {
        if (!mInitialized || !mLuaState)
            return;

        // Example: Call a Lua function named "Update" if it exists
        lua_getglobal(mLuaState, "Update");
        if (lua_isfunction(mLuaState, -1))
        {
            lua_pushnumber(mLuaState, deltaTime);
            if (lua_pcall(mLuaState, 1, 0, 0) != LUA_OK)
            {
                Core::Logging::Log("[Scripting] Lua Error: " + std::string(lua_tostring(mLuaState, -1)), Core::LogLevel::ERROR);
                lua_pop(mLuaState, 1); // Remove error message
            }
        }
        else
        {
            lua_pop(mLuaState, 1); // Remove non-function
        }

        Core::Logging::Log("[Scripting] Scripting System updated.");
    }

    bool ScriptingSystem::ExecuteScript(const std::string &scriptPath)
    {
        if (!mInitialized || !mLuaState)
            return false;

        Core::Logging::Log("[Scripting] Executing Lua script: " + scriptPath);
        if (luaL_dofile(mLuaState, scriptPath.c_str()) != LUA_OK)
        {
            Core::Logging::Log("[Scripting] Lua Error: " + std::string(lua_tostring(mLuaState, -1)), Core::LogLevel::ERROR);
            lua_pop(mLuaState, 1); // Remove error message
            return false;
        }

        Core::Logging::Log("[Scripting] Lua script executed successfully.");
        return true;
    }

    void ScriptingSystem::Shutdown()
    {
        Core::Logging::Log("[Scripting] Shutting down Lua Scripting System...");

        if (mLuaState)
        {
            lua_close(mLuaState);
            mLuaState = nullptr;
        }

        mInitialized = false;
        Core::Logging::Log("[Scripting] Lua Scripting System shutdown complete.");
    }

    ScriptingSystem &Get()
    {
        return gScriptingSystem;
    }

} // namespace Scripting
