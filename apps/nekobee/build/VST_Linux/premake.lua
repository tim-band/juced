make_plugin_project ("nekobeevst", "SharedLib", false)

defines { "XNEKOBEE_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
