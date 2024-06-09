workspace "ycstl"
    architecture "x64"
    startproject "ycstl"

    configurations
    {
        "Debug",
        "Release"
    }

-- variables
    -- cfg - configuration
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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

    includedirs
    {
        "include",
    }

    libdirs
    {
    }

    filter "system:linux"
        cppdialect "C++20"
        systemversion "latest"
        toolset "clang"

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

project "ycstl-test"
    location "ycstl-test"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "vendor/googletest/googletest/include/gtest/**.h",
        "vendor/googletest/googletest/src/gtest-all.cc",
        "vendor/googletest/googletest/src/gtest_main.cc",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "vendor/googletest/googletest/include/gtest",
        "vendor/googletest/googletest/include",
        "vendor/googletest/googletest"
    }

    links
    {
        "ycstl",
        "gtest"
    }

    filter { "configurations:Debug" }
        symbols "On"

    filter { "configurations:Release" }
        optimize "On"
