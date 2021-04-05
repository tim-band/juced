
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("jostvst", "SharedLib", true, false)
configure_jost_libraries (false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

