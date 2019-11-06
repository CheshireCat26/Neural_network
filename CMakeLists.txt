cmake_minimum_required(VERSION 3.15)
project(NeuralNetwork)

add_executable(NeuralNetwork main.cpp Neuron.cpp Neuron.h Neural_network.cpp Neural_network.h)
target_link_libraries(NeuralNetwork gtest_main)
