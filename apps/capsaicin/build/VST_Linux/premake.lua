
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("capsaicinvst", "SharedLib", true, false)

defines { "XSYNTH_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.c",
    "../../src/**.cpp"
}

