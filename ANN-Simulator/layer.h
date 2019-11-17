#ifndef LAYER_H
#define LAYER_H
#include <QList>
#include <QVector>
#include <QPainter>
#include <memory>
#include "inputneutron.h"
#include "hideneutron.h"
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
    void renew_output();
public:
    Layer();
    Layer(int x, int y, int n, int gap, int weight, int height, int last_layer_count);
    virtual ~Layer() = default;
    int size() const;
    void set_input(const Layer& layer);
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
};

#endif // LAYER_H
