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
    debug_neutron = nullptr;
    debug_layer = nullptr;
}

Manager::~Manager()
{
}

int Manager::size() const
{
    return layer_list.size();
}

void Manager::draw_line(std::shared_ptr<QPainter> painter) const
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
    draw_line(painter);
}

void Manager::create()
{
    QPoint point = first_pos;
    layer_list.clear();
    layer_list.append(shared_ptr<Layer>(new InputLayer(point.x(), point.y(), neutron_count[0], height_gap, neutron_weight, neutron_height)));
    cout << "Manager create" << endl;
    point.setX(point.x()+weight_gap);
    for (int i = 1; i < layer_count; i++)
    {
        cout << i << endl;
        shared_ptr<Layer> temp(new HideLayer(point.x(), point.y(), neutron_count[i], height_gap, neutron_weight, neutron_height, neutron_count[i-1]));
        shared_ptr<ActivationFunction> af(new ActivationReLu());
        temp->update_activation(af);
        layer_list.append(temp);
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

void Manager::update_para(QVector<double> para)
{
    for (auto& iter : layer_list)
    {
        iter->update_para(para);
    }
}

void Manager::update_layer_activation(std::shared_ptr<Layer> l, std::shared_ptr<ActivationFunction> af)
{
    l->update_activation(af);
}

void Manager::compute_all()
{
    QList<shared_ptr<Layer>>::iterator iter1 = layer_list.begin();
    QList<shared_ptr<Layer>>::iterator iter2 = iter1++;
    for (; iter1 != layer_list.end(); iter1++)
    {
        (*iter1)->set_input((*iter2++)->get_output());
        (*iter1)->layer_compute();
    }
}

void Manager::set_input()
{
    shared_ptr<Layer> l = layer_list.front();
    l->renew_output();
}

bool Manager::debug_next()
{
    QList<shared_ptr<Layer>>::const_iterator iter1;
    QList<shared_ptr<Layer>>::const_iterator iter2;
    if (this->debug_layer == nullptr)
    {
        iter1 = layer_list.begin();
        iter2 = iter1;
        debug_layer = *++iter1;
        layer_list.back()->set_last_debug(false);
    }
    else
    {
        iter1 = qFind(layer_list, debug_layer);
        iter2 = --iter1;
        ++iter1;
    }
    if ((*iter1)->debug_next(*iter2) == false)
    {
        (*iter1)->renew_output();
        if (++iter1 == layer_list.end())
        {
            debug_layer = nullptr;
            return false;
        }
        else
        {
            ++iter2;
        }
    }

    debug_layer = *iter1;

    return true;
}

QTextStream& Manager::write_file(QTextStream &out)
{
    int layer_size = layer_list.size();
    out << layer_size << " ";
    for (int i = 0; i < layer_size; i++)
    {
        out << neutron_count[i] << " ";
    }
    for (auto& iter : layer_list)
    {
        iter->write_file(out);
    }

    return out;
}

QTextStream& Manager::read_file(QTextStream &in)
{
    int layer_size;
    in >> layer_size;
    layer_count = layer_size;
    neutron_count.clear();
    for (int i = 0; i < layer_size; i++)
    {
        int x;
        in >> x;
        neutron_count.append(x);
    }
    create();
    for(auto& iter : layer_list)
    {
        iter->read_file(in);
    }
    update_fbpoint();
    cout << "Mangaer read_file create" << endl;


    return in;
}
