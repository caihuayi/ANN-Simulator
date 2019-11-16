#include "manager.h"
#include "layer.h"
#include "neutron.h"
#include <iostream>
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
    //painter->setPen(*line_pen);
    QList<std::shared_ptr<Layer>>::const_iterator iter = layer_list.begin();
    iter++;
    for (; iter != layer_list.end(); iter++)
    {
        cout << "first for " << endl;
        QList<std::shared_ptr<Layer>>::const_iterator fiter = --iter;
        iter++;
        QList<QPoint> start = (*fiter)->get_bplist();
        QList<QPoint> end = (*iter)->get_fplist();
        for (auto& iter1 : start)
        {
            cout << "second for " << endl;
            for (auto& iter2 : end)
            {
                painter->drawLine(iter1, iter2);
                cout << "drawLine" << endl;
            }
        }
    }
    //painter->setPen()
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

void Manager::create(int n)
{
    QPoint point = first_pos;
    for (int i = 0; i < n; i++)
    {
        layer_list.append(shared_ptr<Layer>(new Layer(point.x(), point.y(), n, height_gap, neutron_weight, neutron_height)));
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
