
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("tal-filtervst", "SharedLib", true, false)

includedirs { "../../src" }

defines { "XTALFILTER_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

