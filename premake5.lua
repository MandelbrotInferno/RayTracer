workspace "RayTracer"
	configurations{"Debug", "Release"}
	platforms{"x64"}

project "RayTracer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"


	vpaths {
        ["src/**"] = { "src/**.cpp" },
        ["include/**"] = { "include/**.h", "include/**.hpp" },
    }

	files{"include/**.hpp", 
		  "include/**.h",
		  "src/**.c",
		  "src/**.cpp"}
		  
	targetdir "x64/%{cfg.buildcfg}"
	objdir ("bin-intermediate/%{cfg.buildcfg}")
	includedirs{"include/"}
	libdirs{}
	links{}
	
	postbuildcommands {}

	filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

	filter "toolset:gcc or toolset:clang"
		buildoptions { "-Wall", "-Wextra", "-Werror" }

	filter "toolset:msc"
		buildoptions { "/W4 /WX" }

	