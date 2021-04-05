
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("helixvst", "SharedLib", true, false)

defines { "HELIX_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.c",
    "../../src/**.cpp"
}

