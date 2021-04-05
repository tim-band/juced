
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("notemap", "SharedLib", true, false)

files {
    "../../../../wrapper/*.h",
    "../../../../wrapper/*.cpp",
    "../../../../wrapper/formats/VST/*.cpp",
    "../../src/**.h",
    "../../src/**.cpp"
}
