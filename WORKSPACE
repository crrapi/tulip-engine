# WORKSPACE
workspace(name = "tulip")

# External libraries are provided by the host system (e.g., Homebrew on macOS).

# Homebrew SDL2 repository (macOS). If SDL2 is installed via Homebrew, this
# exposes headers and link flags to Bazel in a sandbox-friendly way.
new_local_repository(
    name = "homebrew_sdl2",
    path = "/opt/homebrew/opt/sdl2",
    build_file_content = 
        """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "sdl2",
    hdrs = glob(["include/SDL2/**"]),
    includes = ["include/SDL2"],
    linkopts = ["-L/opt/homebrew/opt/sdl2/lib", "-lSDL2"],
)
""",
)
