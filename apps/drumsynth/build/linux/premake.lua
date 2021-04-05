dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("drumsynth", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
