// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan
//

#ifndef AIRQUALITYAPP_MAIN_MENU_BAR_H
#define AIRQUALITYAPP_MAIN_MENU_BAR_H

#include "../DearImgui/imgui.h"

namespace Menu
{
static void ShowMainMenuBar()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
//        ShowExampleMenuFile();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
    {
      if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
      if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
      ImGui::Separator();
      if (ImGui::MenuItem("Cut", "CTRL+X")) {}
      if (ImGui::MenuItem("Copy", "CTRL+C")) {}
      if (ImGui::MenuItem("Paste", "CTRL+V")) {}
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}

}

#endif // AIRQUALITYAPP_MAIN_MENU_BAR_H
