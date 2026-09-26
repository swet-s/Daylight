project "Daylight"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp", "vendor/imgui/*.h", "vendor/imgui/*.cpp" }

   includedirs
   {
      "vendor/imgui",
      "%{IncludeDir.GLFW}",
      "vendor/glm",
      "vendor/stb_image",

      "src",

      "%{IncludeDir.VulkanSDK}",
   }

   libdirs { "%{LibraryDir.VulkanSDK}" }

   links
   {
       "GLFW",
       "%{Library.Vulkan}"
   }

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "WL_PLATFORM_WINDOWS" }

   filter "system:macosx"
      defines { "WL_PLATFORM_MACOS" }
      linkoptions { "-Wl,-rpath,%{LibraryDir.VulkanSDK}" }
      links
      {
         "Cocoa.framework",
         "IOKit.framework",
         "CoreVideo.framework",
         "QuartzCore.framework"
      }

   filter "configurations:Debug"
      defines { "WL_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "WL_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      kind "WindowedApp"
      defines { "WL_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"