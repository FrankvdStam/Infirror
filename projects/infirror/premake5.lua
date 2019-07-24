project "infirror"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir	  ("obj/" .. outputdir .. "/%{prj.name}")
		
	files
	{
		"*.h",
		"*.cpp",
		"*.ino",
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
