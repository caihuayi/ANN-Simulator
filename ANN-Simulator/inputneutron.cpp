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

    out << output << " " << is_active << " " << is_debug << " ";


    return out;
}

QTextStream& InputNeutron::read_file(QTextStream& in)
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
    //cout << "read_output" << output << endl;
    in >> output;
    in >> act;
    in >> deb;
    is_active = act;
    is_debug = deb;


    return in;
}
