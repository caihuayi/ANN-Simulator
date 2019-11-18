#include "activationrelu.h"

ActivationReLu::ActivationReLu() : k(1)
{}

ActivationReLu::ActivationReLu(double _k): k(_k)
{}

double ActivationReLu::compute(double x) const
{
    if (x <= 0) return 0;
    else {return k*x;}
}

double ActivationReLu::get_k() const
{
    return k;
}

void ActivationReLu::set_k(double _k)
{
    k = _k;
}

ActivationFunction::ActivationType ActivationReLu::get_type() const
{
    return type;
}
