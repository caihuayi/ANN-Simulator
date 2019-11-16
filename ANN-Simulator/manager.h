#ifndef MANAGER_H
#define MANAGER_H
#include <QList>
#include <QPainter>
#include <memory>
class Layer;
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

    void init_painter();
    void draw_layer() const;
    void draw_line() const;
public:
    Manager();
    Manager(int x, int y, int neutron_height, int neutron_weight, int weight_gap, int height_gap);
    ~Manager();
    int size() const;
    void draw(std::shared_ptr<QPainter> active_painter,
              std::shared_ptr<QPainter> debug_painter,
              std::shared_ptr<QPainter> normal_painter) const;
    void create(int n);
};

#endif // MANAGER_H
