
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("kombat", "SharedLib", true, false)

includedirs { "../../src" }

files {
    "../../../../wrapper/*.h",
    "../../../../wrapper/*.cpp",
    "../../../../wrapper/formats/VST/*.cpp",
    "../../src/**.h",
    "../../src/**.cpp"
}

