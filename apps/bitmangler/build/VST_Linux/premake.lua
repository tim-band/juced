make_plugin_project ("bitmanglervst", "SharedLib", false)

defines { "XBITMANGLER_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
