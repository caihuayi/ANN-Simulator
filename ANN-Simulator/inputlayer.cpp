#include "inputlayer.h"
using namespace std;

InputLayer::InputLayer()
{

}

InputLayer::InputLayer(int x, int y, int nc
                       , int hg, int nw, int nh) :
    Layer(x, y, hg, nw, nh, 0)
{
    create(nc);
}

InputLayer::~InputLayer()
{}

void InputLayer::create(int n)
{
    QPoint point = first_pos;
    neutron_list.clear();
    for (int i = 0; i < n; i++)
    {
        neutron_list.append(shared_ptr<Neutron>(new InputNeutron(point, neutron_weight, neutron_height, 0)));
        point.setY(point.y()+height_gap);
    }
    update_fbpoint();
    output_vector.fill(0, n);
}

QTextStream& InputLayer::write_file(QTextStream &out)
{

    return out;
}

QTextStream& InputLayer::read_file(QTextStream &in)
{

    return in;
}
