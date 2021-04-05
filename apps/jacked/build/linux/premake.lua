
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("jacked", "WindowedApp", true, false)

includedirs { "../../src" }
links { "jack" }

files {
        "../../src/**.h",
        "../../src/**.cpp"
}

