
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("HybridReverb2", "exe", true, false)

package.includepaths = { 
    "/usr/include",
    "/usr/include/freetype2",
    "../../src",
    "../../../../juce",
    "../../../../vst/vstsdk2.4",
    "../../../../juce/extras/audio\ plugins",
    "../../../../juce/extras/audio\ plugins/wrapper"
}

package.libpaths = { 
    "/usr/X11R6/lib/",
    "../../../../bin/"
}

package.config["Debug"].links = { 
    "juce_debug", "freetype", "pthread", "rt", "X11", "GL", "GLU", "Xinerama", "asound", "m", "gomp"
}

package.config["Release"].links = { 
    "juce", "freetype", "pthread", "rt", "X11", "GL", "GLU", "Xinerama", "asound", "m", "gomp"
}

package.config["Debug"].buildoptions = {
" -O0 -march=pentium3 -fopenmp",
" `pkg-config fftw3f --cflags`"
}

package.config["Release"].buildoptions = {
" -O2 -march=pentium3 -fomit-frame-pointer -funroll-loops -fopenmp",
" `pkg-config fftw3f --cflags`"
}

package.linkoptions = {
"`pkg-config fftw3f --libs`"
}

package.linkflags = { "static-runtime" }

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    ),
    matchfiles (
        "../../src/libHybridConv/*.c"
    )
}
