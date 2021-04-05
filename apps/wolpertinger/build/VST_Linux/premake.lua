
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("wolpertingervst", "SharedLib", true, false)

defines { "XWOLPERTINGER_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

