workspace "Infirror"
	startproject "simulator"
    toolset "clang"
	
	configurations
	{
		"Debug",
		"Release",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "graphics"
	include "projects/simulator/libraries/glfw/"
	include "projects/simulator/libraries/glad/"
	include "projects/simulator/libraries/imgui/"
	
group "desktop"
	include "projects/simulator/"
	include "projects/cli/"

group "arduino"
--include "projects/infirror/"

group ""
	include "projects/infirror/src/infirror_lib/"

