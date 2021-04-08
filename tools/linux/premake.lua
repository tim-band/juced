
--======================================================================================
-- Premake5 constructs are commented out and followed (if applicable) by their Premake4 equivalents
function make_library_project (name) 

    print ("==== Configuring " .. name .. " ====")
    print ("Configuring GNU makefiles:")

    solution "juced"
    project (name)
    location "."
    configuration {}
    kind "StaticLib"
    links { "dl", "lo", "sndfile", "libcpptest", "samplerate" }
    -- also install: dssi-dev

    generic_configuration(name, false)
    configure_standard_options (false)
    configuration {}
    buildoptions { "`pkg-config --cflags Qt5Widgets`" }
    linkoptions { "`pkg-config --libs Qt5Widgets`" }
end

function generic_configuration(name, basedir)

    configuration {}
        if not basedir then
            basedir = "../../../bin/"
        end
        language "c++"

        targetname (name)
        objdir (basedir .. "intermediate/" .. name)

    --filter { "system:linux" }
    configuration "linux"
        targetdir (basedir .. "linux")
        libdirs { basedir .. "linux" }
        buildoptions { "-fPIC" }

    --filter { "system:windows" }
    configuration "windows"
        defines { "WIN32=1" }
        targetdir (basedir .. "windows")
        libdirs { basedir .. "windows" }

    --filter { "system:macosx" }
    configuration "macosx"
        targetdir (basedir .. "macosx")
        libdirs { basedir .. "macosx" }

    --filter { "configurations:Debug or Release" }
        --architecture "x86_64"

    --filter { "configurations:Release32" }
    configuration "*32"
        --architecture "x86"
        targetsuffix "32"

    --filter { "configurations:Debug" }
    configuration "Debug"
        targetsuffix "_debug"
        defines { "DEBUG=1", "_DEBUG=1" }
        --symbols "On"
        flags { "Symbols" }

    --filter { "configurations:Release*" }
    configuration "Release"
        defines { "NDEBUG=1" }
        --optimize "On"
        flags { "NoFramePointer", "OptimizeSpeed" }
        --visibility { "Hidden" }
    --configuration { "Release", "gcc" }
        --buildoptions { "-fvisibility=hidden" }
    end

--======================================================================================
function make_plugin_project (name, kind_, libpath) 

    print ("==== Configuring " .. name .. " ====")
    print ("Configuring GNU makefiles:")

    solution "juced"
    project (name)
    location "."
    targetname (name)
    kind (kind_)
    
    generic_configuration(name, libpath)
    configure_standard_options (true)
    configuration {}
end

--======================================================================================
function configure_standard_options (link_with_libraries)

    configuration {}

    newoption {
        trigger = "vstsdk-version",
        description = "Specify version of VSTSDK (default 2.4)",
        value = "VERSION",
        allowed = { { "2.3", "VST SDK version 2.3" }, { "2.4", "VST SDK version 2.4" } },
        default = "2.4"
    }
    configure_vst_sdk ()

    includedirs {
        "../../src",
        "../../../../juce",
        "../../../../juce/src",
        "../../../../juce/extras/audio plugins"
    }
    flags { "NoPCH", "NoEditAndContinue", "ExtraWarnings" }

    --filter { "configurations:Debug" }
    configuration "Debug"

    flags { "NoPCH" }
    if (link_with_libraries) then
        links { "juce_debug" }
    end

    --filter { "configurations:Release" }
    configuration "Release"

    if (link_with_libraries) then
        links { "juce" }
    end

    --filter { "configurations:Release32" }
    configuration "Release32"

    if (link_with_libraries) then
        links { "juce32" }
    end

    --filter { "action:gmake*" }
    configuration"gmake*"

    newoption {
        trigger = "enable-scripting",
        description = "Disable scripting support (doesn't work)"
    }
    newoption {
        trigger = "disable-alsa",
        description = "Disable ALSA support (this will disable also midi)"
    }
    newoption {
        trigger = "disable-jack",
        description = "Disable jack-audio-connection-kit"
    }
    newoption {
        trigger = "disable-xshm",
        description = "Disable SHM support for Xorg"
    }
    newoption {
        trigger = "enable-opengl",
        description = "enable OpenGL support (default disabled)"
    }
    newoption {
        trigger = "enable-lash",
        description = "Enable LASH support (default disabled)"
    }
    newoption {
        trigger = "enable-xinerama",
        description = "Enable Xinerama support (default disabled)"
    }
    newoption {
        trigger = "enable-glx",
        description = "Enable GLX support for ARGB visuals (default disabled)"
    }
    newoption {
        trigger = "enable-sqlite",
        description = "Enable SQLITE support (default disabled)"
    }

    defines { "LINUX=1" }
    buildoptions { "`pkg-config --cflags freetype2`" }

    links { "rt", "dl", "m", "pthread", "freetype", "X11", "Xext" }

    -- configure step for libraries ---------------------------------------
    configuration { "enable-scripting" }
        defines { "JUCE_SUPPORT_SCRIPTING=1" }
 
    configuration { "gmake*", "not disable-xshm" }
    if (os.isfile ("/usr/include/X11/extensions/XShm.h")) then
        defines { "JUCE_USE_XSHM=1" }
        if link_with_libraries then
        end
    end

    configuration { "gmake*", "enable-xinerama" }
    if (os.findlib ("Xinerama")) then
        defines { "JUCE_USE_XINERAMA=1" }
        if link_with_libraries then
        end
    end

    configuration { "gmake*", "enable-opengl or enable-glx" }
    if (os.findlib ("GL") and os.findlib ("GLU")) then
        defines { "JUCE_OPENGL=1" }
        if link_with_libraries then
            links { "GL", "GLU" }
        end        

        configuration { "gmake*", "enable-glx" }
        defines { "JUCE_USE_GLX=1" }
        if link_with_libraries then
            links { "Xrender", "Xi" }
        end
    end

    configuration { "gmake*", "enable-sqlite" }
    if (os.findlib ("sqlite3")) then
        defines { "JUCE_SUPPORT_SQLITE=1" }
        if link_with_libraries then
            links { "sqlite3" }
        end
    end

    -- enable these only if we are in standalone mode
    configuration { "gmake*", "not disable-alsa", "not SharedLib" }
    if (os.isfile ("/usr/include/alsa/asoundlib.h")
        and os.findlib ("asound")) then
        defines { "JUCE_ALSA=1" }
        if link_with_libraries then
            links { "asound" }
        end
    end

    configuration { "gmake*", "not disable-jack", "not SharedLib" }
    if (os.findlib ("jack")) then
        defines { "JUCE_JACK=1" }
        if link_with_libraries then
            links { "jack" }
        end
    end

    configuration { "gmake*", "enable-lash", "not SharedLib" }
    if (os.isfile ("/usr/include/lash-1.0/lash/lash.h")
        and os.findlib ("lash")) then
        defines { "JUCE_LASH=1" }
        includedirs { "/usr/include/lash-1.0" }
        if link_with_libraries then
            links { "lash" }
        end
    end
end

--======================================================================================
function configure_jost_libraries (standalone)

    newoption {
        trigger = "disable-vst",
        description = "Disable VST support"
    }
    -- newoption {trigger="enable-surface", description="Enable surface component in debug mode (Disabled)"}

    if (not standalone) then
        defines { "JOST_VST_PLUGIN=1" }
    end

    configuration { "not disable-vst" }
        defines { "JOST_USE_VST=1" }
    configuration { "disable-vst" }
        defines { "JOST_USE_VST=0" }

    --filter { "system:linux" }
    configuration "linux"

        newoption {
            trigger="disable-ladspa",
            description="Disable LADSPA support"
        }
        newoption {
            trigger="disable-dssi",
            description="Disable DSSI support"
        }
        newoption {
            trigger="enable-jackbridge",
            description="Enable jack-audio-connection-kit 32/64 bit bridge (Disabled)"
        }

    configuration { "linux", "not disable-ladspa" }
        if (os.isfile ("/usr/include/ladspa.h")) then
            defines { "JOST_USE_LADSPA=1" }
            print ("...enabled LADSPA support")
        else
            defines { "JOST_USE_LADSPA=0" }
        end

    configuration { "linux", "not disable-dssi" }
        if (os.isfile ("/usr/include/dssi.h")) then
            defines { "JOST_USE_DSSI=1" }
            print ("...enabled DSSI support")
        else
            defines { "JOST_USE_DSSI=0" }
        end

    configuration { "enable-jackbridge" }
        defines { "JOST_USE_JACKBRIDGE=1" }
    configuration { "not enable-jackbridge" }
        defines { "JOST_USE_JACKBRIDGE=0" }
    
    configuration {}
end

--======================================================================================
function configure_vst_sdk ()

    configuration "vstsdk-version=2.3"
        defines { "JUCE_USE_VSTSDK_2_4=0" }
        includedirs {
            "../../../../vst/vstsdk2.3",
            "../../../../vst/vstsdk2.3/source/common",
        }
        --filter { "system:linux" }
        configuration { "vstsdk-version=2.3", "linux" }
            includedirs { "/usr/include/vstsdk2.3/source/common", "/usr/include/vst/source/common" }
    configuration "not vstsdk-version=2.3"
        defines { "JUCE_USE_VSTSDK_2_4=1" }
        includedirs {
            "../../../../vst/vstsdk2.4",
            "../../../../vst/vstsdk2.4/public.sdk/source/vst2.x",
        }
        --filter { "system:linux" }
        configuration { "not vstsdk-version=2.3", "linux" }
            includedirs { "/usr/include/vstsdk2.4/public.sdk/source/vst2.x", "/usr/include/vst/public.sdk/source/vst2.x" }
    configuration {}
end
