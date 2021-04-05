
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("nekobee", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
