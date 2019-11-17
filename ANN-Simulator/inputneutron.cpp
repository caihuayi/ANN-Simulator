#include "inputneutron.h"
using namespace std;
InputNeutron::InputNeutron()
{

}

InputNeutron::InputNeutron(const QPoint &p, int w, int h, double _z) :
    Neutron(p, w, h, 0), z(_z)
{
    output = z;
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


