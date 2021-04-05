
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("dubdelay", "SharedLib", true, false)

defines { "XDUBDELAY_VST_PLUGIN=1" }

files {
    "../../src/*.h",
    "../../src/*.cpp"
}
