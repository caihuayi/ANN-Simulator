#ifndef INPUTNEUTRON_H
#define INPUTNEUTRON_H
#include "neutron.h"
#include <QTime>
#include <QVector>
class InputNeutron : public Neutron
{
private:
    double z;
public:
    InputNeutron();
    InputNeutron(const QPoint &p, int w, int h, double _z);
    void random_para() override;
    double get_z() const;
    void set_z(double z);
    QVector<double> get_weight_vector() const override;
};

#endif // INPUTNEUTRON_H
