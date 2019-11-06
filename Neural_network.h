//
// Created by cheshirecat on 11/6/19.
//

#ifndef NEURALNETWORK_NEURAL_NETWORK_H
#define NEURALNETWORK_NEURAL_NETWORK_H


#include "Neuron.h"
#include <vector>


class Neural_network {
public:

    /*Input neuron is child of Neruon. Input neuron  */
    class Input_neuron : public Neuron{
    public:

        float sum_function(){
            return value;
        }

        void set_value(float v) { value = v; }

    private:
        float value;
    };

    //Size of hidden_size is amount of hidden layers .Each element in hidden_size is size of hidden layer.
    Neural_network(int input_size, std::vector<int> hidden_size, int output_size);

    //return answer of net for input in;
    std::vector<float> test(const std::vector<float> &in);

    //0 - input layer, last - out layer;
    float get_weight(int ind_layer, int ind_neuron, int ind_dendrite) const;
    //0 - input layer, last - out layer;
    void set_weight(int ind_layer, int ind_neuron, int ind_dendrite, float value);
    //return amount of layers;
    int size() const;
    int input_layer_size() const { return inNeurons.size(); }
    int hidden_layers_size() const {return hidNeurons.size(); }
    int hidden_layer_size(int ind_layer) const;
    int out_layer_size() const { return hidNeurons.size(); }

private:
    void set_inputs(std::vector<float> inpts);

    std::vector<Input_neuron> inNeurons;
    std::vector<std::vector<Neuron>> hidNeurons;
    std::vector<Neuron> outNeurons;
};


#endif //NEURALNETWORK_NEURAL_NETWORK_H
