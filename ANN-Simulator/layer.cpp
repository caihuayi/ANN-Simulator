#include "layer.h"
#include "neutron.h"
using namespace std;
Layer::Layer()
{

}

Layer::Layer(int x, int y, int n, int g, int weight, int height) :
    height_gap(g), neutron_weight(weight), neutron_height(height)
{
    first_pos.setX(x);
    first_pos.setY(y);
    create(n);
}

void Layer::create(int n)
{
    QPoint point = first_pos;
    for (int i = 0; i < n; i++)
    {
        neutron_list.append(shared_ptr<Neutron>(new Neutron(point, neutron_weight, neutron_height)));
        point.setY(point.y()+height_gap);
    }
    update_fbpoint();
    output_vector.fill(0, n);
}

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

void Layer::set_input(const Layer &layer)
{
    input_vector = layer.get_output();
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


