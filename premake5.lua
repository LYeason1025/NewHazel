workspace "Hazel"
    architecture "x64"
    configurations { "Debug", "Release" ,"Dist"}
   
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


    IncludeDir ={}
    IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
    IncludeDir["Glad"] = "Hazel/vendor/Glad/include"
    IncludeDir["ImGui"] = "Hazel/vendor/imgui"
    IncludeDir["glm"] = "Hazel/vendor/glm"

    include "Hazel/vendor/GLFW"
    include "Hazel/vendor/Glad"
    include "Hazel/vendor/imgui"

project "Hazel"
    location "Hazel"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"	

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   pchheader "hzpch.h"
   pchsource "Hazel/src/hzpch.cpp"

   files { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp",

        "%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.Glad}"
        
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }
    filter "system:windows"
        -- staticruntime "on"
        systemversion "latest"

        defines { "HZ_PLATFORM_WINDOWS", "HZ_BUILD_DLL","GLFW_INCLUDE_NONE",}

    -- postbuildcommands 
    -- {
    --     ( "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
    -- }

    filter "configurations:Debug"
        defines  "HZ_DEBUG" 
        -- buildoptions  "/MDd" 
        runtime "Debug"
        symbols "On"

   filter "configurations:Release"
        defines  "HZ_RELEASE"
        -- buildoptions  "/MD" 
        runtime "Release"
        optimize "On"

   filter "configurations:Dist"
         defines  "HZ_DIST" 
        --  buildoptions "/MD" 
         runtime "Release"
         optimize "On"



project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    cppdialect "C++17"
    language "C++"
    staticruntime "On"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   files { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp" 
    }

    includedirs
    {
        "Hazel/vendor/spdlog/include",
        "Hazel/src",
        "Hazel/vendor",
        "%{IncludeDir.glm}",
    }


    links
    {
        "Hazel",
    }

    filter "system:windows"
        -- staticruntime "On"
        systemversion "latest"

        defines { "HZ_PLATFORM_WINDOWS",}

    filter "configurations:Debug"
        defines { "HZ_DEBUG" }
        -- buildoptions  "/MDd" 
        runtime "Debug"
        symbols "On"


   filter "configurations:Release"
        defines  "HZ_RELEASE" 
        -- buildoptions "/MD" 
        runtime "Release"
        optimize "On"

   filter "configurations:Dist"
         defines  "HZ_DIST" 
        --  buildoptions "/MD"
         runtime "Release" 
         optimize "On"