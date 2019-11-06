cmake_minimum_required(VERSION 3.15)
project(NeuralNetwork)

set(CMAKE_CXX_STANDARD 17)

add_executable(NeuralNetwork main.cpp Neuron.cpp Neuron.h Neural_network.cpp Neural_network.h)