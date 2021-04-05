
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("soundcrab", "WindowedApp", true, false)

includedirs { "../../src", "../../src/Synth" }

defines { "HAVE_CONFIG_H=1" }

files {
    "../../src/**.h",
    "../../src/**.c",
    "../../src/**.cpp"
}
