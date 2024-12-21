# src/subsystems/physics/BUILD
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "physics",
    srcs = [
        "physics.cc",
    ],
    hdrs = [
        "physics.h",
    ],
    linkopts = ["-lbullet3"],
    deps = [
        "//src/core",
        "//src/math",
        "@bullet3//:bullet_lib",  # Adjust based on your Bullet integration
    ],
)
