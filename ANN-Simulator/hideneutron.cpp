#include "hideneutron.h"
#include <iostream>
using namespace std;
HideNeutron::HideNeutron()
{

}

HideNeutron::HideNeutron(const QPoint &p, int w, int h, int llc) :
                         Neutron(p, w, h, llc)
{
    last_layer_count = llc;
    activation_function = nullptr;
}

void HideNeutron::random_para()
{
    weight_vector.clear();
    RandomMaker rm;
    for (int i = 0; i < last_layer_count; i++)
    {
        double n = rm.make_random(2);
        weight_vector.append(n);

    }
}

QVector<double> HideNeutron::get_weight_vector() const
{
    return weight_vector;
}

void HideNeutron::set_weight_vector(QVector<double> arr)
{
    weight_vector = arr;
}

void HideNeutron::set_compute_function(std::shared_ptr<ComputeFunction> cf)
{
    compute_function = cf;
}

void HideNeutron::set_activation_function(std::shared_ptr<ActivationFunction> af)
{
    activation_function = af;
}

void HideNeutron::update_para(QVector<double> para)
{
    this->weight_vector = para;
}

void HideNeutron::update_activation(shared_ptr<ActivationFunction> af)
{
    activation_function = af;
}

Neutron::NeutronType HideNeutron::get_type() const
{
    return type;
}

shared_ptr<ActivationFunction> HideNeutron::get_activation() const
{
    return activation_function;
}

double HideNeutron::compute(QVector<double> x)
{
    double result = 0;
    for (int i = 0; i < weight_vector.size(); i++)
    {
        result += x[i]*weight_vector[i];
        cout << "x[i]=" << x[i] << " weight[i]=" << weight_vector[i] << endl;
    }
    output = activation_function->compute(result);
    cout << output << endl;
    return output;
}

QTextStream& HideNeutron::write_file(QTextStream &out)
{
    //out << 2 << " " << last_layer_count << " ";
    return out;
}

QTextStream& HideNeutron::read_file(QTextStream &in)
{
    //int llc;
    //in >> llc;
    //last_layer_count = llc;

    return in;
}
