#ifndef HIDENEUTRON_H
#define HIDENEUTRON_H
#include "neutron.h"
#include <QVector>
#include <QTime>
#include <memory>
#include "computefunction.h"
#include "activationfunction.h"
#include "randommaker.h"

class HideNeutron : public Neutron
{
private:
    const NeutronType type = Hide;
    int last_layer_count;
public:
    HideNeutron();
    HideNeutron(const QPoint &position, int weight, int height, int last_layer_count);
    void random_para() override;
    QVector<double> get_weight_vector() const override;
    void set_weight_vector(QVector<double>);
    void set_compute_function(std::shared_ptr<ComputeFunction> compute_function);
    void set_activation_function(std::shared_ptr<ActivationFunction> activation_function);
    void update_para(QVector<double>) override;
    void update_activation(std::shared_ptr<ActivationFunction> activation_function) override;
    NeutronType get_type() const override;
    std::shared_ptr<ActivationFunction> get_activation() const override;
    double compute(QVector<double> x) override;
    QTextStream & read_file(QTextStream &in) override;
    QTextStream & write_file(QTextStream &out) override;
};

#endif // HIDENEUTRON_H
