
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("dubdelay", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

