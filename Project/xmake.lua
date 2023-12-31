-- define project
set_project("MyProject")
set_xmakever("2.6.1")
set_version("1.0.0", {build = "%Y%m%d%H%M"})

-- set common flags
set_warnings("all", "error")
set_languages("c99")
add_cxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing", "-Wno-error=expansion-to-defined")
add_mxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing", "-Wno-error=expansion-to-defined")

-- add build modes
add_rules("mode.release", "mode.debug")

-- includes sub-projects
includes("log")

target("app")
    set_kind("binary")
    add_includedirs("./log/src/")
    add_files("./main/main.c")
    add_deps("log")
    add_deps("log")
   