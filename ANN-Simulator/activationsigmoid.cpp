#include "activationsigmoid.h"

ActivationSigmoid::ActivationSigmoid()
{

}

double ActivationSigmoid::compute(double x) const
{
    return 1/(1+qPow(e, -x));
}

ActivationFunction::ActivationType ActivationSigmoid::get_type() const
{
    return type;
}
