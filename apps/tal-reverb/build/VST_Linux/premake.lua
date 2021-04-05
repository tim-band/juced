
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("tal-reverbvst", "SharedLib", true, false)

defines { "XTALREVERB_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

