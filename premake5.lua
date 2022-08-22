-- premake5.lua
workspace "Daylight"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Daylight"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "Daylight"