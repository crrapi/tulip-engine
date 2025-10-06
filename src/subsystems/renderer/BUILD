# src/subsystems/renderer/BUILD
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "renderer",
    srcs = [
        "material.cc",
        "mesh.cc",
        "renderer.cc",
        "scene.cc",
        "shader.cc",
    ],
    hdrs = [
        "material.h",
        "mesh.h",
        "renderer.h",
        "scene.h",
        "shader.h",
    ],
    linkopts = [
        "-framework", "OpenGL",
    ],
    deps = [
        "//src/core",
        "//src/math",
        "//src/platform",
        "@homebrew_sdl2//:sdl2",
    ],
)
