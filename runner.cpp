// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

// TODO: JSON parser
// TODO: Epoch converter
// TODO: Visualization

#include "Utility/DataScraper/data_scraper.h"

#include <iostream>

int main() {

  DataScraper data_scraper;

  data_scraper.SetUrl("http://iszz.azo.hr/iskzl/rs/podatak/export/"
                      "json?postaja=160&polutant=3&tipPodatka=0&vrijemeOd=04."
                      "04.2020&vrijemeDo=04.04.2020");

  data_scraper.FetchAirQualityData();

  return 0;
}
