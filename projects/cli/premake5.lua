project "cli"
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
	}
	
	links
	{
	}    	

	defines
	{
	}

	
	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
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
		
		
