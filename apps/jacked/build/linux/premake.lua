make_plugin_project ("jacked", "WindowedApp", false)

includedirs { "../../src" }
links { "jack" }

files {
        "../../src/**.h",
        "../../src/**.cpp"
}

