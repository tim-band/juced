make_plugin_project ("kombat", "SharedLib", false)

includedirs { "../../src" }

files {
    "../../../../wrapper/*.h",
    "../../../../wrapper/*.cpp",
    "../../../../wrapper/formats/VST/*.cpp",
    "../../src/**.h",
    "../../src/**.cpp"
}

