
dofile ("../../../../tools/linux/premake.lua")

make_plugin_project ("implzr", "SharedLib", true, false)

defines { "LIBFV3_FLOAT=1", "LIBSRATE2_FLOAT=1", "XIMPLZR_VST_PLUGIN=1" }
links { "fftw3f" }

files {
    "../../src/**.h",
    "../../src/**.cpp"
}

