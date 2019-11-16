#include "manager.h"
#include "layer.h"
using namespace std;
Manager::Manager()
{
    init_painter();
}

Manager::Manager(int x, int y, int nh, int nw, int wg, int hg):
    first_pos(x, y), neutron_height(nh), neutron_weight(nw),
    weight_gap(wg), height_gap(hg)
{
    init_painter();
}

Manager::~Manager()
{
}

void Manager::init_painter()
{
    QPen active_pen(Qt::red);
    QBrush active_brush(Qt::red, Qt::BrushStyle::TexturePattern);
    active_painter.reset(new QPainter());
    active_painter->setPen(active_pen);
    active_painter->setBrush(active_brush);

    QPen debug_pen(Qt::green);
    QBrush debug_brush(Qt::green, Qt::BrushStyle::TexturePattern);
    debug_painter.reset(new QPainter());
    debug_painter->setPen(debug_pen);
    debug_painter->setBrush(debug_brush);

    QPen normal_pen(Qt::black);
    QBrush normal_brush(Qt::BrushStyle::NoBrush);
    normal_painter.reset(new QPainter());
    normal_painter->setPen(normal_pen);
    normal_painter->setBrush(normal_brush);
}

int Manager::size() const
{
    return layer_list.size();
}

void Manager::draw() const
{
    for (auto &iter : layer_list)
    {
        iter->draw(active_painter, debug_painter, normal_painter);
    }
}

void Manager::create(int n)
{
    QPoint point = first_pos;
    for (int i = 0; i < n; i++)
    {
        layer_list.append(shared_ptr<Layer>(new Layer(point.x(), point.y(), n, height_gap, neutron_weight, neutron_height)));
    }
}
