#include "inputneutron.h"
using namespace std;
InputNeutron::InputNeutron()
{

}

InputNeutron::InputNeutron(const QPoint &p, int w, int h, double _z) :
    Neutron(p, w, h, 0), z(_z)
{
    output = z;
    activation_function = nullptr;
}

void InputNeutron::random_para()
{
    QTime time;
    qsrand(time.msec() + time.second()*1000);
    double n = static_cast<double>(qrand()%20) / 10;
    z = n;
    output = n;
}

double InputNeutron::get_z() const
{
    return z;
}

void InputNeutron::set_z(double _z)
{
    z = _z;
    output = z;
}

QVector<double> InputNeutron::get_weight_vector() const
{
    QVector<double> n = {z};
    return n;
}

void InputNeutron::update_para(QVector<double> para)
{
    z = para[0];
    output = para[0];
}

void InputNeutron::update_activation(shared_ptr<ActivationFunction>)
{}

Neutron::NeutronType InputNeutron::get_type() const
{
    return type;
}

shared_ptr<ActivationFunction> InputNeutron::get_activation() const
{
    return activation_function;
}

double InputNeutron::compute(QVector<double> x)
{
    return output;
}
