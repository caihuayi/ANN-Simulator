#ifndef LAYER_H
#define LAYER_H
#include <QList>
#include <QVector>
#include <QPainter>
#include <memory>
class Neutron;
class Layer
{
private:
    QList<std::shared_ptr<Neutron>> neutron_list;
    QVector<double> input_vector;
    QVector<double> output_vector;
    QPoint first_pos;
    int height_gap;
    int neutron_weight;
    int neutron_height;

    void create(int n);
    void renew_output();
public:
    Layer();
    Layer(int x, int y, int n, int gap, int weight, int height);
    int size() const;
    void set_input(const Layer& layer);
    const QVector<double>& get_output() const;
    void draw(std::shared_ptr<QPainter> active_painter,
              std::shared_ptr<QPainter> debug_painter,
              std::shared_ptr<QPainter> normal_painter) const;
    void remove_node(std::shared_ptr<Neutron> neu);
    void add_node(std::shared_ptr<Neutron> neu);
};

#endif // LAYER_H
