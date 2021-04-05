
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("analyzer", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.cc",
    "../../src/**.cpp"
}

