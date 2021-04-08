make_plugin_project ("notemap", "SharedLib", false)

files {
    "../../../../wrapper/*.h",
    "../../../../wrapper/*.cpp",
    "../../../../wrapper/formats/VST/*.cpp",
    "../../src/**.h",
    "../../src/**.cpp"
}
