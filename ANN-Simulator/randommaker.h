#ifndef RANDOMMAKER_H
#define RANDOMMAKER_H

#include <QTime>
#include <cmath>
class RandomMaker
{

public:
    static int random;
    RandomMaker();
    double make_random(int max);
};

#endif // RANDOMMAKER_H
