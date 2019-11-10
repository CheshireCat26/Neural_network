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
    class Input_neuron : public Neuron
    {
    public:
        Input_neuron() { get_axon_ref().set_input(true); }
        Input_neuron (const Input_neuron& inputNeuron);

        void set_value(float v) { value = v; }
        float get_value() const { return value; }

        Input_neuron& operator=(const Input_neuron& inputNeuron);
    private:
        float sum_function() const override {
            return value;
        }
        float value{};
    };

    //Bias is used to neural network be able to study when all inputs is 0. Each layer except output has bias.
    //Bias connect to each neuron on lower layer
    class Bias_neuron : public Input_neuron
    {
    public:
        Bias_neuron() : Input_neuron() { set_value(1); }

        Bias_neuron(const Bias_neuron& biasNeuron) : Input_neuron(biasNeuron) {}
        Bias_neuron& operator=(const Bias_neuron& biasNeuron) { set_value(biasNeuron.get_value()); }
    };

    //Size of hidden_size is amount of hidden layers .Each element in hidden_size is size of hidden layer.
    Neural_network();

    //return answer of net for input in;
    std::vector<float> test(const std::vector<float> &in);

    //return amount of layers;
    int size() const;
    int input_layer_size() const { return inNeurons.size(); }
    int hidden_layers_size() const {return hidNeurons.size(); }
    int hidden_layer_size(int ind_layer) const;
    int out_layer_size() const { return outNeurons.size(); }

    void add_input_neuron(const Input_neuron& inputNeuron);
    void add_hidden_neuron(int ind_layer, const Neuron& neuron);
    void add_out_neuron(const Neuron& neuron);

    Input_neuron& get_input_neuron_ref(int ind);
    Neuron& get_hid_neuron_ref(int ind_lay, int ind_n);
    Neuron& get_out_neuron_ref(int ind);
private:
    void set_inputs(std::vector<float> inputs);

    std::vector<Input_neuron> inNeurons;
    std::vector<std::vector<Neuron>> hidNeurons;
    std::vector<Neuron> outNeurons;
};


#endif //NEURALNETWORK_NEURAL_NETWORK_H
