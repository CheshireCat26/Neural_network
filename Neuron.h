//
// Created by cheshirecat on 11/6/19.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H

#include <vector>

class Neuron
{

public:

    /* Axon is the output part of the neuron. Dentrits gets value of neuron from it's Axon.*/
    class Axon{
    public:
        float getSignal() const;//Функция активации
        Neuron *ownerNeuron;
    };

    /* Dendrite is an input part of neuron. It has weight. It gets value from axon of neron from previous layer.*/
    class Dendrite{
    public:
        float weight;
        Axon *inputAkson;
    };


    Neuron();

    float get_axon_value() const {return axon.getSignal(); }
    float get_weight(int ind_dendrite) const;
    void set_weight(int ind_dendrite, float value);
private:
    virtual float sum_function() const;

    std::vector<Dendrite> dendrite;
    Axon axon;
};

#endif