workspace "UrbanEngine"
    architecture "x86_64"
    configurations {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "UrbanEngine"
    location "UrbanEngine"
    kind "StaticLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.h"
    }

    includedirs {
        "UrbanEngine/src"
    }

    filter "configurations:Debug"
        defines "URBAN_DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "URBAN_RELEASE"
        optimize "On"
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        defines "URBAN_PLATFORM_WINDOWS"

project "TestApp"
    location "TestApp"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.h"
    }

    includedirs {
        "UrbanEngine/src",
        "%{prj.name}/src"
    }

    links {
        "UrbanEngine"
    }

    filter "configurations:Debug"
        symbols "On"
    filter "configurations:Release"
        optimize "On"

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
