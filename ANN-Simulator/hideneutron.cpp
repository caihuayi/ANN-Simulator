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
    out << position.x() << " " << position.y() << " ";
    out << weight_vector.size() << " ";
    for (auto& iter : weight_vector)
    {
        out << iter << " ";
    }
    out << input.size() << " ";
    for (auto& iter : input)
    {
        out << iter << " ";
    }
    //cout << output << " " << is_active << " " << is_debug << " " << activation_function->get_type() << " ";

    out << output << " " << is_active << " " << is_debug << " " << activation_function->get_type() << " ";

    return out;
}

QTextStream& HideNeutron::read_file(QTextStream &in)
{
    int x, y;
    in >> x >> y;
    position.setX(x);
    position.setY(y);
    //cout << "get in Neutron::read_file" << endl;
    int n;
    in >> n;
    for (int i = 0; i < n; i++)
    {
        in >> weight_vector[i];
    }
    in >> n;
    for (int i = 0; i < n; i++)
    {
        double inp;
        in >> inp;
        input.append(inp);
    }
    int act, deb;
    cout << "read_output" << output << endl;
    in >> output;
    in >> act;
    in >> deb;
    is_active = act;
    is_debug = deb;
    int act_typ;
    in >> act_typ;

    if (act_typ == ActivationFunction::ReLU)
    {
        shared_ptr<ActivationFunction> relu(new ActivationReLu());
        activation_function = relu;
    }
    else if(act_typ == ActivationFunction::Sigmoid)
    {
        shared_ptr<ActivationFunction> sigmoid(new ActivationSigmoid());
        activation_function = sigmoid;
    }
    else if(act_typ == ActivationFunction::Tanh)
    {
        shared_ptr<ActivationFunction> tanh(new ActivationTanh());
        activation_function = tanh;
    }
    compute_mid_point();
    renew_point();
    return in;
}
