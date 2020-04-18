// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_AIR_QUALITY_GUI_H
#define AIRQUALITYAPP_AIR_QUALITY_GUI_H

/// @brief An abstraction class of the whole application. Calls the underlying
/// functionality which collects, processes and renders the air quality data.
/// @attention Currently displays only data for Osijek region for a selected
/// date.
class AirQualityGui {
public:
  /// @brief Assigns initial data
  static void Setup();

  /// @brief Starts and runs the application
  /// @return Error code
  static int Run();
};

#endif // AIRQUALITYAPP_AIR_QUALITY_GUI_H
