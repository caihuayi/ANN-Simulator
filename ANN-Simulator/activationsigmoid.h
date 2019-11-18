#ifndef ACTIVATIONSIGMOID_H
#define ACTIVATIONSIGMOID_H

#include <QtMath>

#include "activationfunction.h"

class ActivationSigmoid : public ActivationFunction
{
private:
    const double e = 2.7182818;
    const ActivationType type = Sigmoid;
public:
    ActivationSigmoid();
    double compute(double x) const override;
    ActivationType get_type() const override;
};

#endif // ACTIVATIONSIGMOID_H
