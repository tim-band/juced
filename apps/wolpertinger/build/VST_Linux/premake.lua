make_plugin_project ("wolpertingervst", "SharedLib", false)

defines { "XWOLPERTINGER_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

