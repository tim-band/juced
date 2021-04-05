
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("peggy2000", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
