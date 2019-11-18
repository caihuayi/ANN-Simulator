#ifndef HIDENEUTRON_H
#define HIDENEUTRON_H
#include "neutron.h"
#include <QVector>
#include <QTime>
#include <memory>
#include "computefunction.h"
#include "activationfunction.h"

class HideNeutron : public Neutron
{
private:
    const NeutronType type = Hide;
    double z;
    double y;
    int last_layer_count;
    std::shared_ptr<ComputeFunction> compute_function;

public:
    HideNeutron();
    HideNeutron(const QPoint &position, int weight, int height, int last_layer_count, double x, double y);
    void random_para() override;
    QVector<double> get_weight_vector() const override;
    void set_weight_vector(QVector<double>);
    void set_compute_function(std::shared_ptr<ComputeFunction> compute_function);
    double compute_operation(double x);
    void set_activation_function(std::shared_ptr<ActivationFunction> activation_function);
    double activation_operation(double y);
    void update_para(QVector<double>) override;
    void update_activation(std::shared_ptr<ActivationFunction> activation_function) override;
    NeutronType get_type() const override;
    std::shared_ptr<ActivationFunction> get_activation() const override;
    double compute(QVector<double> x) override;
};

#endif // HIDENEUTRON_H
