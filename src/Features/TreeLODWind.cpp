#include "TreeLODWind.h"

#include <imgui.h>

void TreeLODWind::DrawSettings()
{
	ImGui::TextWrapped(
		"This feature provides compatibility with the Windswept Tree LOD SKSE plugin, which makes the distant DynDOLOD billboard trees sway in the wind. The plugin's own settings control the sway. This feature is only active when the Windswept Tree LOD plugin is installed.");
}

void TreeLODWind::PostPostLoad()
{
	// Checked here because every SKSE plugin has loaded by now and the shader disk cache has not
	// been validated yet, so installing or removing the plugin invalidates the cache through
	// regular feature validation.
	if (loaded && GetModuleHandleW(L"K747_LodWind.dll") == nullptr) {
		loaded = false;
		failedLoadedMessage = "Windswept Tree LOD is not installed, compatibility is disabled.";
		logger::info("[Tree LOD Wind] Windswept Tree LOD plugin not detected, compatibility disabled");
	} else if (loaded) {
		logger::info("[Tree LOD Wind] Windswept Tree LOD plugin detected, compatibility enabled");
	}
}
