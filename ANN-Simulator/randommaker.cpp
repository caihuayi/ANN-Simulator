#include "randommaker.h"
#include <iostream>
using namespace std;
RandomMaker::RandomMaker()
{

}

int RandomMaker::random = 0;

double RandomMaker::make_random(int max)
{
    if (random == 0)
    {
        QTime time;
        time = QTime::currentTime();
        qsrand(time.msec()*qrand());
        random = qrand();

    }
    qsrand(random);
    random = qrand();
    max *= 1000;
    double result = random % max;
    result /= 1000;

    return result;
}
