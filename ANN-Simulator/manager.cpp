#include "manager.h"
#include "layer.h"
#include "neutron.h"
using namespace std;
Manager::Manager()
{
}

Manager::Manager(int x, int y, int nh, int nw, int wg, int hg):
    first_pos(x, y), neutron_height(nh), neutron_weight(nw),
    weight_gap(wg), height_gap(hg)
{
}

Manager::~Manager()
{
}

int Manager::size() const
{
    return layer_list.size();
}

void Manager::draw_line(std::shared_ptr<QPainter> painter, std::shared_ptr<QPen> line_pen) const
{
    QList<std::shared_ptr<Layer>>::const_iterator iter = layer_list.begin();
    iter++;
    for (; iter != layer_list.end(); iter++)
    {
        QList<std::shared_ptr<Layer>>::const_iterator fiter = --iter;
        iter++;
        QList<QPoint> start = (*fiter)->get_bplist();
        QList<QPoint> end = (*iter)->get_fplist();
        for (auto& iter1 : start)
        {
            for (auto& iter2 : end)
            {
                painter->drawLine(iter1, iter2);
            }
        }
    }
}

void Manager::draw_layer(std::shared_ptr<QPainter> painter,
                         std::shared_ptr<QBrush> active_brush,
                         std::shared_ptr<QBrush> debug_brush,
                         std::shared_ptr<QBrush> normal_brush) const
{
    for (auto &iter : layer_list)
    {
        iter->draw(painter, active_brush, debug_brush, normal_brush);
    }
}

void Manager::draw(std::shared_ptr<QPainter> painter,
                   std::shared_ptr<QBrush> active_brush,
                   std::shared_ptr<QBrush> debug_brush,
                   std::shared_ptr<QBrush> normal_brush,
                   std::shared_ptr<QPen> line_pen) const
{
    draw_layer(painter, active_brush, debug_brush, normal_brush);
    draw_line(painter, line_pen);
}

void Manager::create()
{
    QPoint point = first_pos;
    layer_list.clear();
    layer_list.append(shared_ptr<Layer>(new InputLayer(point.x(), point.y(), neutron_count[0], height_gap, neutron_weight, neutron_height)));
    point.setX(point.x()+weight_gap);
    for (int i = 1; i < layer_count; i++)
    {
        layer_list.append(shared_ptr<Layer>(new HideLayer(point.x(), point.y(), neutron_count[i], height_gap, neutron_weight, neutron_height, neutron_count[i-1])));
        point.setX(point.x()+weight_gap);
    }
}

void Manager::OnPress(double x, double y)
{
    for (auto& iter : layer_list)
    {
        iter->onPress(x, y);
    }
}

void Manager::OnRelease(double x, double y)
{
    for (auto& iter : layer_list)
    {
        iter->onRelease(x, y);
    }
}

void Manager::OnMove(double cx, double cy)
{
    for (auto& iter : layer_list)
    {
        iter->onMove(cx, cy);
    }
}

shared_ptr<Neutron> Manager::search_active()
{
    for (auto& iter : layer_list)
    {
        if (iter->get_active_neutron() != nullptr)
        {
            return iter->get_active_neutron();
        }
    }

    return nullptr;
}

void Manager::update_fbpoint()
{
    for (auto& iter : layer_list)
    {
        iter->update_fbpoint();
    }
}

void Manager::set_network(int lc, QVector<int> nc)
{
    layer_count = lc;
    neutron_count = nc;
}

void Manager::random_para()
{
    for (auto& iter : layer_list)
    {
        iter->random_para();
    }
}
