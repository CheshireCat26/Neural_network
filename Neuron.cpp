//
// Created by cheshirecat on 11/6/19.
//

#include "Neuron.h"
#include <cmath>
#include <stdexcept>

using namespace std;

/*Activation function is sigmoid function. Sigmoid function is 1/(1 + exp(-x)). X is output from neuron*/
float Neuron::Axon::getSignal() const
{
    return 1 / (1 + exp(ownerNeuron->sum_function()));
}

/* Set this neuron as the owner for this Neuron's axon */
Neuron::Neuron()
{
    axon.ownerNeuron = this;
}

/* Neuron get signal from every it's dendrite, multiply the signal by dendrite's weight ans sum them.
 * Dendrite get signals from their axon. Axon get signal from it's neuron.
 * Sum_function is a recursive function*/
float Neuron::sum_function() const
{
    float result(0.);
    for(Dendrite d : dendrite){
        result += d.inputAkson->getSignal() * d.weight;
    }
    return result;
}

float Neuron::get_weight(int ind_dendrite) const
{
    if (ind_dendrite < 0 || ind_dendrite >= dendrite.size())
        throw runtime_error("Neuron::get_weight(): not available value");

    return dendrite[ind_dendrite].weight;
}

void Neuron::set_weight(int ind_dendrite, float value)
{
    if (ind_dendrite < 0 || ind_dendrite >= dendrite.size())
        throw runtime_error("Neuron::set_weight(): not available value");

    dendrite[ind_dendrite].weight = value;
}