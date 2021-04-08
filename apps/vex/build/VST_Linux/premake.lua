make_plugin_project ("vexvst", "SharedLib", false)

defines { "XVEX_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

