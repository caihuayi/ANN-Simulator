#ifndef INPUTNEUTRON_H
#define INPUTNEUTRON_H
#include "neutron.h"
#include "activationfunction.h"
#include "randommaker.h"
#include <QTime>
#include <QVector>
#include <memory>
class InputNeutron : public Neutron
{
private:
    const NeutronType type = Input;
public:
    InputNeutron();
    InputNeutron(const QPoint &p, int w, int h, double output);
    void random_para() override;
    QVector<double> get_weight_vector() const override;
    void update_para(QVector<double>) override;
    void update_activation(std::shared_ptr<ActivationFunction> activation_function) override;
    NeutronType get_type() const override;
    std::shared_ptr<ActivationFunction> get_activation() const override;
    double compute(QVector<double> x) override;
    QTextStream& read_file(QTextStream &in) override;
    QTextStream& write_file(QTextStream &out) override;
};

#endif // INPUTNEUTRON_H
