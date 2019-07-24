project "infirror_lib"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir	  ("obj/" .. outputdir .. "/%{prj.name}")
		
	files
	{
		"src/**.h",
		"src/**.cpp",
		"include/**.h",
		"include/**.cpp",
	}
	
	includedirs
	{
		"include/",
	}
	
	filter {"system:windows", "configurations:Debug"}
		buildoptions "/MTd"
		
	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"
