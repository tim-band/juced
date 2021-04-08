
make_plugin_project ("capsaicinvst", "SharedLib", false)

defines { "XSYNTH_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.c",
    "../../src/**.cpp"
}

