# src/subsystems/scripting/BUILD
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "scripting",
    srcs = [
        "scripting.cc",
    ],
    hdrs = [
        "scripting.h",
    ],
    linkopts = ["-llua"],
    deps = [
        "//src/core",
        "@lua//:lua_lib",  # Adjust based on your Lua integration
    ],
)
