#include "hideneutron.h"
#include <iostream>
using namespace std;
HideNeutron::HideNeutron()
{

}

HideNeutron::HideNeutron(const QPoint &p, int w, int h, int llc, double _z, double _y) :
                         Neutron(p, w, h, llc)
                       , z(_z)
                       , y(_y)
{
    last_layer_count = llc;
    activation_function = nullptr;
}

void HideNeutron::random_para()
{
    QTime time;
    weight_vector.clear();
    for (int i = 0; i < last_layer_count; i++)
    {
        time = QTime::currentTime();
        qsrand(time.msec() + time.second()*1000);
        double n = static_cast<double>(qrand()%20) / 10;
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

double HideNeutron::compute_operation(double x)
{

}

void HideNeutron::set_activation_function(std::shared_ptr<ActivationFunction> af)
{
    activation_function = af;
}

double HideNeutron::activation_operation(double y)
{

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
