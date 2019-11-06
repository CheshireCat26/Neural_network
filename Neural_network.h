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
    class InputNeuron : public Neuron{
    public:

        float kernelFunction(){
            return value;
        }

        void set_value(float v) { value = v; }

    private:
        float value;
    };

    //return answer of net for input in;
    std::vector<float> test(const std::vector<float> &in);

    //0 - input layer, last - out layer;
    float get_weight(int ind_layer, int ind_neuron, int ind_dendrite) const;
    //0 - input layer, last - out layer;
    void set_weight(int ind_layer, int ind_neuron, int ind_dendrite, float value);
    //return amount of layers;
    int size() const;

protected:
    Neural_network();
private:
    void set_inputs(std::vector<float> inpts);

    std::vector<InputNeuron> inNeurons;
    std::vector<std::vector<Neuron>> hidNeurons;
    std::vector<Neuron> outNeurons;
};


#endif //NEURALNETWORK_NEURAL_NETWORK_H
