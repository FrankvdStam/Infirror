project "simulator"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir	  ("obj/" .. outputdir .. "/%{prj.name}")
		
	files
	{
		"src/**.h",
		"src/**.cpp",
	}
	
	includedirs
	{
		"src",
		"libraries/glfw/include",
        "libraries/glad/include",
        "libraries/imgui",
	}

	links
	{
		"glfw",
		"glad",
		"imgui",
	}    	

	defines
	{
		"GLFW_INCLUDE_NONE",
	}

	
	filter "system:linux"
		cppdialect "C++11"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"SIMULATOR_LINUX"
		}

		links
		{
			"dl",
			"pthread",
			"Xrandr",
			"Xi",
			"X11",

		}		

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		links
		{
			"opengl32.lib"
		}
		
		defines
		{
			"SIMULATOR_WINDOWS"
		}
		
	filter {"system:windows", "configurations:Debug"}
		buildoptions "/MTd"
		
	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"
		
	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"
		
		
