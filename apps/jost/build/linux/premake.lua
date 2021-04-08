make_plugin_project ("jost", "WindowedApp", false)
configure_jost_libraries (true)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
