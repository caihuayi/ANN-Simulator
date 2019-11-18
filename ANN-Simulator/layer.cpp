#include "layer.h"
#include "neutron.h"
#include <iostream>
using namespace std;
Layer::Layer()
{

}

Layer::Layer(int x, int y, int n, int g, int weight, int height, int llc) :
    height_gap(g), neutron_weight(weight), neutron_height(height), last_layer_count(llc)
{
    first_pos.setX(x);
    first_pos.setY(y);
    debug_neuron = nullptr;
}
/*
void Layer::create(int n)
{
    QPoint point = first_pos;
    neutron_list.clear();
    for (int i = 0; i < n; i++)
    {
        neutron_list.append(shared_ptr<Neutron>(new HideNeutron(point, neutron_weight, neutron_height, last_layer_count, 0, 0)));
        point.setY(point.y()+height_gap);
    }
    update_fbpoint();
    output_vector.fill(0, n);
}*/

void Layer::renew_output()
{
    int i = 0;
    for (auto& iter : neutron_list)
    {
        output_vector[i++] = iter->get_output();
    }
}

void Layer::update_fbpoint()
{
    fpoint_list.clear();
    bpoint_list.clear();
    for (auto& iter : neutron_list)
    {
        fpoint_list.append(iter->get_fpoint());
        bpoint_list.append(iter->get_bpoint());
    }
}

int Layer::size() const
{
    return neutron_list.size();
}

void Layer::set_input(QVector<double> in)
{
    input_vector = in;
}

const QVector<double>& Layer::get_output() const
{
    return output_vector;
}

void Layer::draw(std::shared_ptr<QPainter> painter,
                 std::shared_ptr<QBrush> active_brush,
                 std::shared_ptr<QBrush> debug_brush,
                 std::shared_ptr<QBrush> normal_brush) const
{
    for (auto& iter : neutron_list)
    {
        iter->draw(painter, active_brush, debug_brush, normal_brush);
    }
}

void Layer::remove_node(shared_ptr<Neutron> neu)
{
    if (neutron_list.removeOne(neu) == false)
    {
        throw "Layer::remove_node false: cannot find the Neutron";
    }
    output_vector.pop_back();
}

void Layer::add_node(shared_ptr<Neutron> neu)
{
    neutron_list.append(neu);
}

void Layer::onPress(double x, double y)
{
    for (auto& iter : neutron_list)
    {
        iter->OnPress(x, y);
    }
}

void Layer::onRelease(double x, double y)
{
    for (auto& iter : neutron_list)
    {
        if (iter->get_active())
        {
            iter->OnRelease(x, y);
        }
    }
}

void Layer::onMove(double cx, double cy)
{
    for (auto& iter : neutron_list)
    {
        if (iter->get_active())
        {
            iter->OnMove(cx, cy);
        }
    }
    update_fbpoint();
}

shared_ptr<Neutron> Layer::get_active_neutron()
{
    for (auto& iter : neutron_list)
    {
        if (iter->get_active())
        {
            return iter;
        }
    }
    return nullptr;
}

const QList<QPoint>& Layer::get_fplist() const
{
    return fpoint_list;
}

const QList<QPoint>& Layer::get_bplist() const
{
    return bpoint_list;
}

void Layer::random_para()
{
    for (auto& iter : neutron_list)
    {
        iter->random_para();
    }
}

void Layer::update_para(QVector<double> para)
{
    for (auto& iter : neutron_list)
    {
        iter->update_para(para);
    }
}

void Layer::update_activation(std::shared_ptr<ActivationFunction> af)
{
    for (auto& iter : neutron_list)
    {
        iter->update_activation(af);
    }
}

void Layer::layer_compute()
{
    output_vector.clear();
    for (auto& iter : neutron_list)
    {
        output_vector.append(iter->compute(input_vector));
    }
}

void Layer::layer_debug()
{
    shared_ptr<Neutron> neu = get_debug_neutron();
    if (neu == nullptr)
    {
        neu = neutron_list.front();
        neu->set_debug(true);
        neu->compute(input_vector);
    }
    else if (neu == neutron_list.back())
    {
        neu->set_debug(false);
    }
    else
    {
        neu->set_debug(false);
        QList<shared_ptr<Neutron>>::const_iterator iter = qFind(neutron_list, neu);
        iter++;
        (*iter)->set_debug(true);
        (*iter)->compute(input_vector);
    }
}

shared_ptr<Neutron> Layer::get_debug_neutron()
{
    return debug_neuron;
}

bool Layer::get_debugging() const
{
    return is_debugging;
}

bool Layer::debug_have_next()
{
    cout << "layer 4" << endl;
    QList<shared_ptr<Neutron>>::const_iterator iter = qFind(neutron_list, debug_neuron);
    cout << "layer 5" << endl;
    if (++iter == neutron_list.end())
    {
        is_debugging = false;
        return false;
    }
    else
    {
        is_debugging = true;
        return true;
    }
}

bool Layer::debug_next(shared_ptr<Layer> layer)
{
    if (debug_neuron == nullptr)
    {
        QList<shared_ptr<Neutron>>::const_iterator iter = neutron_list.begin();
        debug_neuron = *iter;
        debug_neuron->set_debug(true);
        set_input(layer->get_output());
        debug_neuron->compute(input_vector);
        return true;
    }
    cout << "layer 1" << endl;
    if (debug_have_next() == true)
    {
        QList<shared_ptr<Neutron>>::const_iterator iter = qFind(neutron_list, debug_neuron);
        (*iter)->set_debug(false);
        ++iter;
        for (int i = 0; i < 4; i++)
        {
            cout << layer->get_output()[i] << endl;
        }
        set_input(layer->get_output());
        for (int i = 0; i < 4; i++)
        {
            cout << input_vector[i] << endl;
        }
        output_vector.append((*iter)->compute(input_vector));
        (*iter)->set_debug(true);
        debug_neuron = *iter;
        cout << "layer 2" << endl;
        return true;
    }
    else
    {
        cout << "layer 3" << endl;
        debug_neuron = nullptr;
        return false;
    }
}
