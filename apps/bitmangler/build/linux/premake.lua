
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("bitmangler", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
