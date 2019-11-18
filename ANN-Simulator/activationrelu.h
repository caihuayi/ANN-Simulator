#ifndef ACTIVATIONRELU_H
#define ACTIVATIONRELU_H

#include "activationfunction.h"

class ActivationReLu : public ActivationFunction
{
private:
    double k;
    const ActivationType type = ActivationType::ReLU;
public:
    ActivationReLu();
    ActivationReLu(double k);
    double compute(double x) const override;
    double get_k() const;
    void set_k(double k);
    ActivationType get_type() const override;
};

#endif // ACTIVATIONRELU_H
