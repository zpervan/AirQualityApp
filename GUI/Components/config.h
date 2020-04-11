// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_CONFIG_H
#define AIRQUALITYAPP_CONFIG_H

/// @brief This represents the configuration file for implemented components.
/// All components have their own namespace and configuration variables should
/// be
///

#include "../Utility/ThirdParty/DearImgui/imgui.h"
namespace Config {

namespace Window {
static ImVec2 window_size{200.f, 300.f};

static bool show_carbon_monoxide{false};
static bool show_benzen{false};
static bool show_ozone{false};
} // namespace Window

} // namespace Config

#endif // AIRQUALITYAPP_CONFIG_H
