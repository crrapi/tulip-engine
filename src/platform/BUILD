# src/platform/BUILD
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "platform",
    srcs = [
        "platform.cc",
        "window.cc",
    ],
    hdrs = [
        "platform.h",
        "window.h",
    ],
    linkopts = [
        "-lSDL2",
        "-lGL",
    ],
    deps = [
        "//src/core",
        "@SDL2//:sdl2",
    ],
)
