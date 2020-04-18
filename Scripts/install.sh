#!/usr/bin/env bash

echo "This script installs all needed dependencies to successfully run the Air Quality Application"
echo "Run this script with sudo privileges in order to install the libraries"

echo "Fetching updates"
apt update -qq

echo "Installing libraries..."
apt install -y build-essential cmake make libcurl4-openssl-dev libglew-dev libglfw3-dev libglfw3

echo "Installation successfull!"
