
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("bitmanglervst", "SharedLib", true, false)

defines { "XBITMANGLER_VST_PLUGIN=1" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}
