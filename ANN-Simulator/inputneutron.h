#ifndef INPUTNEUTRON_H
#define INPUTNEUTRON_H
#include "neutron.h"
#include "activationfunction.h"
#include <QTime>
#include <QVector>
#include <memory>
class InputNeutron : public Neutron
{
private:
    const NeutronType type = Input;
    double z;
public:
    InputNeutron();
    InputNeutron(const QPoint &p, int w, int h, double _z);
    void random_para() override;
    double get_z() const;
    void set_z(double z);
    QVector<double> get_weight_vector() const override;
    void update_para(QVector<double>) override;
    void update_activation(std::shared_ptr<ActivationFunction> activation_function) override;
    NeutronType get_type() const override;
    std::shared_ptr<ActivationFunction> get_activation() const override;
    double compute(QVector<double> x) override;
};

#endif // INPUTNEUTRON_H
