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

void Layer::draw(std::shared_ptr<QPainter> active_painter,
                 std::shared_ptr<QPainter> debug_painter,
                 std::shared_ptr<QPainter> normal_painter) const
{
    for (auto& iter : neutron_list)
    {
        iter->draw(active_painter, debug_painter, normal_painter);
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








