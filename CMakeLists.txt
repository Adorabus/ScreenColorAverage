cmake_minimum_required(VERSION 3.4...3.18)
project(ScreenColorAverage)
add_subdirectory(pybind11)
pybind11_add_module(screen_color_avg ScreenColorAverage/ColorAverager.cpp)