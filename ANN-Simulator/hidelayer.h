#ifndef HIDELAYER_H
#define HIDELAYER_H

#include <memory>
#include "layer.h"
#include "hideneutron.h"
class HideLayer : public Layer
{
private:
    void create(int n) override;
public:
    HideLayer();
    HideLayer(int x, int y, int neutron_count, int height_gap, int neutron_weight, int neutron_height, int last_layer_count);
    ~HideLayer() override;
};

#endif // HIDELAYER_H