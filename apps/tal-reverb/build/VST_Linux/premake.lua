make_plugin_project ("tal-reverbvst", "SharedLib", false)

defines { "XTALREVERB_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

