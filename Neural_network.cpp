//
// Created by cheshirecat on 11/6/19.
//

#include "Neural_network.h"
#include <stdexcept>

using namespace std;


void Neural_network::set_inputs(std::vector<float> inpts)
{
    if (inpts.size() != inNeurons.size())
        throw runtime_error("Neural_network::set_inputs(): inpts.size() != inNeurons.size()");

    for (int i{0}; i < inpts.size(); i++)
        inNeurons[i].set_value(inpts[i]);
}

vector<float> Neural_network::test(const vector<float> &in)
{
    set_inputs(in);
    vector<float> out(outNeurons.size());
    for (int i{0}; i < outNeurons.size(); i++)
        out[i] = outNeurons[i].get_axon_value();

    return out;
}

float Neural_network::get_weight(int ind_layer, int ind_neuron, int ind_dendrite) const
{
    if (ind_layer < 0 || ind_neuron < 0 || ind_dendrite < 0)
        throw runtime_error("Neural_network::get_weight(): negative value");

    if (ind_layer > hidNeurons.size() + 1)
        throw runtime_error("Neural_network::get_weight(): out of layers");

    if (ind_layer == 0) //input layer
    {
        if (ind_neuron >= inNeurons.size())
            throw runtime_error("Neural_network::get_weight(): out of input neurons");

        return inNeurons[ind_neuron].get_weight(ind_dendrite);
    }
    else if (ind_layer == hidNeurons.size() + 1) //out layer
    {
        if (ind_neuron >= outNeurons.size())
            throw runtime_error("Neural_network::get_weight(): out of output neurons");

        return outNeurons[ind_neuron].get_weight(ind_dendrite);
    }
    else //hidden layers
    {
        if (ind_neuron >= hidNeurons[ind_layer].size())
            throw runtime_error("Neural_network::get_weight(): out of hidden neurons");

        return hidNeurons[ind_layer][ind_neuron].get_weight(ind_dendrite);
    }
}

void Neural_network::set_weight(int ind_layer, int ind_neuron, int ind_dendrite, float value)
{
    if (ind_layer < 0 || ind_neuron < 0 || ind_dendrite < 0)
        throw runtime_error("Neural_network::get_weight(): negative value");

    if (ind_layer > hidNeurons.size() + 1)
        throw runtime_error("Neural_network::get_weight(): out of layers");

    if (ind_layer == 0) //input layer
    {
        if (ind_neuron >= inNeurons.size())
            throw runtime_error("Neural_network::get_weight(): out of input neurons");

        inNeurons[ind_neuron].set_weight(ind_dendrite, value);
    }
    else if (ind_layer == hidNeurons.size() + 1) //out layer
    {
        if (ind_neuron >= outNeurons.size())
            throw runtime_error("Neural_network::get_weight(): out of output neurons");

        outNeurons[ind_neuron].set_weight(ind_dendrite, value);
    }
    else //hidden layers
    {
        if (ind_neuron >= hidNeurons[ind_layer].size())
            throw runtime_error("Neural_network::get_weight(): out of hidden neurons");

        hidNeurons[ind_layer][ind_neuron].set_weight(ind_dendrite, value);
    }
}

int Neural_network::size() const
{
    return hidNeurons.size() + 2;
}

Neural_network::Neural_network()
= default;

int Neural_network::hidden_layer_size(int ind_layer) const {
    if (ind_layer < 0 || ind_layer >= hidNeurons.size())
        throw runtime_error("Neural_network::hidden_layer_size(): out of hidden layers");
    return hidNeurons[ind_layer].size();
}

void Neural_network::add_input_neuron(const Neural_network::Input_neuron& inputNeuron) {
    inNeurons.emplace_back(inputNeuron);
}

void Neural_network::add_hidden_neuron(int ind_layer, const Neuron& neuron) {
    if (ind_layer < 0 || ind_layer > hidNeurons.size())
        throw runtime_error("Neural_network::add_hidden_neuron(): out of hidden layers");
    if (ind_layer == hidNeurons.size())
        hidNeurons.emplace_back(vector<Neuron>());
    hidNeurons[ind_layer].emplace_back(neuron);
}

void Neural_network::add_out_neuron(const Neuron& neuron) {
    outNeurons.emplace_back(neuron);
}

Neural_network::Input_neuron &Neural_network::get_input_neuron_ref(int ind) {
    if (ind < 0 || ind >= inNeurons.size())
        throw runtime_error("Neural_network::get_input_neuron_ref(): out of input neurons");
    return inNeurons[ind];
}

Neuron &Neural_network::get_hid_neuron_ref(int ind_lay, int ind_n) {
    if (ind_lay < 0 || ind_lay >= hidNeurons.size())
        throw runtime_error("Neural_network::get_hid_neuron_ref(): out of hidden layers");
    if (ind_n < 0 || ind_n >= hidNeurons[ind_lay].size())
        throw runtime_error("Neural_network::get_hid_neuron_ref(): out of hidden neurons");
    return hidNeurons[ind_lay][ind_n];
}

Neuron &Neural_network::get_out_neuron_ref(int ind) {
    if (ind < 0 || ind >= outNeurons.size())
        throw runtime_error("Neural_network::get_out_neuron_ref(): out of out neurons");
    return outNeurons[ind];
}
