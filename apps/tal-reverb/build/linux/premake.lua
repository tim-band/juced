
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("tal-reverb", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
