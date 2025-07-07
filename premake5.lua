workspace "RayTracer"
	configurations{"Debug", "Release"}
	platforms{"x64"}

project "RayTracer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"


	vpaths {
		["deps/**"] = {"dependencies/**.h", "dependencies/**.hpp", "dependencies/**.c", "dependencies/**.cpp"},
        ["src/**"] = { "src/**.cpp" },
        ["include/**"] = { "include/**.h", "include/**.hpp" },
    }

	files{"include/**.hpp", 
		  "include/**.h",
		  "src/**.c",
		  "src/**.cpp",
		  "dependencies/glm/**.h",
		  "dependencies/glm/**.hpp",
		  }
		  
	targetdir "x64/%{cfg.buildcfg}"
	objdir ("bin-intermediate/%{cfg.buildcfg}")
	includedirs{"include/"}
	libdirs{"dependencies/glm/"}
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

	