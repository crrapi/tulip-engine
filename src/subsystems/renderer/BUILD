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
    linkopts = ["-lGL"],  # Adjust based on platform
    deps = [
        "//src/core",
        "//src/math",
        "@SDL2//:sdl2",  # For OpenGL context via SDL2
        "@glad//:glad_lib",  # Assuming you're using GLAD for OpenGL loading
    ],
)
