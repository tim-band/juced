make_plugin_project ("monitor", "SharedLib", false)

files {
    "../../../../wrapper/*.h",
    "../../../../wrapper/*.cpp",
    "../../../../wrapper/formats/VST/*.cpp",
    "../../src/**.h",
    "../../src/**.cpp"
}

