make_plugin_project ("peggy2000vst", "SharedLib", false)

defines { "XPEGGY_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

