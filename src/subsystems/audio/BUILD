# src/subsystems/audio/BUILD
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "audio",
    srcs = [
        "audio.cc",
    ],
    hdrs = [
        "audio.h",
    ],
    linkopts = ["-lfmod"],
    deps = [
        "//src/core",
        "@fmod//:fmod_lib",  # Adjust based on your FMOD integration
    ],
)
