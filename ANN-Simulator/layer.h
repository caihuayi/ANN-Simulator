#ifndef LAYER_H
#define LAYER_H
#include <QList>
#include <QVector>
#include <QPainter>
#include <memory>
#include <QtAlgorithms>
#include <QTextStream>
#include "inputneutron.h"
#include "hideneutron.h"
#include "activationfunction.h"

class Neutron;
class Layer
{
protected:
    QList<std::shared_ptr<Neutron>> neutron_list;
    QVector<double> input_vector;
    QVector<double> output_vector;
    QList<QPoint> fpoint_list;
    QList<QPoint> bpoint_list;
    QPoint first_pos;
    int height_gap;
    int neutron_weight;
    int neutron_height;
    int last_layer_count;
    virtual void create(int n) = 0;
    bool is_debugging;
    std::shared_ptr<Neutron> debug_neuron;

public:
    Layer();
    Layer(int x, int y, int gap, int weight, int height, int last_layer_count);
    virtual ~Layer() = default;
    int size() const;
    void set_input(QVector<double> input);
    //QVector<double> get_output()
    const QVector<double>& get_output() const;
    void draw(std::shared_ptr<QPainter> painter,
              std::shared_ptr<QBrush> active_brush,
              std::shared_ptr<QBrush> debug_brush,
              std::shared_ptr<QBrush> normal_brush) const;
    void remove_node(std::shared_ptr<Neutron> neu);
    void add_node(std::shared_ptr<Neutron> neu);
    void onPress(double x, double y);
    void onRelease(double x, double y);
    void onMove(double cx, double cy);
    std::shared_ptr<Neutron> get_active_neutron();
    const QList<QPoint>& get_fplist() const;
    const QList<QPoint>& get_bplist() const;
    void update_fbpoint();
    void random_para();
    void update_para(QVector<double> para);
    void update_activation(std::shared_ptr<ActivationFunction> activation_function);
    void layer_compute();
    void renew_output();
    void layer_debug();
    bool get_debugging() const;
    std::shared_ptr<Neutron> get_debug_neutron();
    bool debug_next(std::shared_ptr<Layer> layer);
    void clear_output();
    void set_last_debug(bool state);
    QTextStream& write_file(QTextStream& out);
    QTextStream& read_file(QTextStream& in);
};

#endif // LAYER_H
