# src/main/BUILD
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "game_app",
    srcs = [
        "main.cc",
    ],
    linkopts = [
        "-framework", "OpenGL",
    ],
    deps = [
        "//src/core",
        "//src/ecs",
        "//src/engine",
        "//src/math",
        "//src/platform",
        "//src/subsystems/input",
        "//src/subsystems/renderer",
        "@homebrew_sdl2//:sdl2",
    ],
)
