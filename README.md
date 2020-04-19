## Air quality monitor application
[![Build Status](https://travis-ci.com/zpervan/AirQualityApp.svg?branch=master)](https://travis-ci.com/zpervan/AirQualityApp)

### Introduction

An application which shows the air quality for the Croatian city Osijek. The data is acquired from the site [HAOP](http://iszz.azo.hr/iskzl/exc.htm), a site from the Croatian agency of environment and nature.
Pollutants visualized:
* Nitrogen Dioxide [NO2], ug/m3
* Sulfur Dioxide [SO2], ug/m3
* Carbon Monoxide [CO], mg/m3
* Benzene [C6H6], ug/m3
* Ozone [O3], ug/m3

Also, the temperature data can be visualized and is represented in degree Celsius [°C].

<img src="https://raw.githubusercontent.com/zpervan/AirQualityApp/master/Images/example_app.png"  width="1200">

Libraries used in this project:
* [DearImgui](https://github.com/ocornut/imgui) 
* [Google Test](https://github.com/google/googletest)

### Install

In order to run the application, the following libraries needs to be installed:
```
libcurl4-openssl-dev 
libglew-dev
libglfw3-dev
libglfw3
```

Run the `install.sh` script to automate the installation process. This script is located inside the `Scripts` folder. Also, `sudo` privileges are needed. 
Usage:
* Position your terminal in the `AirQualityApp` folder,
* Execute the following commands:
```
sudo chmod 755 Scripts/install.sh    # Modify the file to make it a executable
cd Scripts/
./install.sh
```
### Use

To use this application, from the `Scripts` folder run the script `build_and_run.sh` without any arguments. This should configure, build and execute the application.
Usage:
* Position your terminal in the `AirQualityApp` folder,
* Execute the following commands:
```
sudo chmod 755 Scripts/build_and_run.sh    # Modify the file to make it a executable
cd /Scripts
./build_and_run.sh
```
For more options type `build_and_run.sh --help`.
The application itself is highly interactive so you can see data values for each pollutant and toggle plots you are interested in.

### Issues

* The API data tends sometimes to refresh the data at a later point of time or the data is not availabe for fetching at all. The most known problem is the fetching of the temperature data, to be more specific, the fetched data is empty! 
* Imgui, in it's current state, has somewhat basic plotting functionalities.
* Data fetching takes up to 5-6 seconds so while changing dates it will take a while to load the plots with new data.
