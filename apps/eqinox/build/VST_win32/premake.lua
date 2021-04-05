
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("eqinoxvst", "SharedLib", true, false)
defines { "XEQ_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp",
    "./exports.def"
}

