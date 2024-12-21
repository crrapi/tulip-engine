// src/subsystems/scripting/scripting.h
#pragma once
#include <lua.hpp>
#include <string>

namespace Scripting
{

    class ScriptingSystem
    {
    public:
        ScriptingSystem();
        ~ScriptingSystem();

        bool Initialize();
        void Update(float deltaTime);
        void Shutdown();

        // Example method to execute a Lua script
        bool ExecuteScript(const std::string &scriptPath);

    private:
        bool mInitialized;
        lua_State *mLuaState;
    };

    // Global accessor
    ScriptingSystem &Get();

} // namespace Scripting
