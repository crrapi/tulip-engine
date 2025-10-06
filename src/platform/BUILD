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
        "-framework", "OpenGL",
    ],
    deps = [
        "//src/core",
        "@homebrew_sdl2//:sdl2",
    ],
)
