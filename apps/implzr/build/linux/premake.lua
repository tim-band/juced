make_plugin_project ("implzr", "WindowedApp", false)

defines { "LIBFV3_FLOAT=1", "LIBSRATE2_FLOAT=1" }
links { "fftw3f" }

files {
    "../../src/**.h",
    "../../src/**.hpp",
    "../../src/**.c",
    "../../src/**.cpp"
}

