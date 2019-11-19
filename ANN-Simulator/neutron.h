#ifndef NEUTRON_H
#define NEUTRON_H
#include <QPainter>
#include <memory>
#include <QTextStream>

#include "activationrelu.h"
#include "activationsigmoid.h"
#include "activationtanh.h"


class ActivationFunction;
class Neutron
{
protected:
    QPoint position;
    QPoint old_position;
    QPoint mid_position;
    QPoint fpoint;
    QPoint bpoint;
    QVector<double> weight_vector;
    int weight;
    int height;
    QVector<double> input;
    double output;
    bool is_active;
    bool is_debug;
    std::shared_ptr<ActivationFunction> activation_function;
private:
    inline bool is_in(double x, double y);
    void compute_mid_point();
    void renew_point();
public:
    typedef enum{Input, Hide} NeutronType;
    Neutron();
    Neutron(const QPoint &position, int weight, int height, int last_layer_count);
    virtual ~Neutron();
    const QPoint& get_fpoint() const;
    const QPoint& get_bpoint() const;
    void set_input(QVector<double> input);
    QVector<double> get_input() const;
    double get_output() const;
    void set_active(bool act);
    bool get_active() const;
    void set_debug(bool de);
    bool get_debug() const;
    const QPoint& get_old_point() const;
    virtual void draw(std::shared_ptr<QPainter> painter,
                      std::shared_ptr<QBrush> active_brush,
                      std::shared_ptr<QBrush> debug_brush,
                      std::shared_ptr<QBrush> normal_brush) const;
    virtual void random_para() = 0;
    void OnPress(double x, double y);
    void OnMove(double cx, double cy);
    void OnRelease(double x, double y);
    virtual QVector<double> get_weight_vector() const = 0;
    virtual void update_para(QVector<double> para) = 0;
    virtual void update_activation(std::shared_ptr<ActivationFunction> activation_function) = 0;
    virtual NeutronType get_type() const = 0;
    virtual std::shared_ptr<ActivationFunction> get_activation() const = 0;
    virtual double compute(QVector<double> x) = 0;

    virtual QTextStream& write_file(QTextStream &out);
    virtual QTextStream& read_file(QTextStream &in);
};

#endif // NEUTRON_H
