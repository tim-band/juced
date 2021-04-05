
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("tal-filter", "WindowedApp", true, false)

includedirs { "../../src" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
