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
    if (!input)
        return 1 / (1 + exp(-ownerNeuron->sum_function()));
    else
        return ownerNeuron->sum_function();
}

/* Set this neuron as the owner for this Neuron's axon */
Neuron::Neuron() : axon()
{
    axon.ownerNeuron = this;
    dendrite.clear();
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

Neuron::Neuron(const vector<Dendrite>& dendrites) : Neuron()
{
    for(Dendrite den : dendrites)
        dendrite.emplace_back(den);
}

Neuron::Neuron(const Neuron &neuron) : dendrite{neuron.dendrite}{
    axon.ownerNeuron = this;
    axon.set_input(neuron.axon.get_input());
}

Neuron &Neuron::operator=(const Neuron &neuron) {
    if (&neuron == this)
        return *this;

    axon.ownerNeuron = neuron.axon.ownerNeuron;
    axon.set_input(neuron.axon.get_input());
    return *this;
}

Neuron::Dendrite &Neuron::get_dendrite_ref(int ind) {
    if (ind < 0 || ind > dendrite.size())
        throw runtime_error("Neuron::Dendrite &Neuron::get_dendrite_ref(): out of dendrites");
    return dendrite[ind];
}
