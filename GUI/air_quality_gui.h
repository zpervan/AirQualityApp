// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan
//

#ifndef AIRQUALITYAPP_AIR_QUALITY_GUI_H
#define AIRQUALITYAPP_AIR_QUALITY_GUI_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class AirQualityGui
{
public:
  int Run();

private:
  int Setup(GLFWwindow *window);
};

#endif // AIRQUALITYAPP_AIR_QUALITY_GUI_H
