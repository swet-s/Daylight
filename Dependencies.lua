VULKAN_SDK = os.getenv("VULKAN_SDK")

if os.target() == "macosx" and not VULKAN_SDK then
   -- Homebrew: brew install vulkan-headers vulkan-loader molten-vk
   VULKAN_SDK = os.isdir("/opt/homebrew") and "/opt/homebrew" or "/usr/local"
end

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Daylight/vendor/GLFW/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/lib"

Library = {}
Library["Vulkan"] = os.target() == "windows" and "vulkan-1" or "vulkan"
