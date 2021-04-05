
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("nekobeevst", "SharedLib", true, false)

defines { "XNEKOBEE_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
