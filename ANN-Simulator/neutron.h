#ifndef NEUTRON_H
#define NEUTRON_H
#include <QPainter>
#include <memory>
class Neutron
{
protected:
    QPoint position;
    QPoint old_position;
    QPoint fpoint;
    QPoint bpoint;
    int weight;
    int height;
    double input;
    double output;
    bool is_active;
    bool is_debug;
private:
    inline bool is_in(double x, double y);
    void renew_point();
public:
    Neutron();
    Neutron(const QPoint &position, int weight, int height);
    virtual ~Neutron();
    const QPoint& get_fpoint() const;
    const QPoint& get_bpoint() const;
    void set_input(double input);
    double get_input() const;
    double get_output() const;
    void set_active(bool act);
    bool get_active() const;
    void set_debug(bool de);
    bool get_debug() const;
    virtual void draw(std::shared_ptr<QPainter> active_painter,
              std::shared_ptr<QPainter> debug_painter,
              std::shared_ptr<QPainter> normal_painter) const;

    void OnPress(double x, double y);
    void OnMove(double cx, double cy);
    void OnRelease(double x, double y);
};

#endif // NEUTRON_H
