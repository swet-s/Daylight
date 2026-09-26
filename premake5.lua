-- premake5.lua
workspace "Daylight"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Daylight"

filter "system:macosx"
   architecture "arm64"
filter {}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Dependencies.lua"

group "Dependencies"
   include "Daylight/vendor/GLFW"
group ""

include "Daylight"