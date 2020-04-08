// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

// TODO: Epoch converter
// TODO: Visualization
// TODO: Linear regression
// TODO: Installation script
// TODO: RunAllTests script
// TODO: out-of-source build check RoutePlanning project

#include "Utility/DataScraper/data_scraper.h"

#include <iostream>

#include "GUI/air_quality_gui.h"


int main() {

  AirQualityGui* air_quality_gui =  new AirQualityGui;

    air_quality_gui->Run();


  return 0;
}
