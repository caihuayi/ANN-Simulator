#include "hidelayer.h"
using namespace std;

HideLayer::HideLayer()
{

}

HideLayer::HideLayer(int x, int y, int nc, int hg, int nw, int nh, int llc) :
    Layer(x, y, hg, nw, nh, llc)
{
    create(nc);
}

HideLayer::~HideLayer()
{}

void HideLayer::create(int n)
{
    QPoint point = first_pos;
    neutron_list.clear();
    for (int i = 0; i < n; i++)
    {
        neutron_list.append(shared_ptr<Neutron>(new HideNeutron(point, neutron_weight, neutron_height, last_layer_count)));
        point.setY(point.y()+height_gap);
    }
    update_fbpoint();
    output_vector.fill(0, n);
}

void HideLayer::update_activation(shared_ptr<ActivationFunction> af)
{
    for (auto& iter : neutron_list)
    {
        iter->update_activation(af);
    }
}
