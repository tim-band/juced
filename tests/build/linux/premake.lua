make_plugin_project ("unit_testing", "ConsoleApp", "../../../bin/")

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

links { "cpptest" }
