#ifndef MANAGER_H
#define MANAGER_H
#include <QList>
#include <QPainter>
#include <memory>
#include <QVector>
class Layer;
class Neutron;
class Manager
{
private:
    std::shared_ptr<QPainter> active_painter;
    std::shared_ptr<QPainter> debug_painter;
    std::shared_ptr<QPainter> normal_painter;

    QList<std::shared_ptr<Layer>> layer_list;

    QPoint first_pos;
    int neutron_height;
    int neutron_weight;
    int weight_gap;
    int height_gap;
    QVector<int> neutron_count;
    int layer_count;

    void draw_layer(std::shared_ptr<QPainter> painter,
                    std::shared_ptr<QBrush> active_brush,
                    std::shared_ptr<QBrush> debug_brush,
                    std::shared_ptr<QBrush> normal_brush) const;
    void draw_line(std::shared_ptr<QPainter> painter, std::shared_ptr<QPen> line_pen) const;
public:
    Manager();
    Manager(int x, int y, int neutron_height, int neutron_weight, int weight_gap, int height_gap);
    ~Manager();
    int size() const;
    void draw(std::shared_ptr<QPainter> painter,
              std::shared_ptr<QBrush> active_brush,
              std::shared_ptr<QBrush> debug_brush,
              std::shared_ptr<QBrush> normal_brush,
              std::shared_ptr<QPen> line_pen) const;
    void create();
    void OnPress(double x, double y);
    void OnRelease(double x, double y);
    void OnMove(double cx, double cy);
    std::shared_ptr<Neutron> search_active();
    void update_fbpoint();
    void set_network(int layer_count, QVector<int> neutron_count);
};

#endif // MANAGER_H
