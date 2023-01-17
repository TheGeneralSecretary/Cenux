workspace "Cenux"
   architecture "x86"
   startproject "Cenux"
   configurations { "Unknown" }

project "Cenux"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"
staticruntime "off"

targetdir ("%{wks.location}/Build/VSJunk")
objdir ("%{wks.location}/Build/VSJunk/Int/")

files
{
	"Kernel/**.h",
	"Kernel/**.cpp",
}

includedirs
{
	".",
}
