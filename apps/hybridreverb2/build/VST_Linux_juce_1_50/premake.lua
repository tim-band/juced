make_plugin_project ("HybridReverb2vst", "SharedLib", false)

defines { "HYBRIDREVERB2_VST_PLUGIN" }

buildoptions {
"`pkg-config fftw3f --cflags`"
}

linkoptions {
"`pkg-config fftw3f --libs`"
}

files {
    "../../src/**.h",
    "../../src/**.cpp",
    "../../src/libHybridConv/*.c"
}
