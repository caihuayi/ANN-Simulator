#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

class ActivationFunction
{
public:
    typedef enum {ReLU, Sigmoid, Tanh, MAX} ActivationType;

    ActivationFunction();
    virtual ~ActivationFunction() = default;
    virtual double compute(double x) const = 0;
    virtual ActivationType get_type() const = 0;
};

#endif // ACTIVATIONFUNCTION_H
