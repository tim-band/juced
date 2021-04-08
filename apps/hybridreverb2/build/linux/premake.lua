make_plugin_project ("HybridReverb2", "WindowedApp", false)

includedirs { 
    "/usr/include",
    "/usr/include/freetype2",
    "../../src",
    "../../../../juce",
    "../../../../vst/vstsdk2.4",
    "../../../../juce/extras/audio\ plugins",
    "../../../../juce/extras/audio\ plugins/wrapper"
}

configuration { "Debug" }

links { 
    "juce_debug", "freetype", "pthread", "rt", "X11", "GL", "GLU", "Xinerama", "asound", "m", "gomp"
}

buildoptions {
    " -O0 -fopenmp",
    " `pkg-config fftw3f --cflags`"
}
    
configuration { "Release" }

links { 
    "juce", "freetype", "pthread", "rt", "X11", "GL", "GLU", "Xinerama", "asound", "m", "gomp"
}

buildoptions {
" -O2 -fomit-frame-pointer -funroll-loops -fopenmp",
" `pkg-config fftw3f --cflags`"
}

configuration {}

linkoptions {
"`pkg-config fftw3f --libs`"
}

flags { "StaticRuntime" }

files {
    "../../src/**.h",
    "../../src/**.cpp",
    "../../src/libHybridConv/*.c"
}
