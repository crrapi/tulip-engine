# src/subsystems/networking/BUILD
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "networking",
    srcs = [
        "network_client.cc",
        "network_server.cc",
    ],
    hdrs = [
        "network_client.h",
        "network_server.h",
    ],
    linkopts = ["-lenet"],
    deps = [
        "//src/core",
        "@enet//:enet_lib",  # Adjust based on your ENet integration
    ],
)
