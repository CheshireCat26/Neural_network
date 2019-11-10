//
// Created by cheshirecat on 11/6/19.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H

#include <vector>
#include <iostream>

class Neuron
{

public:

    /* Axon is the output part of the neuron. Dentrits gets value of neuron from it's Axon.*/
    class Axon{
    public:
        virtual float getSignal() const;//Activation function
        Neuron *ownerNeuron;

        void set_input(bool b) { input = b; }
        bool get_input() const { return input; }
    private:
        bool input = false; //Axon can be in Input neuron. If it in input neuron, it should't modify signal;
    };

    /* Dendrite is an input part of neuron. It has weight. It gets value from axon of neron from previous layer.*/
    class Dendrite{
    public:
        float weight;
        Axon *inputAkson;

        Dendrite(float weight, Axon& inAxon) : weight{weight}, inputAkson{&inAxon} {}
        Dendrite() : weight{0}, inputAkson{nullptr} {}
    };

    Neuron(const Neuron &neuron);
    explicit Neuron(const std::vector<Dendrite>& dendrites);

    float get_axon_value() const { return axon.getSignal(); }
    Axon& get_axon_ref() { return axon; }
    Dendrite& get_dendrite_ref(int ind);

    Neuron& operator=(const Neuron& neuron);
private:

    virtual float sum_function() const;
    std::vector<Dendrite> dendrite;
    Axon axon{};
};

#endif