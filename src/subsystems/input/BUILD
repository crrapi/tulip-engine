# src/subsystems/input/BUILD
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "input",
    srcs = [
        "input.cc",
    ],
    hdrs = [
        "input.h",
    ],
    linkopts = ["-lSDL2"],
    deps = [
        "//src/core",
        "@SDL2//:sdl2",
    ],
)
