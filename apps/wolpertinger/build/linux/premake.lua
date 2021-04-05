
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("wolpertinger", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
