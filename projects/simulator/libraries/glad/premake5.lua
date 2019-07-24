project "glad"
    kind "StaticLib"
    language "C"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/glad.c"
	}
    
	includedirs
	{
		"include"
	}
	
	
	filter "system:windows"
        systemversion "latest"
        staticruntime "On"

	filter {"system:windows", "configurations:Debug"}
		buildoptions "/MTd"
		
	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"