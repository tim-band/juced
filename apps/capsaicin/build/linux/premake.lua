
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("capsaicin", "WindowedApp", true, false)

files {
    "../../src/**.h",
    "../../src/**.c",
    "../../src/**.cpp"
}
