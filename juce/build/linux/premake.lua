make_library_project ("juce")

files {
    "../../src/*.h",
    "../../src/core/**.cpp",
    "../../src/core/**.h",
    "../../src/cryptography/**.cpp",
    "../../src/cryptography/**.h",
    "../../src/containers/**.cpp",
    "../../src/containers/**.h",
    "../../src/io/**.cpp",
    "../../src/io/**.h",
    "../../src/text/**.cpp",
    "../../src/text/**.h",
    "../../src/threads/**.cpp",
    "../../src/threads/**.h",
    "../../src/application/**.cpp",
    "../../src/application/**.h",
    "../../src/audio/**.cpp",
    "../../src/audio/**.h",
    "../../src/events/**.cpp",
    "../../src/events/**.h",
    "../../src/utilities/**.cpp",
    "../../src/utilities/**.h",
    "../../src/gui/**.cpp",
    "../../src/gui/**.h",
    "../../src/extended/**.cpp",
    "../../src/extended/**.h",
}

configuration { "linux" }
files {
    "../../src/native/linux/**.h", 
    "../../src/native/linux/**.cpp", 
    "../../src/native/juce_linux_NativeCode.cpp"
}

configuration { "windows" }
files {
    "../../src/native/windows/**.h", 
    "../../src/native/windows/**.cpp", 
    "../../src/native/juce_win32_NativeCode.cpp"
}

configuration { "macos" }
files {
    "../../src/native/mac/**.h", 
    "../../src/native/mac/**.cpp", 
    "../../src/native/juce_mac_NativeCode.cpp"
}
