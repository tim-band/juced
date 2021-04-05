
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("jost", "WindowedApp", true, false)
configure_jost_libraries (true)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
