make_plugin_project ("jostvst", "SharedLib", false)
configure_jost_libraries (false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

