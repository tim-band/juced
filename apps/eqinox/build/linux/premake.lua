
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("eqinox", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
