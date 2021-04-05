
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("vex", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
