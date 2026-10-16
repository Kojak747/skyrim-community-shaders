#pragma once

#include "Feature.h"

/**
 * @brief Core feature enabling wind sway on DynDOLOD billboard tree LOD for the Windswept Tree LOD plugin.
 *
 * Windswept Tree LOD (an SKSE plugin, K747_LodWind.dll) sways the distant billboard trees. It picks
 * out the tree LOD draws itself and binds the wind state (b13) and per-vertex weights (t120) to the
 * vertex shader for those draws only. The TREE_LOD_WIND define adds the matching vertex offset to
 * Lighting.hlsl and Utility.hlsl, so the colour, depth and shadow passes all move together.
 *
 * It self-disables in PostPostLoad when the plugin is absent, so the define is off and the shaders
 * are unchanged without it; regular feature validation recompiles them when the plugin is added or removed.
 */
struct TreeLODWind : Feature
{
	virtual inline std::string GetName() override { return "Tree LOD Wind"; }
	virtual inline std::string GetShortName() override { return "TreeLODWind"; }
	virtual inline std::string_view GetShaderDefineName() override { return "TREE_LOD_WIND"; }
	virtual inline bool HasShaderDefine(RE::BSShader::Type t) override
	{
		return t == RE::BSShader::Type::Lighting || t == RE::BSShader::Type::Utility;
	}
	virtual std::string_view GetCategory() const override { return FeatureCategories::kLandscapeAndTextures; }

	/** @brief Returns a summary description for the UI. */
	virtual std::pair<std::string, std::vector<std::string>> GetFeatureSummary() override
	{
		return { "Lets the distant DynDOLOD billboard trees sway in the wind, in support of the Windswept Tree LOD plugin.",
			{ "Active only while the Windswept Tree LOD SKSE plugin is installed.",
				"Without the plugin, tree LOD is drawn exactly as before." } };
	}

	virtual void DrawSettings() override;

	/** @brief Disables the feature when the Windswept Tree LOD plugin is not installed. */
	virtual void PostPostLoad() override;

	virtual bool IsCore() const override { return true; }
};
