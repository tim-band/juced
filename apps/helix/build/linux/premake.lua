
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("helix", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.c",
    "../../src/**.cpp"
}
