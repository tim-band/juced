
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("drumsynthvst", "SharedLib", true, false)

defines { "XDRUMSYNTH_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
