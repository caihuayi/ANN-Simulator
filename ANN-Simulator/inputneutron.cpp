#include "inputneutron.h"
using namespace std;
InputNeutron::InputNeutron()
{

}

InputNeutron::InputNeutron(const QPoint &p, int w, int h, double o) :
    Neutron(p, w, h, 0)
{
    output = o;
    activation_function = nullptr;
}

void InputNeutron::random_para()
{
    RandomMaker rm;
    double n = rm.make_random(2);
    output = n;
}

QVector<double> InputNeutron::get_weight_vector() const
{
    QVector<double> n = {output};
    return n;
}

void InputNeutron::update_para(QVector<double> para)
{
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

double InputNeutron::compute(QVector<double>)
{
    return output;
}

QTextStream& InputNeutron::write_file(QTextStream &out)
{
    out << 1 << " ";

    return out;
}

QTextStream& InputNeutron::read_file(QTextStream& in)
{

    return in;
}
