# src/engine/BUILD
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "engine",
    srcs = ["engine.cc"],
    hdrs = ["engine.h"],
    deps = [
        "//src/core",
        "//src/ecs",
        "//src/math",
        "//src/platform",
        "//src/resources",
        "//src/subsystems/ai",
        "//src/subsystems/audio",
        "//src/subsystems/input",
        "//src/subsystems/networking",
        "//src/subsystems/physics",
        "//src/subsystems/renderer",
        "//src/subsystems/scripting",
        "//src/subsystems/tools",
    ],
)
