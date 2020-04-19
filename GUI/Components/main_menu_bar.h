// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_MAIN_MENU_BAR_H
#define AIRQUALITYAPP_MAIN_MENU_BAR_H

#include "../Utility/ThirdParty/DearImgui/imgui.h"
#include "config.h"

namespace Menu {
static void ShowMainMenuBar() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("Window")) {
      if (ImGui::MenuItem("About")) {
      }
      ImGui::Separator();
      if (ImGui::MenuItem("Exit", "Alt+F4")) {
        Config::Window::exit_application = true;
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}

} // namespace Menu

#endif // AIRQUALITYAPP_MAIN_MENU_BAR_H
