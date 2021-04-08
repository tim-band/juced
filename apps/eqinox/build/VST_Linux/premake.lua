make_plugin_project ("eqinoxvst", "SharedLib", false)
defines { "XEQ_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
