make_plugin_project ("drumsynthvst", "SharedLib", false)

defines { "XDRUMSYNTH_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
