make_plugin_project ("analyzervst", "SharedLib", false)

defines { "XANALYZER_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

