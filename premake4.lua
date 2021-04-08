solution "juced"
configurations { "Debug", "Release", "Release32" }
location "."
dofile "tools/linux/premake.lua"
dofile "juce/build/linux/premake.lua"
dofile "tests/build/linux/premake.lua"
apps = os.matchdirs("apps/*")
types = { "linux/premake.lua", "VST_Linux/premake.lua" }
for k,v in pairs(apps) do
    if os.isdir(v .. "/build") then
        for k0, t in pairs(types) do
            f = v .. "/build/" .. t
            if os.isfile(f) then
                dofile(f)
            end
        end
    end
end
