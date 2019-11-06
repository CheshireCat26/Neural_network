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

Neural_network::Neural_network(int input_size, std::vector<int> hidden_size, int output_size) {
    for (int i{0}; i < input_size; i++)
    {
        inNeurons.emplace_back(Input_neuron());
    }

}

int Neural_network::hidden_layer_size(int ind_layer) const {
    if (ind_layer < 0 || ind_layer >= hidNeurons.size())
        throw runtime_error("Neural_network::hidden_layer_size(): out of hidden layers");
    return hidNeurons[ind_layer].size();
}
