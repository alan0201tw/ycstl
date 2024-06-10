workspace "ycstl"
    architecture "x64"
    startproject "ycstl"
    toolset "clang"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
testoutputdir = "tests"

project "ycstl"
    location "."
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/**.hpp",
        "src/**.cpp"
    }

    includedirs { "include" }

    libdirs {}

    filter "system:linux"
        cppdialect "C++20"
        systemversion "latest"

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"

        defines
        {
            "PLATFORM_WINDOWS",
            "_USE_MATH_DEFINES"
        }

    filter { "configurations:Debug" }
        symbols "On"

    filter { "configurations:Release" }
        optimize "On"

project "gtest"
    language "C++"
    kind "StaticLib"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs
    {
        "vendor/googletest/googletest/",
        "vendor/googletest/googletest/include"
    }

    files
    {
        "vendor/googletest/googletest/src/**.h",
        "vendor/googletest/googletest/src/gtest-all.cc",
    }

project "gtest_main"
    language "C++"
    kind "StaticLib"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs
    {
        "vendor/googletest/googletest/",
        "vendor/googletest/googletest/include"
    }

    files
    {
        "vendor/googletest/googletest/src/gtest_main.cc",
    }

    links { "gtest" }

function create_test_project(name)
    project (path.getbasename(name))
        -- location "ycstl-test"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("bin/" .. testoutputdir .. "/%{prj.basename}")
        objdir ("bin-int/" .. testoutputdir .. "/%{prj.basename}")

        files { (name) }

        includedirs
        {
            "vendor/googletest/googletest/include",
            "ycstl"
        }

        links
        {
            "ycstl",
            "gtest",
            "gtest_main"
        }

        filter { "configurations:Debug" }
            symbols "On"

        filter { "configurations:Release" }
            optimize "On"
end

test_src_files = os.matchfiles("ycstl-test/**.cpp")
for i, file in pairs(test_src_files) do
    create_test_project(file)
end

newaction {
    trigger = "run-tests",
    description = "Export project information as Lua tables",

    execute = function()
        -- Ref: https://www.lua.org/manual/5.4/manual.html#pdf-os.execute
        local exit = os.execute("wsl --exec make")
        print(exit)
        if (true == exit)
        then
            testcases = os.matchfiles("bin/**/test*")
            for i, testcase in pairs(testcases) do
                os.execute("wsl --exec " .. testcase)
            end
        end
    end
}
