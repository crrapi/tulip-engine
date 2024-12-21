# src/main/BUILD
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "game_app",
    srcs = [
        "main.cc",
    ],
    linkopts = [
        "-lSDL2",
        "-lGL",
        "-lbullet3",
        "-lfmod",
        "-lenet",
        "-llua",
    ],
    deps = [
        "//src/core",
        "//src/ecs",
        "//src/engine",
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
