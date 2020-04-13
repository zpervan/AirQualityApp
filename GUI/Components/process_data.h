//
// Created by zvonimir on 13. 04. 2020..
//

#ifndef AIRQUALITYAPP_PROCESS_DATA_H
#define AIRQUALITYAPP_PROCESS_DATA_H

void ProcessCarbonMonoxide(std::string &fetch_data) {

  Utility::sDataScraper->SetUrl("http://iszz.azo.hr/iskzl/rs/podatak/export/"
                                "json?postaja=160&polutant=3&tipPodatka=0&"
                                "vrijemeOd=11.04.2020&vrijemeDo=11.04.2020");

  Utility::sDataScraper->FetchData();

  auto fetched_data = Utility::sDataScraper->GetFetchedData();
  if (Utility::counter >= 100) {
    Gas::carbon_monoxide_values.resize(0);

    Utility::sJsonParser->ReadData(fetched_data.data());
    Utility::air_quality_measurements = Utility::sJsonParser->Parse().value();

    for (auto &air_quality_measurement : Utility::air_quality_measurements) {
      Gas::carbon_monoxide_values.emplace_back(air_quality_measurement.value);
    }

    Utility::air_quality_measurements.resize(0);
    Utility::counter = 0;
  }
};

#endif // AIRQUALITYAPP_PROCESS_DATA_H
