#include "activationtanh.h"

ActivationTanh::ActivationTanh()
{

}

double ActivationTanh::compute(double x) const
{
    return ((qPow(e, x) - qPow(e, -x)) / (qPow(e, x) + qPow(e, -x)));
}

ActivationFunction::ActivationType ActivationTanh::get_type() const
{
    return type;
}
