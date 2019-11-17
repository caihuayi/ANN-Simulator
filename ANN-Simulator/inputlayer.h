#ifndef INPUTLAYER_H
#define INPUTLAYER_H

#include <memory>
#include "layer.h"
#include "inputneutron.h"
class InputLayer : public Layer
{
private:
    void create(int n) override;
public:
    InputLayer();
    InputLayer(int x, int y, int neutron_count, int height_gap, int neutron_weight, int neutron_height);
    ~InputLayer() override ;
};

#endif // INPUTLAYER_H
