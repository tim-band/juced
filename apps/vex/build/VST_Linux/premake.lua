
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("vexvst", "SharedLib", true, false)

defines { "XVEX_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

