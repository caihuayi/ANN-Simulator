#include "neutron.h"

using namespace std;
Neutron::Neutron()
{

}

Neutron::Neutron(const QPoint &p, int w, int h, int llc):
    position(p), weight(w), height(h), weight_vector(llc, 0)
  , is_active(false), is_debug(false), output(-1)
{
    renew_point();
    compute_mid_point();
}

Neutron::~Neutron()
{}

void Neutron::renew_point()
{
    fpoint.setX(position.x());
    fpoint.setY(position.y() + height/2);
    bpoint.setX(position.x() + weight);
    bpoint.setY(position.y() + height/2);
}

const QPoint& Neutron::get_fpoint() const
{
    return fpoint;
}

const QPoint& Neutron::get_bpoint() const
{
    return bpoint;
}

void Neutron::set_input(double in)
{
    input = in;
}

double Neutron::get_input() const
{
    return input;
}

double Neutron::get_output() const
{
    return output;
}

void Neutron::set_active(bool act)
{
    is_active = act;
}

bool Neutron::get_active() const
{
    return is_active;
}

void Neutron::set_debug(bool de)
{
    is_debug = de;
}

bool Neutron::get_debug() const
{
    return is_debug;
}

const QPoint& Neutron::get_old_point() const
{
    return old_position;
}

void Neutron::draw(std::shared_ptr<QPainter> painter,
                   std::shared_ptr<QBrush> active_brush,
                   std::shared_ptr<QBrush> debug_brush,
                   std::shared_ptr<QBrush> normal_brush) const
{
    shared_ptr<QBrush> brush = normal_brush;
    if (is_active == true)
    {
        brush = active_brush;
    }
    if (is_debug == true)
    {
        brush = debug_brush;
    }
    painter->setBrush(*brush);
    painter->drawRect(position.x(), position.y(), weight, height);
    if (output != -1)
    {
        painter->drawText(mid_position, QString::number(get_output()));
    }
}

inline bool Neutron::is_in(double x, double y)
{
    return x >= position.x() && x <= position.x()+weight
            && y >= position.y() && y <= position.y()+height;
}

void Neutron::OnPress(double x, double y)
{
    if (is_in(x, y))
    {
        is_active = true;
    }
    else
    {
        is_active = false;
    }
}

void Neutron::OnMove(double cx, double cy)
{
    if (is_active == true)
    {
        position.setX(position.x()+cx);
        position.setY(position.y()+cy);
        renew_point();
        compute_mid_point();
    }
}

void Neutron::OnRelease(double x, double y)
{
    old_position.setX(x);
    old_position.setY(y);
}

void Neutron::compute_mid_point()
{
    mid_position.setX(position.x()+weight/4);
    mid_position.setY(position.y()+height/2);
}
