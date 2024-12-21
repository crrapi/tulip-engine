# third_party/BUILD
package(default_visibility = ["//visibility:public"])

# SDL2
filegroup(
    name = "sdl2_headers",
    srcs = glob(["SDL2/include/**/*.h"]),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "sdl2",
    srcs = glob(["SDL2/src/**/*.c"]),
    hdrs = ["@SDL2//:sdl2_headers"],
    copts = ["-Ithird_party/SDL2/include"],
    includes = ["SDL2/include"],
    linkopts = ["-lSDL2"],
    visibility = ["//visibility:public"],
)

# Repeat similar setups for bullet3, fmod, enet, lua
# You need to adjust these based on the actual structure of each third-party library
