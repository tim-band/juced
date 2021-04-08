make_plugin_project ("soundcrab", "WindowedApp", false)

includedirs { "../../src", "../../src/Synth" }

defines { "HAVE_CONFIG_H=1" }

files {
    "../../src/**.h",
    "../../src/**.c",
    "../../src/**.cpp"
}
