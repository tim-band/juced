make_plugin_project ("soundcrabvst", "SharedLib", false)

includedirs { "../../src", "../../src/Synth" }

defines { "HAVE_CONFIG_H=1", "XSOUNDCRAB_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.c",
    "../../src/**.cpp"
}

