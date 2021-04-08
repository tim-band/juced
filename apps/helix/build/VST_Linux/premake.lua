make_plugin_project ("helixvst", "SharedLib", false)

defines { "HELIX_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.c",
    "../../src/**.cpp"
}

