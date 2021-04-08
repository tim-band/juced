make_plugin_project ("dubdelay", "SharedLib", false)

defines { "XDUBDELAY_VST_PLUGIN=1" }

files {
    "../../src/*.h",
    "../../src/*.cpp"
}
