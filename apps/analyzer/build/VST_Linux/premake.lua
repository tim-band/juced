
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("analyzervst", "SharedLib", true, false)

defines { "XANALYZER_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

