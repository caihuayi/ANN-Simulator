#ifndef ACTIVATIONTANH_H
#define ACTIVATIONTANH_H

#include <QtMath>

#include "activationfunction.h"

class ActivationTanh : public ActivationFunction
{
private:
    const ActivationType type = Tanh;
    const double e = 2.7182818;
public:
    ActivationTanh();
    double compute(double x) const override;
    ActivationType get_type() const override;
};

#endif // ACTIVATIONTANH_H
