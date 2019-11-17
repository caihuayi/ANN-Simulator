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
    cout << "hidden layer" << endl;
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
