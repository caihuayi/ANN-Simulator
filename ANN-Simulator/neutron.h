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
    QVector<double> weight_vector;
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
    Neutron(const QPoint &position, int weight, int height, int last_layer_count);
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
    const QPoint& get_old_point() const;
    virtual void draw(std::shared_ptr<QPainter> painter,
                      std::shared_ptr<QBrush> active_brush,
                      std::shared_ptr<QBrush> debug_brush,
                      std::shared_ptr<QBrush> normal_brush) const;
    virtual void random_para() = 0;
    void OnPress(double x, double y);
    void OnMove(double cx, double cy);
    void OnRelease(double x, double y);
    virtual QVector<double> get_weight_vector() const = 0;
};

#endif // NEUTRON_H
